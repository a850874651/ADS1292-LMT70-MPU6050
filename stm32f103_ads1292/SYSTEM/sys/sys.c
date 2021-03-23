#include "sys.h"

//THUMBָ�֧�ֻ������
//�������·���ʵ��ִ�л��ָ��WFI  
void WFI_SET(void)
{
	__ASM volatile("wfi");		  
}
//�ر������ж�
void INTX_DISABLE(void)
{		  
	__ASM volatile("cpsid i");
}
//���������ж�
void INTX_ENABLE(void)
{
	__ASM volatile("cpsie i");		  
}
//����ջ����ַ
//addr:ջ����ַ
__asm void MSR_MSP(u32 addr) 
{
    MSR MSP, r0 			//set Main Stack value
    BX r14
}

/*************************************
���ܣ�����RCC��ʹ�ܸ�ʱ��
*************************************/
void RCC_Configuration()
{
	ErrorStatus HSEStartUpStatus ; //�ⲿ����ʱ�ӿ�����ʶ
	RCC_DeInit() ;                 //��λϵͳʱ��
	RCC_HSEConfig(RCC_HSE_ON) ;    //ʹ���ⲿ����ʱ��
	HSEStartUpStatus = RCC_WaitForHSEStartUp() ;//�ȴ�HSE����
	
	if( HSEStartUpStatus == SUCCESS)            
	{
		RCC_PLLConfig(RCC_PLLSource_HSE_Div1,RCC_PLLMul_9) ;  //PLLʱ��ԴΪHSEһ��Ƶ��Ȼ��PLL�ű�Ƶ
		RCC_PLLCmd(ENABLE) ;                 //ʹ��PLL
		
		while( RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET) ;//�ȴ�PLL�����ȶ�
		
		RCC_SYSCLKConfig( RCC_SYSCLKSource_PLLCLK) ;       //SYSCLKʱ��ԴΪPLL
		
		while( RCC_GetSYSCLKSource() != 0x08) ;              //�ȴ�PLL��ΪSYSCLKʱ��Դ
		
		RCC_HCLKConfig(RCC_SYSCLK_Div1) ;    //HCLKʱ��ԴΪϵͳʱ��һ��Ƶ
		RCC_PCLK2Config(RCC_HCLK_Div1) ;     //PCLK1ʱ��ԴΪHCLKһ��Ƶ
		RCC_PCLK1Config(RCC_HCLK_Div2) ;     //PCLK2ʱ��ԴΪHCLK����Ƶ
	}	
}
