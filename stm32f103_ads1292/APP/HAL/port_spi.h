/**
  ******************************************************************************
  * @file           : port_spi.h
  * @brief          : �ṩ��ds1302��spi�ӿ�
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __PORT_SPI_H
#define __PORT_SPI_H	  

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "port_typ.h"

/** @defgroup Port_Spi Port Spi
  * @{
  */
/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
/** @addtogroup Port_Spi_Exported_Functions Port Spi Exported Functions 
  * @{
  */

/** @brief  spi��ʼ��
  * @details ��ʼ��spi
  * @retval NONE
  */ 
void port_spi_init(void) ;

/** @brief  spi��д
  * @details  ȫ˫����д  
  * @param[in]  tx  ����������
  * @retval ������������
  */
uint8_t port_spi_transmit_receive ( uint8_t tx) ;

/**
  * @}
  */
  
/**
  * @}
  */

#ifdef __cplusplus
}
#endif
  
#endif /* __PORT_SPI_H */





