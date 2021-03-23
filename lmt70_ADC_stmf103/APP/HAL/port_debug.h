/**
  ******************************************************************************
  * @file           : port_debug.h
  * @brief          : 自定义的debug库
  * @details        : 重定向print函数实调试信息打印。需要在
  *                   sys_config.h中通过MY_DEBUG_USE_PR和PRINT_LEVEL宏设置
  *                   调试信息输出开关和级别。
  * @author         : WJXZZZ
  * @date           : 2020/6/13
  * @version        : V0.1
  * @copyright      : Copyright (C) 
  ******************************************************************************
  * @attention      
  * 硬件平台：有jlink接口的stm32单片机
  * 软件平台：KEIL V5
  ******************************************************************************
  * @verbatim
  * 修改历史:    
  *      1. 日期：2020/6/13
  *         作者：Charmander
  *         修改：
  * @endverbatim
  ******************************************************************************
  */

#ifndef __PORT_DEBUG_H__
#define __PORT_DEBUG_H__

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "port_typ.h"

/* Exported constants --------------------------------------------------------*/
/** @defgroup 调试输出
  * @{
  */  
  
/** @defgroup 调试输出级别宏
  * @{
  */ 
#define NONE    0   /*!< 不输出                    */
#define ERROR   1   /*!< 错误及以上输出            */
#define WARN    2   /*!< 警告及以上输出            */
#define INFO    3   /*!< 信息及以上输出            */
#define ENTRY   4   /*!< ENTRY及以上输出           */
#define DEBUG   5   /*!< 调试及以上输出            */
/**
  * @}
  */

#define MY_DEBUG_USE_PR 1        /*!< 1开启调试接口，0关闭调试接口      */
#define PRINT_LEVEL     DEBUG    /*!< DEBUG及以上级别输出               */
  
/**
  * @}
  */

/*
 * 将变量名转成字符串的宏定义函数
 * #是宏定义中转换字符串的用法
 */
#define name2str(name) (#name)

/* 必须定义PRINT_LEVEL宏定义，否则编译阶段就直接报错退出 */
#ifndef PRINT_LEVEL
#   error MUST Define PRINT_LEVEL!
#endif

/* Exported types ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
/*
 * 调试输出接口
 *
 * 备注：还有另外一种方法，用一个缓存使用snprintf实现，这样既可以控制
 *       输出，还可以方便存日志，这种方法后续再做
 *
 * tag       调试级别
 * tagstr    调试级别字符串
 * fmt, ...  printf的可变参数
 */
int pr(int tag, char *tagstr, char *fmt, ...);

#if MY_DEBUG_USE_PR
/** @addtogroup 调试输出
  * @{
  */
/** @defgroup 调试输出接口
  * @brief 各级别打印函数
  * @{
  */
  
/** @brief  错误级别输出
  * @param[in]  ...     输出内容
  * @retval None
  */  
#define pr_err(...)     pr(ERROR, name2str(ERROR), __VA_ARGS__)
/** @brief  警告级别输出
  * @param[in]  ...     输出内容
  * @retval None
  */      
#define pr_warn(...)    pr(WARN, name2str(WARN), __VA_ARGS__)

/** @brief  信息级别输出
  * @param[in]  ...     输出内容
  * @retval None
  */  
#define pr_info(...)    pr(INFO, name2str(INFO), __VA_ARGS__)

/** @brief  entry级别输出
  * @param[in]  ...     输出内容
  * @retval None
  */  
#define pr_entry(inout) \
    pr(ENTRY, name2str(ENTRY), "%s() %s", __func__, #inout)
    
/** @brief  调试级别输出
  * @param[in]  ...     输出内容
  * @retval None
  */      
#define pr_debug(...)   pr(DEBUG, name2str(DEBUG), __VA_ARGS__)
/**
  * @}
  */
/**
  * @}
  */
#else
#define pr_err(...)     ;
#define pr_warn(...)    ;
#define pr_info(...)    ;
#define pr_entry(inout) ;
#define pr_debug(...)   ;
#endif

#endif /* __PORT_DEBUG_H__ */


