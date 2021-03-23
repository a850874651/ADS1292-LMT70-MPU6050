/**
  ******************************************************************************
  * @file           : port_gpio.c
  * @brief          : Ϊads1292�ṩcs��start��rest��drdy���ĸ�gpio���ŵĽӿں���
  * @details        : Ӧ�ó����ʼ��Ӧ�ó�������
  * @author         :  
  * @date           : 2020/9/2
  * @version        : V0.1
  * @copyright      : Copyright (C) 
  ******************************************************************************
  * @attention      
  * NONE
  ******************************************************************************
  * @verbatim
  * �޸���ʷ:    
  *      1. ���ڣ�2020/9/2
  *         ���ߣ�Charmander
  *         �޸ģ�
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

/** @brief  cs��start��rest��drdy���ĸ�gpio���ų�ʼ��
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
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   /* ������� */
    GPIO_Init(GPIOA, &GPIO_InitStructure);	
    
    /* START��RESET */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1 ;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz ;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   /* ������� */
    GPIO_Init(GPIOB, &GPIO_InitStructure);	
    
    /* DRDY������ʱ�ߵ�ƽ���ɼ�ʱ�͵�ƽ��Ч */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 ;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU ;   /* ��������*/
    GPIO_Init(GPIOB, &GPIO_InitStructure) ;			  
}    



/**
  * @}
  */



