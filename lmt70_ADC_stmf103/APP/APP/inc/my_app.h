/**
  ******************************************************************************
  * @file           : my_app.h
  * @brief          : 顶层应用程序头文件
  * @details        : 应用程序初始化应用程序函数。
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
#ifndef __MY_APP_H
#define __MY_APP_H	  

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/** @defgroup My_App My App
  * @{
  */
/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
/** @addtogroup My_App_Exported_Functions My App Exported Functions 
  * @{
  */

/** @brief  应用程序初始化函数
  * @details 初始化顶层应用程序
  * @retval None
  */
void my_app_init(void) ;

/** @brief  应用程序
  * @details 顶层应用程序
  * @retval None
  */
void my_app(void) ; 

/**
  * @}
  */
  
/**
  * @}
  */

#ifdef __cplusplus
}
#endif
  
#endif /* __MY_APP_H */


