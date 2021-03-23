/**
  ******************************************************************************
  * @file           : my_app.h
  * @brief          : ����Ӧ�ó���ͷ�ļ�
  * @details        : Ӧ�ó����ʼ��Ӧ�ó�������
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

/** @brief  Ӧ�ó����ʼ������
  * @details ��ʼ������Ӧ�ó���
  * @retval None
  */
void my_app_init(void) ;

/** @brief  Ӧ�ó���
  * @details ����Ӧ�ó���
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


