/**
  ******************************************************************************
  * @file           : main.c
  * @brief          :
  * @details        :
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
#include "main.h"
#include "my_app.h"
#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"
#include "usart2.h"
#include "GBK_LibDrive.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/

u8 x=0;
u8 lcd_id[12];			 //存放LCD ID字符串

int main()
{
    SystemInit() ;	//系统时钟配置
    delay_init();	    	 //延时函数初始化

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
    usart1_init(115200) ;
		USART2_Init();
//    LED_Init();			      //LED端口初始化

//    LCD_Init();

//    GBK_Lib_Init();       //硬件GBK字库初始化--(如果使用不带字库的液晶屏版本，此处可以屏蔽，不做字库初始化）

//    POINT_COLOR=RED;
    my_app_init() ;
//    LCD_Clear(GRAY0); //清屏
//    Draw_Font24B(16,4,MAGENTA,"DevEBox-大越创新");
//    Draw_Font24B(48,32,MAGENTA,"液晶屏测试");
    while(1)
    {

        my_app() ;
			

    }
}


