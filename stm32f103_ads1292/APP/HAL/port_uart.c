/**
  ******************************************************************************
  * @file           : my_debug.c
  * @brief          : �Զ����debug��
  * @details        : �ض���print����ʵ����itm debug�µĵ�����Ϣ��ӡ����Ҫ��
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
  * ��������: ����NVIC���趨USART�����ж����ȼ�.
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ������
  */
void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure; 
	 /* Ƕ�������жϿ�������ѡ�� */  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	
   /* ����USARTΪ�ж�Դ */
	NVIC_InitStructure.NVIC_IRQChannel = USARTx_IRQn;	 
	 /* �������ȼ�Ϊ0 */
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	 /* �����ȼ�Ϊ1 */
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	 /* ʹ���ж� */
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	 /* ��ʼ������NVIC */
	NVIC_Init(&NVIC_InitStructure);
}

/**
  * ��������: ���ڲ�������.
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ����ʹ�ú궨�巽������������źţ����������ֲ��ֻҪ���޸�bsp_led.h
  *           �ļ���غ궨��Ϳ��Է����޸����š�
  */
void USARTx_Init(void)
{
  /* ����IOӲ����ʼ���ṹ����� */
  GPIO_InitTypeDef GPIO_InitStructure;
  /* ����USART��ʼ���ṹ����� */
	USART_InitTypeDef USART_InitStructure;
  
  /* ����NVIC���趨USART�����ж����ȼ� */
  NVIC_Configuration();
  
  /* ʹ��USARTʱ�� */
  USARTx_ClockCmd(USARTx_CLK,ENABLE);
  /* ʹ��USART����GPIOʱ�� */
  USARTx_GPIO_ClockCmd(USARTx_TX_CLK | USARTx_RX_CLK | RCC_APB2Periph_AFIO,ENABLE);
  
	/* ����USART����GPIO��ʼ�� */
	/* �趨USART���Ͷ�ӦIO��� */
	GPIO_InitStructure.GPIO_Pin =  USARTx_TX_PIN;
  /* �趨USART���Ͷ�ӦIOģʽ������������� */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  /* �趨USART���Ͷ�ӦIO�������ٶ� ��GPIO_Speed_50MHz */
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  /* ��ʼ��USART���Ͷ�ӦIO */
	GPIO_Init(USARTx_TX_PORT, &GPIO_InitStructure);    
  
	/* �趨USART���ն�ӦIO��� */
	GPIO_InitStructure.GPIO_Pin = USARTx_RX_PIN;
  /* �趨USART���Ͷ�ӦIOģʽ���������� */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  /* ����û�����¸�ֵ�ĳ�Աʹ���봮�ڷ�����ͬ���� */
  /* ��ʼ��USART���ն�ӦIO */
	GPIO_Init(USARTx_RX_PORT, &GPIO_InitStructure);	
			
	/* USART������������ */
  /* USART������:115200 */
	USART_InitStructure.USART_BaudRate = USARTx_BAUDRATE;
  /* USART�ֳ�(��Чλ)��8λ */
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  /* USARTֹͣλ��1λ */
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
  /* USARTУ��λ���� */
	USART_InitStructure.USART_Parity = USART_Parity_No ;
  /* USARTӲ������������(Ӳ���źſ��ƴ���ֹͣ)���� */
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	/* USART����ģʽʹ�ܣ�������պͷ��� */
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  /* ��ʼ��USART */
	USART_Init(USARTx, &USART_InitStructure);
  
	/* ʹ�ܽ����ж� */
  USART_ITConfig(USARTx, USART_IT_RXNE, ENABLE);	
  
  /* ���������ɱ�־ */
	USART_ClearFlag(USARTx, USART_FLAG_TC|USART_FLAG_TXE|USART_FLAG_RXNE);
  /* ʹ��USART */
	USART_Cmd(USARTx, ENABLE);
 
}

/**
  * ��������: ���ڷ���һ���ֽ����� 
  * �������: ch���������ַ�
  * �� �� ֵ: ��
  * ˵    ������
  */
void Usart_SendByte(uint8_t ch)
{
  /* ����һ���ֽ����ݵ�USART1 */
  USART_SendData(USARTx,ch);

  /* �ȴ�������� */
  while (USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET);	
}

/**
  * ��������: ���ڷ���ָ�����ȵ��ַ���
  * �������: str���������ַ���������
  *           strlen:ָ���ַ�������
  * �� �� ֵ: ��
  * ˵    ������
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
  * ��������: ���ڷ����ַ�����ֱ�������ַ���������
  * �������: str���������ַ���������
  * �� �� ֵ: ��
  * ˵    ������
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






