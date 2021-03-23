/**
  ******************************************************************************
  * @file           : my_debug.c
  * @brief          : �Զ����debug��
  * @details        : �ض���print����ʵ����itm debug�µĵ�����Ϣ��ӡ����Ҫ��
  *                   sys_config.h��ͨ��MY_DEBUG_USE_PR��PRINT_LEVEL������
  *                   ������Ϣ������غͼ���
  * @author         : WJXZZZ
  * @date           : 2020/6/13
  * @version        : V0.1
  * @copyright      : Copyright (C) 
  ******************************************************************************
  * @attention      
  * Ӳ��ƽ̨����jlink�ӿڵ�stm32��Ƭ��
  * ���ƽ̨��KEIL V5
  ******************************************************************************
  * @verbatim
  * �޸���ʷ:    
  *      1. ���ڣ�2020/6/13
  *         ���ߣ�Charmander
  *         �޸ģ�
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

//�ض���fputc���� 
int fputc(int ch, FILE *f)
{ 	
    while((USART1->SR&0X40)==0);//ѭ������,ֱ���������   
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
	/* �������������if���棬�������ر�ʱ��ִ��Ч�� */
	if ( tag <= PRINT_LEVEL)
	{
		va_list valist ;    /* ...��ʾ�ɱ��������valist��ȡ���ɱ���� */
		
		va_start(valist, fmt) ;    /* �ҵ���������ʼλ�� */
		printf("[%s]:",tagstr) ;
		vprintf(fmt,valist) ;    /* ���������vprintf */
		va_end(valist) ;
		
		printf("\r\n") ;
	}
	
	return 0 ;
}











