/**
  ******************************************************************************
  * @file           : port_uart.h
  * @brief          : ����һ���ڶ�DMA���
  * @details        : �ض���print����ʵ������Ϣ��ӡ����Ҫ��
  *                   sys_config.h��ͨ��MY_DEBUG_USE_PR��PRINT_LEVEL������
  *                   ������Ϣ������غͼ���
  * @author         : Charmander ��Ϊ���ӿƼ� QQ: 228303760
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

