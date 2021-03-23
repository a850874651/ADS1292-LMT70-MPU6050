#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
/******************************************************************/
//STM32F103ZE核心板
//按键驱动代码	


//DevEBox  大越创新
//淘宝店铺：mcudev.taobao.com
//淘宝店铺：shop389957290.taobao.com	
/******************************************************************/	  
							  
//////////////////////////////////////////////////////////////////////////////////   	 


#define KEY0  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)  //读取按键0
#define KEY1  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)  //读取按键1
//#define KEY2  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)//读取按键2 
#define WK_UP   GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)//读取按键3(WK_UP) 

 

#define KEY0_PRES 	1	  //KEY0按下
#define KEY1_PRES	  2	  //KEY1按下
#define KEY2_PRES	  3	  //KEY2按下
#define WKUP_PRES   4	  //KEY_UP按下(即WK_UP/KEY_UP)


void KEY_Init(void);    //IO初始化
u8 KEY_Scan(u8);  	    //按键扫描函数					    
#endif





















/******************************************************************/
//STM32F103ZE核心板
//按键驱动代码	


//DevEBox  大越创新
//淘宝店铺：mcudev.taobao.com
//淘宝店铺：shop389957290.taobao.com	
/******************************************************************/	





