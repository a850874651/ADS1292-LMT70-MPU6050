/**
  ******************************************************************************
  * @file           : port_delay.h
  * @brief          : 底层软件延时头文件
  * @details        : 提供毫秒和微妙级别的软件延时接口
  * @author         : WJXZZZ
  * @date           : 2020/9/2
  * @version        : V0.1
  * @copyright      : Copyright (C) 
  ******************************************************************************
  * @attention      
  * NONE
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
#include "port_delay.h"

/** @addtogroup My_App
  * @{
  */
/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
static uint8_t  fac_us=0;							/* us延时倍乘数 */			   
static uint16_t fac_ms=0;							/* ms延时倍乘数,在ucos下,代表每个节拍的ms数 */
static uint8_t delay_init_flag = 0 ;                /* 延时函数初始化标志位 */

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/

/** @brief  初始化延迟函数
  * @details SYSTICK的时钟固定为HCLK时钟的1/8
  * @retval None
  */
static void port_delay_init(void)
{
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	/* 选择外部时钟  HCLK/8 */
	fac_us=SystemCoreClock/8000000 ;				                /* 为系统时钟的1/8 */

	fac_ms=(uint16_t)fac_us*1000;					            /* 非OS下,代表每个ms需要的systick时钟数 */   
}	

/** @brief  微妙延时
  * @details 
  * @retval None
  */
void port_delay_us( uint32_t us) 
{
	uint32_t temp ;
    
    if ( delay_init_flag == 0)
    {
        port_delay_init() ;
        delay_init_flag = 1 ;
    }
    
	SysTick->LOAD = us * fac_us ; 					/* 时间加载 */	  		 
	SysTick->VAL = 0x00 ;        					/* 清空计数器 */   
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;	    /* 开始倒数 */
    
	do                                              /* 等待时间到达 */ 
	{
		temp = SysTick->CTRL ;
	}while( ( temp & 0x01) && ( !( temp & ( 1 << 16)))) ;		
    
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk ;	    /* 关闭计数器 */
	SysTick->VAL = 0X00 ;      					    /* 清空计数器 */
}    

/** @brief  毫秒延时
  * @details 延时nms,注意nms的范围,对72M条件下,nms<=1864
  * @retval None
  */
void port_delay_ms( uint32_t ms)
{
 		  	  
	uint32_t temp ;	
    
    if ( delay_init_flag == 0)
    {
        port_delay_init() ;
        delay_init_flag = 1 ;
    }
    
	SysTick->LOAD = (uint32_t)( ms * fac_ms) ; /* 时间加载(SysTick->LOAD为24bit) */
	SysTick->VAL = 0x00 ;					    /* 清空计数器 */
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;	/* 开始倒数 */
    
	do                                          /* 等待时间到达 */ 
	{
		temp=SysTick->CTRL;
	}while( ( temp & 0x01) && ( !( temp & ( 1 << 16)))) ;		  
    
	SysTick->CTRL &= ( ~SysTick_CTRL_ENABLE_Msk) ;	/* 关闭计数器 */
	SysTick->VAL = 0X00 ;       					/* 清空计数器 */	  	    
}


/**
  * @}
  */



