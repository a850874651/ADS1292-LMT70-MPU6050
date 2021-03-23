/**
  ******************************************************************************
  * @file           : port_iic.c
  * @brief          : iic驱动源文件
  * @details        : 软件模拟iic
  * @author         : WJXZZZ
  * @date           : 2020/8/23
  * @version        : V0.1
  * @copyright      : Copyright (C) 
  ******************************************************************************
  * @attention      
  * NONE
  ******************************************************************************
  * @verbatim
  * 修改历史:    
  *      1. 日期：2020/8/23
  *         作者：Charmander
  *         修改：
  * @endverbatim
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "port_iic.h"
#include "port_delay.h"
#include "sys.h"

/** @addtogroup Port_IIC
  * @{
  */
/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/
#define I2C_DELAY_US(x) port_delay_us(x)
#define I2C_DELAY_MS(x) port_delay_ms(x)

#define I2C_SCL_SET()   PAout(12) = 1 
#define I2C_SCL_RESET() PAout(12) = 0
#define I2C_SDA_SET()   PAout(11) = 1
#define I2C_SDA_RESET() PAout(11) = 0
#define I2C_SDA_GET()   PAin(11)


#define I2C_SDA_IN()  {GPIOA->CRH&=0XFFFF0FFF;GPIOA->CRH|=0X00008000;}	//PA11输入模式
#define I2C_SDA_OUT() {GPIOA->CRH&=0XFFFF0FFF;GPIOA->CRH|=0X00003000;}  //PA11输出模式
/* Private typedef -----------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
uint8_t iic_txbuf[256] ;

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/

/* 发送iic起始信号 */
static void iic_start()
{
    /* 当 SCL 高电平时，SDA 出现一个下跳沿表示 I2C 总线启动信号 */
    I2C_SDA_OUT() ;
    I2C_SDA_SET() ;
    I2C_SCL_SET() ;
    I2C_DELAY_US(4) ;
    I2C_SDA_RESET() ;
    I2C_DELAY_US(4) ;
    I2C_SCL_RESET() ;
}

/* iic发送结束信号 */
static void iic_stop()
{
    /* 当 SCL 高电平时，SDA 出现一个上跳沿表示 I2C 总线停止信号 */
    I2C_SDA_OUT() ;
    I2C_SCL_RESET() ;
    I2C_SDA_RESET() ;  
    I2C_DELAY_US(4) ;
    I2C_SCL_SET() ;
    I2C_SDA_SET() ;
    I2C_DELAY_US(4) ;
}

/* 发送一个字节 */
static void iic_send_byte (uint8_t tx)
{
    uint8_t i ;
    
    I2C_SDA_OUT() ;
    I2C_SCL_RESET() ;
    
    for ( i = 0; i < 8; i++)
    {
        if ( tx & 0x80) 
        {
            I2C_SDA_SET() ;
        }
        else
        {
            I2C_SDA_RESET() ;
        }
        
        tx <<= 1 ;
        
        I2C_DELAY_US(2) ;
        I2C_SCL_SET() ;
        I2C_DELAY_US(2) ;
        I2C_SCL_RESET() ;       
        I2C_DELAY_US(2) ;
    }
}

/* iic读一个字节 */
static uint8_t iic_read_byte()
{
    uint8_t i ;
    uint8_t res ;
    
    res = 0 ;
    
    I2C_SDA_IN() ;
    
    for ( i = 0; i < 8; i++)
    {      
        I2C_SCL_RESET() ;
        I2C_DELAY_US(2) ;
        I2C_SCL_SET() ;
        res <<= 1 ;
        
        if ( I2C_SDA_GET())
        {
            res++ ;
        }

        I2C_DELAY_US(1) ;
    }
    
    return res ;
}

