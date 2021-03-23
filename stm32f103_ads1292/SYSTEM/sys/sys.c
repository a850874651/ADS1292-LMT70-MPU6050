#include "sys.h"

//THUMB指令不支持汇编内联
//采用如下方法实现执行汇编指令WFI  
void WFI_SET(void)
{
	__ASM volatile("wfi");		  
}
//关闭所有中断
void INTX_DISABLE(void)
{		  
	__ASM volatile("cpsid i");
}
//开启所有中断
void INTX_ENABLE(void)
{
	__ASM volatile("cpsie i");		  
}
//设置栈顶地址
//addr:栈顶地址
__asm void MSR_MSP(u32 addr) 
{
    MSR MSP, r0 			//set Main Stack value
    BX r14
}

/*************************************
功能：设置RCC，使能各时钟
*************************************/
void RCC_Configuration()
{
	ErrorStatus HSEStartUpStatus ; //外部高速时钟开启标识
	RCC_DeInit() ;                 //复位系统时钟
	RCC_HSEConfig(RCC_HSE_ON) ;    //使能外部高速时钟
	HSEStartUpStatus = RCC_WaitForHSEStartUp() ;//等待HSE起振
	
	if( HSEStartUpStatus == SUCCESS)            
	{
		RCC_PLLConfig(RCC_PLLSource_HSE_Div1,RCC_PLLMul_9) ;  //PLL时钟源为HSE一分频，然后PLL九倍频
		RCC_PLLCmd(ENABLE) ;                 //使能PLL
		
		while( RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET) ;//等待PLL起振并稳定
		
		RCC_SYSCLKConfig( RCC_SYSCLKSource_PLLCLK) ;       //SYSCLK时钟源为PLL
		
		while( RCC_GetSYSCLKSource() != 0x08) ;              //等待PLL成为SYSCLK时钟源
		
		RCC_HCLKConfig(RCC_SYSCLK_Div1) ;    //HCLK时钟源为系统时钟一分频
		RCC_PCLK2Config(RCC_HCLK_Div1) ;     //PCLK1时钟源为HCLK一分频
		RCC_PCLK1Config(RCC_HCLK_Div2) ;     //PCLK2时钟源为HCLK二分频
	}	
}
