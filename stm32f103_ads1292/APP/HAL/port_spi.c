/**
  ******************************************************************************
  * @file           : port_spi.c
  * @brief          : 提供给ds1302的spi接口是
  * @details        : 移植时需要根据具体硬件实现spi初始化和读写接口
  * @author         : 
  * @date           : 2020/9/2
  * @version        : V0.1
  * @copyright      : Copyright (C) 
  ******************************************************************************
  * @attention
  * 硬件平台 stm32f103c8t6
  * 软件平台 keil 5  
  *
  * -该版本使用hal库实现
  ******************************************************************************
  * @verbatim
  * 修改历史:    
  *      1. 日期：2020/9/2
  *         作者：Charmander
  *         修改：
  * @endverbatim
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "port_spi.h"

/** @addtogroup Port_Spi
  * @{
  */
/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/

/* spi初始化 */ 
void port_spi_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;   
	SPI_InitTypeDef SPI_InitStructure;	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_SPI1, ENABLE) ; 
	
	/* SCK  PA5，MISO  PA6，MOSI  PA7 */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;                                                                                                   
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;   
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;    
    GPIO_Init(GPIOA,&GPIO_InitStructure);              
				
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  /* 双线双向全双工 */
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;                       /* 设置为主SPI */
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b; 		            /* SPI发送8bit数据 */
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low; 					        /* SCLK空闲为低，上升沿锁存数据 */
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge; 					    /* 第二个时钟沿数据被采样 */
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;							/* 片选由软件控制 */
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32;  /* 时钟分频72M/x */ 
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB; 		            /* 高位在前 */
	SPI_InitStructure.SPI_CRCPolynomial = 7; 							/* CRC计算值的多项式 */
	SPI_Init(SPI1,&SPI_InitStructure); 	
	SPI_Cmd(SPI1,ENABLE);                                               /* 使能SPI外设 */
}

/* spi全双工读写 */
uint8_t port_spi_transmit_receive ( uint8_t tx)
{   
	uint8_t retry = 0 ;			
    
	while ( SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET) /* 检查指定的SPI标志位设置与否:发送缓存空标志位 */
    {
        retry++ ;
        if ( retry > 200)
            return 0 ;
    }	
    
	SPI_I2S_SendData(SPI1, tx) ; /* 通过外设SPIx发送一个数据 */
	retry = 0 ;

	while ( SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET) /* 检查指定的SPI标志位设置与否:接受缓存非空标志位 */
    {
        retry++ ;
        if ( retry > 200)
            return 0 ;
    }	  
        
	return SPI_I2S_ReceiveData(SPI1) ; /* 返回通过SPIx最近接收的数据 */	
}


/**
  * @}
  */

