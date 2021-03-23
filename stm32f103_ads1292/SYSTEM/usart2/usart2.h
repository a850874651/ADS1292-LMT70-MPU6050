#ifndef __USART2_H
#define __USART2_H
#include "stdio.h"	
#include "sys.h" 

#define USART2_MAX_RECV_LEN		50					//最大接收缓存字节数
#define USART2_MAX_SEND_LEN		50					//最大发送缓存字节数
#define USART2_RX_EN 			1								//0,不接收;1,接收.

extern u8  USART2_RX_BUF[USART2_MAX_RECV_LEN]; 		//接收缓冲,最大USART2_MAX_RECV_LEN字节
extern u8  USART2_TX_BUF[USART2_MAX_SEND_LEN]; 		//发送缓冲,最大USART2_MAX_SEND_LEN字节
extern vu16 USART2_RX_STA;   						//接收数据状态

void USART2_Init(void);
void Usart2_SendByte(uint8_t ch);
void Usart2_SendStr_length(uint8_t *str,uint32_t strlen);
uint8_t get_ecg_rep_from_rxbuf( uint8_t *rxbuf,int32_t *rep, int32_t *ecg, int16_t rxlength);

extern	void USART2_Init(void);
extern	void Usart2_SendByte(uint8_t ch);
extern  void Usart2_SendStr_length(uint8_t *str,uint32_t strlen);
extern  uint8_t get_ecg_rep_from_rxbuf( uint8_t *rxbuf,int32_t *rep, int32_t *ecg, int16_t rxlength);
#endif
