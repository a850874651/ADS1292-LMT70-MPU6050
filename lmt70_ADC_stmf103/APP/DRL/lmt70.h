/**
  ******************************************************************************
  * @file           : lmt70.c
  * @brief          : lmt70负温度系数电压输出型温度传感器驱动源文件
  * @details        : lmt70的初始化和电压到温度的转换输出
  * @author         : WJXZZZ
  * @date           : 2020/9/2
  * @version        : V0.1
  * @copyright      : Copyright (C) 
  ******************************************************************************
  * @attention
  * -不依赖于具体硬件，通过调用个底层接口实现功能。
  * -手册上提供了三种电压-温度转换方式分别是一阶导数查表法，二阶导数公式法、三阶导数公式法
  * 一阶导数查表法适用于人体窄温度范围的温度测量，二阶和三阶公式法在宽温度范围-50度到100+度
  * 提供全局更准确的转换。
  * -对于没有fpu单元的mcu和人体温度测温范围的应用我们推荐使用一阶导数查表法。
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
#ifndef __LMT70_H
#define __LMT70_H	  

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "port_typ.h"

/** @defgroup ADS1292R ADS1292R
  * @{
  */
/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
/** @addtogroup ADS1292R_Exported_Functions ADS1292R Exported Functions 
  * @{
  */

/** @brief  初始化lmt70
  * @details 完成与lmt70相关的底层外设的初始化。例如adc，gpio。
  * @retval NONE
  */
void lmt70_init(void) ;

/** @brief  从lmt70获取温度数据
  * @details 使用一阶导数查表法实现电压-温度转换
  * @param[in]  vol lmt70输出电压
  * @retval 电压-温度转换结果放大100倍 -5000到+15000度
  */
int32_t lmt70_get_temp( float vol) ;

/**
  * @}
  */
  
/**
  * @}
  */

#ifdef __cplusplus
}
#endif
  
#endif /* __LMT70_H */



