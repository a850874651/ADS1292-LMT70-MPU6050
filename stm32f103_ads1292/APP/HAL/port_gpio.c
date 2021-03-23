/**
  ******************************************************************************
  * @file           : port_gpio.c
  * @brief          : 为ads1292提供cs、start、rest、drdy、四个gpio引脚的接口函数
  * @details        : 应用程序初始化应用程序函数。
  * @author         :  
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
#include "port_gpio.h"

/** @addtogroup PORT_GPIO
  * @{
  */
/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/

/** @brief  cs、start、rest、drdy、四个gpio引脚初始化
  * @details 
  * @retval None
  */
void port_gpio_init() 
{
    GPIO_InitTypeDef 	GPIO_InitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_GPIOB, ENABLE) ; 	 
	
    /* CS */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 ;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz ;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   /* 推挽输出 */
    GPIO_Init(GPIOA, &GPIO_InitStructure);	
    
    /* START、RESET */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1 ;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz ;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   /* 推挽输出 */
    GPIO_Init(GPIOB, &GPIO_InitStructure);	
    
    /* DRDY，待机时高电平，采集时低电平有效 */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 ;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU ;   /* 上拉输入*/
    GPIO_Init(GPIOB, &GPIO_InitStructure) ;			  
}    



/**
  * @}
  */



