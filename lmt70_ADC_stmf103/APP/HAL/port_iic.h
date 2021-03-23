/**
  ******************************************************************************
  * @file           : port_iic.h
  * @brief          : iic驱动头文件
  * @details        : 软件模拟iic
  * @author         : WJXZZZ
  * @date           : 2020/8/23
  * @version        : V0.1
  * @copyright      : Copyright (C) 
  ******************************************************************************
  * @attention      
  * NONE
  ******************************************************************************
  * @verbatim
  * 修改历史:    
  *      1. 日期：2020/8/23
  *         作者：Charmander
  *         修改：
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

/** @brief  初始化iic
  * @details 初始化软件iic
  * @retval NONE
  */ 
void iic_init (void) ;

/** @brief  iic主机写数据
  * @details 向指定从设备的寄存器写入一定数量的数据
  * @param[in]  dev  从设备号
  * @param[in]  reg  寄存器地址
  * @param[in]  str  指向带写入数据的指针
  * @param[in]  length  数据长度
  * @param[in]  timeout 单个数据写入的超时时间
  * @retval 
  * -0 写成功
  * -other 第i个字符写入时出错
  */ 
uint8_t iic_master_transmit ( uint8_t dev, uint8_t reg, uint8_t *str, uint16_t length, uint32_t timeout) ;

/** @brief  iic主机读数据
  * @details 从指定从设备的寄存器读出一定数量的数据
  * @param[in]  dev  从设备号
  * @param[in]  reg  寄存器地址
  * @param[in]  str  接收数据指针
  * @param[in]  length  数据长度
  * @param[in]  timeout 单个数据读取的超时时间
  * @retval 
  * -0 写成功
  * -other 第i个字符写入时出错
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



















