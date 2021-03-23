/**
  ******************************************************************************
  * @file           : port_spi.c
  * @brief          : �ṩ��ds1302��spi�ӿ���
  * @details        : ��ֲʱ��Ҫ���ݾ���Ӳ��ʵ��spi��ʼ���Ͷ�д�ӿ�
  * @author         : 
  * @date           : 2020/9/2
  * @version        : V0.1
  * @copyright      : Copyright (C) 
  ******************************************************************************
  * @attention
  * Ӳ��ƽ̨ stm32f103c8t6
  * ���ƽ̨ keil 5  
  *
  * -�ð汾ʹ��hal��ʵ��
  ******************************************************************************
  * @verbatim
  * �޸���ʷ:    
  *      1. ���ڣ�2020/9/2
  *         ���ߣ�Charmander
  *         �޸ģ�
  * @endverbatim
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "port_spi.h"

/** @addtogroup Port_Spi
  * @{
  */
/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/

/* spi��ʼ�� */ 
void port_spi_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;   
	SPI_InitTypeDef SPI_InitStructure;	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_SPI1, ENABLE) ; 
	
	/* SCK  PA5��MISO  PA6��MOSI  PA7 */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;                                                                                                   
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;   
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;    
    GPIO_Init(GPIOA,&GPIO_InitStructure);              
				
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  /* ˫��˫��ȫ˫�� */
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;                       /* ����Ϊ��SPI */
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b; 		            /* SPI����8bit���� */
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low; 					        /* SCLK����Ϊ�ͣ��������������� */
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge; 					    /* �ڶ���ʱ�������ݱ����� */
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;							/* Ƭѡ��������� */
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32;  /* ʱ�ӷ�Ƶ72M/x */ 
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB; 		            /* ��λ��ǰ */
	SPI_InitStructure.SPI_CRCPolynomial = 7; 							/* CRC����ֵ�Ķ���ʽ */
	SPI_Init(SPI1,&SPI_InitStructure); 	
	SPI_Cmd(SPI1,ENABLE);                                               /* ʹ��SPI���� */
}

/* spiȫ˫����д */
uint8_t port_spi_transmit_receive ( uint8_t tx)
{   
	uint8_t retry = 0 ;			
    
	while ( SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET) /* ���ָ����SPI��־λ�������:���ͻ���ձ�־λ */
    {
        retry++ ;
        if ( retry > 200)
            return 0 ;
    }	
    
	SPI_I2S_SendData(SPI1, tx) ; /* ͨ������SPIx����һ������ */
	retry = 0 ;

	while ( SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET) /* ���ָ����SPI��־λ�������:���ܻ���ǿձ�־λ */
    {
        retry++ ;
        if ( retry > 200)
            return 0 ;
    }	  
        
	return SPI_I2S_ReceiveData(SPI1) ; /* ����ͨ��SPIx������յ����� */	
}


/**
  * @}
  */

