/**
  ******************************************************************************
  * @file           : port_delay.h
  * @brief          : 软件延时
  * @details        : 微妙延时
  * @author         : WJXZZZ
  * @date           : 2020/9/2
  * @version        : V0.1
  * @copyright      : Copyright (C) 
  ******************************************************************************
  * @attention      
  * NONE
  ******************************************************************************
  * @verbatim
  * 修改历史:    
  *      1. 日期：2020/9/2
  *         作者：Charmander
  *         修改：
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

/** @brief  微妙延时
  * @details 延时nus,nus为要延时的us数
  * @retval None
  */
void port_delay_us( uint32_t us) ;

/** @brief  毫秒延时
  * @details 注意ms的范围,SysTick->LOAD为24位寄存器,
  * 所以,最大延时为:nms<=0xffffff*8*1000/SYSCLK,
  * SYSCLK单位为Hz,nms单位为ms对72M条件下,nms<=1864 
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



