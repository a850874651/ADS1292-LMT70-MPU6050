#include "sys.h"
#include "usart2.h"	  


void USART2_Init(void)
{
  /* ����IOӲ����ʼ���ṹ����� */
  GPIO_InitTypeDef GPIO_InitStructure;
  /* ����USART��ʼ���ṹ����� */
	USART_InitTypeDef USART_InitStructure;
  
  /* ʹ��USARTʱ�� */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE) ;
  /* ʹ��USART����GPIOʱ�� */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO,ENABLE);
  
	/* ����USART����GPIO��ʼ�� */
	/* �趨USART���Ͷ�ӦIO��� */
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_2;
  /* �趨USART���Ͷ�ӦIOģʽ������������� */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  /* �趨USART���Ͷ�ӦIO�������ٶ� ��GPIO_Speed_50MHz */
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  /* ��ʼ��USART���Ͷ�ӦIO */
	GPIO_Init(GPIOA, &GPIO_InitStructure);    
  
	/* �趨USART���ն�ӦIO��� */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
  /* �趨USART���Ͷ�ӦIOģʽ���������� */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU ;
  /* ����û�����¸�ֵ�ĳ�Աʹ���봮�ڷ�����ͬ���� */
  /* ��ʼ��USART���ն�ӦIO */
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
			
	/* USART������������ */
  /* USART������:115200 */
	USART_InitStructure.USART_BaudRate = 115200;
  /* USART�ֳ�(��Чλ)��8λ */
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  /* USARTֹͣλ��1λ */
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
  /* USARTУ��λ���� */
	USART_InitStructure.USART_Parity = USART_Parity_No ;
  /* USARTӲ������������(Ӳ���źſ��ƴ���ֹͣ)���� */
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	/* USART����ģʽʹ�ܣ�������պͷ��� */
  USART_InitStructure.USART_Mode = USART_Mode_Tx;
  /* ��ʼ��USART */
	USART_Init(USART2, &USART_InitStructure);
  
  /* ʹ��USART */
	USART_Cmd(USART2, ENABLE);
 /* ���������ɱ�־ */
	USART_ClearFlag(USART2, USART_FLAG_TC|USART_FLAG_TXE) ;
}

void Usart2_SendByte(uint8_t ch)
{
  /* ����һ���ֽ����ݵ�USART1 */
  USART_SendData(USART2,ch);

  /* �ȴ�������� */
  while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);	
}

/**
  * ��������: ���ڷ���ָ�����ȵ��ַ���
  * �������: str���������ַ���������
  *           strlen:ָ���ַ�������
  * �� �� ֵ: ��
  * ˵    ������
  */
void Usart2_SendStr_length(uint8_t *str,uint32_t strlen)
{
  unsigned int k=0;
  do 
  {
    Usart2_SendByte(*(str + k));
    k++;
  } while(k < strlen);
}

uint8_t get_ecg_rep_from_rxbuf( uint8_t *rxbuf,int32_t *rep, int32_t *ecg, int16_t rxlength)
{
    uint8_t rev = 0 ;
    int16_t i,j ;
    
    if ( ( rxbuf[0] == 0xaa) && ( rxbuf[1] == 0xaa))    /* ���ж�һ�������Ƿ���ȷ */
    {
        rev = 1 ;   /* ��ȷ����1 */
        
        for ( i = 0,j = 0; i < rxlength; i+=10,j++)
        {
            rep[j] = ( (int32_t)rxbuf[i+2] << 24) ;     /* ƴ�Ӻ������� */
            rep[j] |= ( (int32_t)rxbuf[i+3] << 16) ;
            rep[j] |= ( (int32_t)rxbuf[i+4] << 8) ;
            rep[j] |= ( (int32_t)rxbuf[i+5] << 0) ;
                       
            ecg[j] = ( (int32_t)rxbuf[i+6] << 24) ;   /* ƴ���ĵ����� */
            ecg[j] |= ( (int32_t)rxbuf[i+7] << 16) ;
            ecg[j] |= ( (int32_t)rxbuf[i+8] << 8) ;
            ecg[j] |= ( (int32_t)rxbuf[i+9] << 0) ;
        }
    }
    
    return rev ;
}