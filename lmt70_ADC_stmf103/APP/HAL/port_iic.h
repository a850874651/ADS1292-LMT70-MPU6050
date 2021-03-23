/**
  ******************************************************************************
  * @file           : port_iic.h
  * @brief          : iic����ͷ�ļ�
  * @details        : ���ģ��iic
  * @author         : WJXZZZ
  * @date           : 2020/8/23
  * @version        : V0.1
  * @copyright      : Copyright (C) 
  ******************************************************************************
  * @attention      
  * NONE
  ******************************************************************************
  * @verbatim
  * �޸���ʷ:    
  *      1. ���ڣ�2020/8/23
  *         ���ߣ�Charmander
  *         �޸ģ�
  * @endverbatim
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __PORT_IIC_H
#define __PORT_IIC_H	  

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "port_typ.h"

/** @defgroup Port_IIC Port IIC
  * @{
  */
/* Exported constants --------------------------------------------------------*/
  
/* Exported types ------------------------------------------------------------*/
  
/* Exported macro ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
/** @addtogroup Port_IIC_Exported_Functions Port IIC Exported Functions 
  * @{
  */

/** @brief  ��ʼ��iic
  * @details ��ʼ�����iic
  * @retval NONE
  */ 
void iic_init (void) ;

/** @brief  iic����д����
  * @details ��ָ�����豸�ļĴ���д��һ������������
  * @param[in]  dev  ���豸��
  * @param[in]  reg  �Ĵ�����ַ
  * @param[in]  str  ָ���д�����ݵ�ָ��
  * @param[in]  length  ���ݳ���
  * @param[in]  timeout ��������д��ĳ�ʱʱ��
  * @retval 
  * -0 д�ɹ�
  * -other ��i���ַ�д��ʱ����
  */ 
uint8_t iic_master_transmit ( uint8_t dev, uint8_t reg, uint8_t *str, uint16_t length, uint32_t timeout) ;

/** @brief  iic����������
  * @details ��ָ�����豸�ļĴ�������һ������������
  * @param[in]  dev  ���豸��
  * @param[in]  reg  �Ĵ�����ַ
  * @param[in]  str  ��������ָ��
  * @param[in]  length  ���ݳ���
  * @param[in]  timeout �������ݶ�ȡ�ĳ�ʱʱ��
  * @retval 
  * -0 д�ɹ�
  * -other ��i���ַ�д��ʱ����
  */ 
uint8_t iic_master_receive ( uint8_t dev, uint8_t reg, uint8_t *str, uint16_t length, uint32_t timeout) ;


/**
  * @}
  */
  
/**
  * @}
  */

#ifdef __cplusplus
}
#endif
  
#endif /* __PORT_IIC_H */



















