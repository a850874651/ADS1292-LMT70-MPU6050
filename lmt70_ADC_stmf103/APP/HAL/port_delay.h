/**
  ******************************************************************************
  * @file           : port_delay.h
  * @brief          : �����ʱ
  * @details        : ΢����ʱ
  * @author         : WJXZZZ
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
#ifndef __PORT_DELAY_H
#define __PORT_DELAY_H	  

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "port_typ.h"

/** @defgroup Port_Delay Port Delay
  * @{
  */
/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
/** @addtogroup Port_Delay_Exported_Functions Port Delay Exported Functions 
  * @{
  */

/** @brief  ΢����ʱ
  * @details ��ʱnus,nusΪҪ��ʱ��us��
  * @retval None
  */
void port_delay_us( uint32_t us) ;

/** @brief  ������ʱ
  * @details ע��ms�ķ�Χ,SysTick->LOADΪ24λ�Ĵ���,
  * ����,�����ʱΪ:nms<=0xffffff*8*1000/SYSCLK,
  * SYSCLK��λΪHz,nms��λΪms��72M������,nms<=1864 
  * @retval None
  */
void port_delay_ms( uint32_t ms) ;

/**
  * @}
  */
  
/**
  * @}
  */

#ifdef __cplusplus
}
#endif
  
#endif /* __PORT_DELAY_H */



