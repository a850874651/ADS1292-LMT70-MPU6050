#include "sys.h"
#include "usart.h"	  

//串口接收缓存区 	
u8 USART1_RX_BUF[USART1_MAX_RECV_LEN]; 				//接收缓冲,最大USART2_MAX_RECV_LEN个字节.
u8 USART1_TX_BUF[USART1_MAX_SEND_LEN]; 


//通过判断接收连续2个字符之间的时间差不大于10ms来决定是不是一次连续的数据.
//如果2个字符接收间隔超过10ms,则认为不是1次连续数据.也就是超过10ms没有接收到
//任何数据,则表示此次接收完毕.
//接收到的数据状态
//[15]:0,没有接收到数据;1,接收到了一批数据.
//[14:0]:接收到的数据长度
vu16 USART1_RX_STA=0;

void USART1_IRQHandler(void)
{
 				 											 
}

//初始化IO 串口2
//pclk1:PCLK1时钟频率(Mhz)
//bound:波特率 
void usart1_init(u32 bound)
{  	 
	GPIO_InitTypeDef  GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef  NVIC_InitStructure;

	/*使能USART1和GPIOA外设时钟*/  
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);	

	/*复位串口1*/
	USART_DeInit(USART1);  

	/*USART1_GPIO初始化设置*/ 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;			//USART1_TXD(PA.9)     
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		//复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//设置引脚输出最大速率为50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);				//调用库函数中的GPIO初始化函数，初始化USART1_TXD(PA.9)  


	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;				//USART1_RXD(PA.10)
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	//浮空输入
	GPIO_Init(GPIOA, &GPIO_InitStructure);					//调用库函数中的GPIO初始化函数，初始化USART1_RXD(PA.10)


	/*USART1 初始化设置*/
	USART_InitStructure.USART_BaudRate = bound;										//设置波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;						//8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;							//1个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;								//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;					//工作模式设置为收发模式
	USART_Init(USART1, &USART_InitStructure);										//初始化串口1

	/*Usart1 NVIC配置*/
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;	//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;		//从优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);							//根据指定的参数初始化VIC寄存器 

	//USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);			//使能串口1接收中断
	
	USART_Cmd(USART1, ENABLE);                    			//使能串口 
	USART_ClearFlag(USART1, USART_FLAG_TC);					//清除发送完成标志
	USART1_RX_STA=0;							//清零
}

