#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "sys.h" 

#define USART1_MAX_RECV_LEN		50					//�����ջ����ֽ���
#define USART1_MAX_SEND_LEN		50					//����ͻ����ֽ���
#define USART1_RX_EN 			1								//0,������;1,����.

extern u8  USART1_RX_BUF[USART1_MAX_RECV_LEN]; 		//���ջ���,���USART2_MAX_RECV_LEN�ֽ�
extern u8  USART1_TX_BUF[USART1_MAX_SEND_LEN]; 		//���ͻ���,���USART2_MAX_SEND_LEN�ֽ�
extern vu16 USART1_RX_STA;   						//��������״̬

void usart1_init(u32 bound);
#endif


