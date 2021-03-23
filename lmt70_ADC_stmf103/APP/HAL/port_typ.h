/**
  ******************************************************************************
  * @file           : port_typ.h
  * @brief          : �Զ�����������
  * @details        : �ַ������͡�������
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
#ifndef __PORT_TYP_H
#define __PORT_TYP_H	  

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/** @defgroup Port_Typ  Port Typ
  * @{
  */
/* Exported types ------------------------------------------------------------*/
/** @addtogroup Port_Typ_Exported_types Port Typ Exported types 
  * @{
  */

#ifndef int8_t 
#define int8_t signed char 
#endif 

#ifndef int16_t 
#define int16_t signed short int 
#endif 

#ifndef int32_t 
#define int32_t signed int 
#endif 
  
#ifndef uint8_t 
#define uint8_t unsigned char 
#endif 

#ifndef uint16_t 
#define uint16_t unsigned short int 
#endif 

#ifndef uint32_t 
#define uint32_t unsigned int 
#endif 

/**
  * @}
  */
/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/

  
/**
  * @}
  */

#ifdef __cplusplus
}
#endif
  
#endif /* __PORT_TYP_H */
