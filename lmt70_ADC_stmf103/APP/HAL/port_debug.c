/**
  ******************************************************************************
  * @file           : my_debug.c
  * @brief          : 自定义的debug库
  * @details        : 重定向print函数实现在itm debug下的调试信息打印。需要在
  *                   sys_config.h中通过MY_DEBUG_USE_PR和PRINT_LEVEL宏设置
  *                   调试信息输出开关和级别。
  * @author         : WJXZZZ
  * @date           : 2020/6/13
  * @version        : V0.1
  * @copyright      : Copyright (C) 
  ******************************************************************************
  * @attention      
  * 硬件平台：有jlink接口的stm32单片机
  * 软件平台：KEIL V5
  ******************************************************************************
  * @verbatim
  * 修改历史:    
  *      1. 日期：2020/6/13
  *         作者：Charmander
  *         修改：
  * @endverbatim
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "port_debug.h"
#include "usart.h"

#include "stdio.h"
#include "stdarg.h"
/* Private constants ---------------------------------------------------------*/

/* Private macros ------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Exported functions --------------------------------------------------------*/  
#pragma import(__use_no_semihosting_swi)             
struct __FILE 
{ 
	int handle; 
} ; 

FILE __stdout ;       
FILE __stdin ; 

//重定义fputc函数 
int fputc(int ch, FILE *f)
{ 	
    while((USART1->SR&0X40)==0);//循环发送,直到发送完毕   
    USART1->DR = (uint8_t) ch;    
    
	return ch ;
}

volatile int32_t ITM_RxBuffer = ITM_RXBUFFER_EMPTY ;
int fget(FILE *f)
{
    uint8_t ch ;
    
//    HAL_UART_Receive(&huart1, (uint8_t *)&ch, 1, 10) ;

	return ( ch) ;
}

int ferror(FILE *f)
{
	return EOF ;
}

void _ttywrch(int c)
{
	fputc(c, &__stdout) ;
}

int __backspace()
{
	return 0 ;
}

void _sys_exit(int return_code)
{
label:
	goto label ;
}

int pr(int tag, char *tagstr, char *fmt, ...)
{
	/* 将变量定义放在if里面，提高输出关闭时的执行效率 */
	if ( tag <= PRINT_LEVEL)
	{
		va_list valist ;    /* ...表示可变参数，用valist来取出可变参数 */
		
		va_start(valist, fmt) ;    /* 找到参数的起始位置 */
		printf("[%s]:",tagstr) ;
		vprintf(fmt,valist) ;    /* 这里必须用vprintf */
		va_end(valist) ;
		
		printf("\r\n") ;
	}
	
	return 0 ;
}











