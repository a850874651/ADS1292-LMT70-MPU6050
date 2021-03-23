/**
  ******************************************************************************
  * @file           : my_app.c
  * @brief          : 顶层应用程序源文件
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
  * 修改历史:    
  *      1. 日期：2020/9/2
  *         作者：Charmander
  *         修改：
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

/* 应程序初始化 */
void my_app_init()
{          
    mcp3421_init(&mcp) ;  /* 初始化MCP3421 */ 
    lmt70_init() ;          /* 初始化lmt70 */
    
}

/* 应用程序 */
void my_app()
{        
    voltage1 = mcp3421_one_conversion(&mcp) ;	
    tep = lmt70_get_temp( voltage1) ;  
    temp=tep/100.0;//3000/00==30  
//		temp_xiaoshu=(tep%100)/100.0;
	temp_end=temp+1;
	
    pr_info("%s:%.2f",TAG,temp_end) ;              /* 打印温度,放大了100倍 */

    port_delay_ms(1000) ;
}

/**
  * @}
  */



