/**
  ******************************************************************************
  * @file           : port_spi.h
  * @brief          : 提供给ds1302的spi接口
  * @details        : 移植时需要根据具体硬件实现spi初始化和读写接口
  * @author         :  
  * @date           : 2020/9/2
  * @version        : V0.1
  * @copyright      : Copyright (C) 
  ******************************************************************************
  * @attention
  * 硬件平台 stm32f103c8t6
  * 软件平台 keil 5  
  *
  * -该版本使用hal库实现
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

/** @brief  spi初始化
  * @details 初始化spi
  * @retval NONE
  */ 
void port_spi_init(void) ;

/** @brief  spi读写
  * @details  全双工读写  
  * @param[in]  tx  待发送数据
  * @retval 读回来的数据
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





