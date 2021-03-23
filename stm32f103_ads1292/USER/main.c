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
  * �޸���ʷ:
  *      1. ���ڣ�2020/9/2
  *         ���ߣ�Charmander
  *         �޸ģ�
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
u8 lcd_id[12];			 //���LCD ID�ַ���

int main()
{
    SystemInit() ;	//ϵͳʱ������
    delay_init();	    	 //��ʱ������ʼ��

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
    usart1_init(115200) ;
		USART2_Init();
//    LED_Init();			      //LED�˿ڳ�ʼ��

//    LCD_Init();

//    GBK_Lib_Init();       //Ӳ��GBK�ֿ��ʼ��--(���ʹ�ò����ֿ��Һ�����汾���˴��������Σ������ֿ��ʼ����

//    POINT_COLOR=RED;
    my_app_init() ;
//    LCD_Clear(GRAY0); //����
//    Draw_Font24B(16,4,MAGENTA,"DevEBox-��Խ����");
//    Draw_Font24B(48,32,MAGENTA,"Һ��������");
    while(1)
    {

        my_app() ;
			

    }
}

