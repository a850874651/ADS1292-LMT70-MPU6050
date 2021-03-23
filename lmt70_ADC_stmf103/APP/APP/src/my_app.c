/**
  ******************************************************************************
  * @file           : my_app.c
  * @brief          : ����Ӧ�ó���Դ�ļ�
  * @details        : 
  * @author         : WJXZZZ
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
#include "my_app.h"

#include "lmt70.h"
#include "mcp3421.h"

#include "port_debug.h"
#include "port_delay.h"
/** @addtogroup My_App
  * @{
  */
/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
uint8_t TAG[] = "app" ;

float port_ad ;
uint32_t tep ;
float temp_end;
float temp;
float temp_xiaoshu;
float voltage1 ;
mcp3421_s mcp ;
/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/

/* Ӧ�����ʼ�� */
void my_app_init()
{          
    mcp3421_init(&mcp) ;  /* ��ʼ��MCP3421 */ 
    lmt70_init() ;          /* ��ʼ��lmt70 */
    
}

/* Ӧ�ó��� */
void my_app()
{        
    voltage1 = mcp3421_one_conversion(&mcp) ;	
    tep = lmt70_get_temp( voltage1) ;  
    temp=tep/100.0;//3000/00==30  
//		temp_xiaoshu=(tep%100)/100.0;
	temp_end=temp+1;
	
    pr_info("%s:%.2f",TAG,temp_end) ;              /* ��ӡ�¶�,�Ŵ���100�� */

    port_delay_ms(1000) ;
}

/**
  * @}
  */