/* iic等待应答信号 */
static uint8_t iic_wait_ack()
{
    uint8_t i ;
    
    I2C_SDA_IN() ;
    I2C_SDA_SET() ;
    I2C_DELAY_US(1) ;
    I2C_SCL_SET() ;
    I2C_DELAY_US(1) ;
    
    while ( I2C_SDA_GET())
    {
        i++ ;
        if ( i > 250)
        {
            iic_stop() ;
            return 1 ;
        }
    }
    
    I2C_SCL_RESET() ;
    
    return 0 ;
}

/* iic发送应答信号 */
static void iic_send_ack()
{
    I2C_SCL_RESET() ;
    I2C_SDA_OUT() ;
    I2C_SDA_RESET() ;   
    I2C_DELAY_US(2) ;     
    I2C_SCL_SET() ;
    I2C_DELAY_US(2) ; 
    I2C_SCL_RESET() ;   
}

static void iic_send_nack()
{
    I2C_SCL_RESET() ;
    I2C_SDA_OUT() ;
    I2C_SDA_SET() ;   
    I2C_DELAY_US(2) ;     
    I2C_SCL_SET() ;
    I2C_DELAY_US(2) ; 
    I2C_SCL_RESET() ;  
}

static void iic_memcpy ( uint8_t *dest, uint8_t *src, uint32_t length)
{
    uint32_t i ;
    
    for ( i = 0; i < length; i++)
    {
        *dest = *src ;
        dest++ ;
        src++ ;
    }
}

void iic_init()
{
 	RCC->APB2ENR|=1<<2;		/* 先使能外设IO PORTA时钟 */ 							 
	GPIOA->CRH&=0XFFF00FFF;	/* PA11/12 推挽输出 */
	GPIOA->CRH|=0X00033000;	   
	GPIOA->ODR|=3<<11;     	/* PA11/12 输出高 */
}

/* iic主机写 数据，返回0写成功，返回其他，则在写第i个数据的时候超时*/
uint8_t iic_master_transmit ( uint8_t dev, uint8_t reg, uint8_t *str, uint16_t length, uint32_t timeout)
{
    uint16_t i ;
    uint32_t j ;
    uint8_t rev ;
    
    rev = 0 ;
    
    iic_txbuf[0] = ( ( dev << 1) | 0) ;  
    iic_txbuf[1] = reg ; 
    iic_memcpy ( &(iic_txbuf[2]), str, length) ;
    length += 2 ;
    
    iic_start() ;
    
    for ( i = 0; i < length; i++)
    {
        iic_send_byte(iic_txbuf[i]) ;
        
        j = 0 ;
        while ( ( iic_wait_ack()) && ( j < timeout))
        {
            j++ ;
            I2C_DELAY_US(5) ;
        }
		
        if ( j >= timeout)
        {
            rev = i + 1 ;
            break ;
        }
    }

	iic_stop() ;
    
	return rev ;	   
}

uint8_t iic_master_receive ( uint8_t dev, uint8_t reg, uint8_t *str, uint16_t length, uint32_t timeout)
{
    uint16_t i = 0 ;
    
    iic_start() ; 
	iic_send_byte ( ( dev << 1) | 0) ;                                
    
	if( iic_wait_ack())	                                                    
	{
		iic_stop() ;		 
		return 1 ;		
	}
    
    iic_send_byte(reg) ;	                                              
    if( iic_wait_ack())	                                                    
	{
		iic_stop() ;		 
		return 1 ;		
	}
    
    iic_start() ;
	iic_send_byte( ( dev << 1) | 1) ;                                   
    if( iic_wait_ack())	                                                    
	{
		iic_stop() ;		 
		return 1 ;		
	} 

    length-- ;
    
    for ( ; i < length; i++)
    {
        str[i] = iic_read_byte() ;
        iic_send_ack() ;        
    }
    
    str[i] = iic_read_byte() ;                                        
    iic_send_nack() ;
    
    iic_stop() ;	                                                         
    
	return 0 ;
}


/**
  * @}
  */


























