/**
  ******************************************************************************
  * @file           : port_uart.h
  * @brief          : 串口一串口二DMA相关
  * @details        : 重定向print函数实调试信息打印。需要在
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

#ifndef __PORT_UART_H__
#define __PORT_UART_H__

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "port_typ.h"

/* Exported constants --------------------------------------------------------*/
#define UARTX_BUFF1_SIZE                      100
#define UARTX_BUFF2_SIZE                      100
#define UARTX_BUFF_SIZE                      (UARTX_BUFF1_SIZE+UARTX_BUFF2_SIZE)
/* Exported functions --------------------------------------------------------*/
#define USARTx_BAUDRATE                        115200

#define USARTx_ClockCmd                        RCC_APB2PeriphClockCmd
#define USARTx_CLK                             RCC_APB2Periph_USART1

#define USARTx_GPIO_ClockCmd                   RCC_APB2PeriphClockCmd
    
#define USARTx_TX_PORT                         GPIOA   
#define USARTx_TX_PIN                          GPIO_Pin_9
#define USARTx_TX_CLK                          RCC_APB2Periph_GPIOA 
#define USARTx_RX_PORT                         GPIOA 
#define USARTx_RX_PIN                          GPIO_Pin_10
#define USARTx_RX_CLK                          RCC_APB2Periph_GPIOA

#define USARTx_IRQHANDLER                      USART1_IRQHandler
#define USARTx_IRQn                            USART1_IRQn
#define USARTx                                 USART1

/* Exported types ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
void USARTx_Init(void);
void Usart_SendByte(uint8_t ch);
void Usart_SendStr_length(uint8_t *str,uint32_t strlen);
void Usart_SendString(uint8_t *str);
uint8_t get_uart_data ( uint8_t *p, uint16_t *l) ;

#endif /* __PORT_UART_H__ */

