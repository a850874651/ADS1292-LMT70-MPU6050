/**
  ******************************************************************************
  * @file           : my_debug.c
  * @brief          : 自定义的debug库
  * @details        : 重定向print函数实现在itm debug下的调试信息打印。需要在
  *                   sys_config.h中通过MY_DEBUG_USE_PR和PRINT_LEVEL宏设置
  *                   调试信息输出开关和级别。
  * @author         : Charmander 有为电子科技 QQ: 228303760
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
#include "port_uart.h"

/* Private constants ---------------------------------------------------------*/

/* Private macros ------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
volatile uint16_t usart1_rx_length = 0 ;
volatile uint8_t usart1_rx_flag = 0 ;
volatile uint8_t usartx_rx_buf[UARTX_BUFF_SIZE] ;

/* Private function prototypes -----------------------------------------------*/

/* Exported functions --------------------------------------------------------*/  

/**
  * 函数功能: 配置NVIC，设定USART接收中断优先级.
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明：无
  */
void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure; 
	 /* 嵌套向量中断控制器组选择 */  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	
   /* 配置USART为中断源 */
	NVIC_InitStructure.NVIC_IRQChannel = USARTx_IRQn;	 
	 /* 抢断优先级为0 */
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	 /* 子优先级为1 */
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	 /* 使能中断 */
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	 /* 初始化配置NVIC */
	NVIC_Init(&NVIC_InitStructure);
}

/**
  * 函数功能: 串口参数配置.
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明：使用宏定义方法代替具体引脚号，方便程序移植，只要简单修改bsp_led.h
  *           文件相关宏定义就可以方便修改引脚。
  */
void USARTx_Init(void)
{
  /* 定义IO硬件初始化结构体变量 */
  GPIO_InitTypeDef GPIO_InitStructure;
  /* 定义USART初始化结构体变量 */
	USART_InitTypeDef USART_InitStructure;
  
  /* 配置NVIC，设定USART接收中断优先级 */
  NVIC_Configuration();
  
  /* 使能USART时钟 */
  USARTx_ClockCmd(USARTx_CLK,ENABLE);
  /* 使能USART功能GPIO时钟 */
  USARTx_GPIO_ClockCmd(USARTx_TX_CLK | USARTx_RX_CLK | RCC_APB2Periph_AFIO,ENABLE);
  
	/* 调试USART功能GPIO初始化 */
	/* 设定USART发送对应IO编号 */
	GPIO_InitStructure.GPIO_Pin =  USARTx_TX_PIN;
  /* 设定USART发送对应IO模式：复用推挽输出 */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  /* 设定USART发送对应IO最大操作速度 ：GPIO_Speed_50MHz */
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  /* 初始化USART发送对应IO */
	GPIO_Init(USARTx_TX_PORT, &GPIO_InitStructure);    
  
	/* 设定USART接收对应IO编号 */
	GPIO_InitStructure.GPIO_Pin = USARTx_RX_PIN;
  /* 设定USART发送对应IO模式：浮空输入 */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  /* 其他没有重新赋值的成员使用与串口发送相同配置 */
  /* 初始化USART接收对应IO */
	GPIO_Init(USARTx_RX_PORT, &GPIO_InitStructure);	
			
	/* USART工作环境配置 */
  /* USART波特率:115200 */
	USART_InitStructure.USART_BaudRate = USARTx_BAUDRATE;
  /* USART字长(有效位)：8位 */
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  /* USART停止位：1位 */
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
  /* USART校验位：无 */
	USART_InitStructure.USART_Parity = USART_Parity_No ;
  /* USART硬件数据流控制(硬件信号控制传输停止)：无 */
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	/* USART工作模式使能：允许接收和发送 */
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  /* 初始化USART */
	USART_Init(USARTx, &USART_InitStructure);
  
	/* 使能接收中断 */
  USART_ITConfig(USARTx, USART_IT_RXNE, ENABLE);	
  
  /* 清除发送完成标志 */
	USART_ClearFlag(USARTx, USART_FLAG_TC|USART_FLAG_TXE|USART_FLAG_RXNE);
  /* 使能USART */
	USART_Cmd(USARTx, ENABLE);
 
}

/**
  * 函数功能: 串口发送一个字节数据 
  * 输入参数: ch：待发送字符
  * 返 回 值: 无
  * 说    明：无
  */
void Usart_SendByte(uint8_t ch)
{
  /* 发送一个字节数据到USART1 */
  USART_SendData(USARTx,ch);

  /* 等待发送完毕 */
  while (USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET);	
}

/**
  * 函数功能: 串口发送指定长度的字符串
  * 输入参数: str：待发送字符串缓冲器
  *           strlen:指定字符串长度
  * 返 回 值: 无
  * 说    明：无
  */
void Usart_SendStr_length(uint8_t *str,uint32_t strlen)
{
  unsigned int k=0;
  do 
  {
    Usart_SendByte(*(str + k));
    k++;
  } while(k < strlen);
}

/**
  * 函数功能: 串口发送字符串，直到遇到字符串结束符
  * 输入参数: str：待发送字符串缓冲器
  * 返 回 值: 无
  * 说    明：无
  */
void Usart_SendString(uint8_t *str)
{
	unsigned int k=0;
  do 
  {
    Usart_SendByte(*(str + k));
    k++;
  } while(*(str + k)!='\0');
}

uint8_t get_uart_data ( uint8_t *p, uint16_t *l)
{
    uint8_t rev = 0 ;
    uint16_t i ;
    
    if ( usart1_rx_flag != 0)
    {
        rev = usart1_rx_flag ;        
        
        if ( usart1_rx_flag == 1)
        {
           *l = usart1_rx_length ;
            
           for ( i = 0; i < UARTX_BUFF1_SIZE; i++) 
               p[i] = usartx_rx_buf[i] ;
        }
        else
        {       
            *l = usart1_rx_length - UARTX_BUFF1_SIZE ;
            usart1_rx_length = 0 ;
            
            for ( i = 0; i < UARTX_BUFF1_SIZE; i++)
               p[i] = usartx_rx_buf[i+UARTX_BUFF1_SIZE] ;
        }  

        usart1_rx_flag = 0 ;
    }
    
    return rev ;
}

void USARTx_IRQHANDLER(void)
{
	if( USART_GetITStatus(USARTx, USART_IT_RXNE) != RESET)
	{ 	            
		usartx_rx_buf[usart1_rx_length] = USART_ReceiveData(USARTx);
        
        usart1_rx_length++ ;
        
        if ( usart1_rx_length == UARTX_BUFF1_SIZE)
        {
            usart1_rx_flag = 1 ;
        }
        else if ( usart1_rx_length == UARTX_BUFF_SIZE)
        {
            usart1_rx_flag = 2 ;
        }
	} 	 
}






