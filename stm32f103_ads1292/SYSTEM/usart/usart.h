#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "sys.h" 

#define USART1_MAX_RECV_LEN		50					//最大接收缓存字节数
#define USART1_MAX_SEND_LEN		50					//最大发送缓存字节数
#define USART1_RX_EN 			1								//0,不接收;1,接收.

extern u8  USART1_RX_BUF[USART1_MAX_RECV_LEN]; 		//接收缓冲,最大USART2_MAX_RECV_LEN字节
extern u8  USART1_TX_BUF[USART1_MAX_SEND_LEN]; 		//发送缓冲,最大USART2_MAX_SEND_LEN字节
extern vu16 USART1_RX_STA;   						//接收数据状态

void usart1_init(u32 bound);
#endif


