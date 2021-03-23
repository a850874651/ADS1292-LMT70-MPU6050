/**
  ******************************************************************************
  * @file           : port_gpio.h
  * @brief          : Ϊads1292�ṩcs��start��rest��drdy���ĸ�gpio���ŵĽӿں���
  * @details        : Ӧ�ó����ʼ��Ӧ�ó�������
  * @author         :  
  * @date           : 2020/9/2
  * @version        : V0.1
  * @copyright      : Copyright (C) 
  ******************************************************************************
  * @attention      
  * NONE
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
#ifndef __PORT_GPIO_H
#define __PORT_GPIO_H	  

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "port_typ.h"

#include "sys.h"

/** @defgroup PORT_GPIO PORT GPIO
  * @{
  */
/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* �ڴ�ʵ��cs��start��rest��drdy���ĸ�gpio���ŵĿ��ƽӿں� */
#define ADS1292_CS_SET()            PAout(4) = 1
#define ADS1292_CS_RESET()          PAout(4) = 0    
#define ADS1292_START_SET()         PBout(0) = 1
#define ADS1292_START_RESET()       PBout(0) = 0
#define ADS1292_REST_SET()          PBout(1) = 1
#define ADS1292_REST_RESET()        PBout(1) = 0
#define ADS1292_DRDY_GET()          PBin(10)

/* Exported functions --------------------------------------------------------*/
/** @addtogroup Port_Gpio_Exported_Functions Port Gpio Exported Functions 
  * @{
  */

/** @brief  ΢����ʱ
  * @details 
  * @retval None
  */
void port_gpio_init(void) ;
/**
  * @}
  */
  
/**
  * @}
  */

#ifdef __cplusplus
}
#endif
  
#endif /* __PORT_GPIO_H */




