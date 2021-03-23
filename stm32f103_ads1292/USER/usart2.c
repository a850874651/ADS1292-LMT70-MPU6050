#include "sys.h"
#include "usart2.h"	  


void USART2_Init(void)
{
  /* 定义IO硬件初始化结构体变量 */
  GPIO_InitTypeDef GPIO_InitStructure;
  /* 定义USART初始化结构体变量 */
	USART_InitTypeDef USART_InitStructure;
  
  /* 使能USART时钟 */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE) ;
  /* 使能USART功能GPIO时钟 */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO,ENABLE);
  
	/* 调试USART功能GPIO初始化 */
	/* 设定USART发送对应IO编号 */
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_2;
  /* 设定USART发送对应IO模式：复用推挽输出 */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  /* 设定USART发送对应IO最大操作速度 ：GPIO_Speed_50MHz */
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  /* 初始化USART发送对应IO */
	GPIO_Init(GPIOA, &GPIO_InitStructure);    
  
	/* 设定USART接收对应IO编号 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
  /* 设定USART发送对应IO模式：浮空输入 */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU ;
  /* 其他没有重新赋值的成员使用与串口发送相同配置 */
  /* 初始化USART接收对应IO */
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
			
	/* USART工作环境配置 */
  /* USART波特率:115200 */
	USART_InitStructure.USART_BaudRate = 115200;
  /* USART字长(有效位)：8位 */
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  /* USART停止位：1位 */
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
  /* USART校验位：无 */
	USART_InitStructure.USART_Parity = USART_Parity_No ;
  /* USART硬件数据流控制(硬件信号控制传输停止)：无 */
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	/* USART工作模式使能：允许接收和发送 */
  USART_InitStructure.USART_Mode = USART_Mode_Tx;
  /* 初始化USART */
	USART_Init(USART2, &USART_InitStructure);
  
  /* 使能USART */
	USART_Cmd(USART2, ENABLE);
 /* 清除发送完成标志 */
	USART_ClearFlag(USART2, USART_FLAG_TC|USART_FLAG_TXE) ;
}

void Usart2_SendByte(uint8_t ch)
{
  /* 发送一个字节数据到USART1 */
  USART_SendData(USART2,ch);

  /* 等待发送完毕 */
  while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);	
}

/**
  * 函数功能: 串口发送指定长度的字符串
  * 输入参数: str：待发送字符串缓冲器
  *           strlen:指定字符串长度
  * 返 回 值: 无
  * 说    明：无
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
    
    if ( ( rxbuf[0] == 0xaa) && ( rxbuf[1] == 0xaa))    /* 简单判断一下数据是否正确 */
    {
        rev = 1 ;   /* 正确返回1 */
        
        for ( i = 0,j = 0; i < rxlength; i+=10,j++)
        {
            rep[j] = ( (int32_t)rxbuf[i+2] << 24) ;     /* 拼接呼吸数据 */
            rep[j] |= ( (int32_t)rxbuf[i+3] << 16) ;
            rep[j] |= ( (int32_t)rxbuf[i+4] << 8) ;
            rep[j] |= ( (int32_t)rxbuf[i+5] << 0) ;
                       
            ecg[j] = ( (int32_t)rxbuf[i+6] << 24) ;   /* 拼接心电数据 */
            ecg[j] |= ( (int32_t)rxbuf[i+7] << 16) ;
            ecg[j] |= ( (int32_t)rxbuf[i+8] << 8) ;
            ecg[j] |= ( (int32_t)rxbuf[i+9] << 0) ;
        }
    }
    
    return rev ;
}