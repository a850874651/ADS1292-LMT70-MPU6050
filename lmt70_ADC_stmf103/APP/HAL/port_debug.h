/**
  ******************************************************************************
  * @file           : port_debug.h
  * @brief          : �Զ����debug��
  * @details        : �ض���print����ʵ������Ϣ��ӡ����Ҫ��
  *                   sys_config.h��ͨ��MY_DEBUG_USE_PR��PRINT_LEVEL������
  *                   ������Ϣ������غͼ���
  * @author         : WJXZZZ
  * @date           : 2020/6/13
  * @version        : V0.1
  * @copyright      : Copyright (C) 
  ******************************************************************************
  * @attention      
  * Ӳ��ƽ̨����jlink�ӿڵ�stm32��Ƭ��
  * ���ƽ̨��KEIL V5
  ******************************************************************************
  * @verbatim
  * �޸���ʷ:    
  *      1. ���ڣ�2020/6/13
  *         ���ߣ�Charmander
  *         �޸ģ�
  * @endverbatim
  ******************************************************************************
  */

#ifndef __PORT_DEBUG_H__
#define __PORT_DEBUG_H__

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "port_typ.h"

/* Exported constants --------------------------------------------------------*/
/** @defgroup �������
  * @{
  */  
  
/** @defgroup ������������
  * @{
  */ 
#define NONE    0   /*!< �����                    */
#define ERROR   1   /*!< �����������            */
#define WARN    2   /*!< ���漰�������            */
#define INFO    3   /*!< ��Ϣ���������            */
#define ENTRY   4   /*!< ENTRY���������           */
#define DEBUG   5   /*!< ���Լ��������            */
/**
  * @}
  */

#define MY_DEBUG_USE_PR 1        /*!< 1�������Խӿڣ�0�رյ��Խӿ�      */
#define PRINT_LEVEL     DEBUG    /*!< DEBUG�����ϼ������               */
  
/**
  * @}
  */

/*
 * ��������ת���ַ����ĺ궨�庯��
 * #�Ǻ궨����ת���ַ������÷�
 */
#define name2str(name) (#name)

/* ���붨��PRINT_LEVEL�궨�壬�������׶ξ�ֱ�ӱ����˳� */
#ifndef PRINT_LEVEL
#   error MUST Define PRINT_LEVEL!
#endif

/* Exported types ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
/*
 * ��������ӿ�
 *
 * ��ע����������һ�ַ�������һ������ʹ��snprintfʵ�֣������ȿ��Կ���
 *       ����������Է������־�����ַ�����������
 *
 * tag       ���Լ���
 * tagstr    ���Լ����ַ���
 * fmt, ...  printf�Ŀɱ����
 */
int pr(int tag, char *tagstr, char *fmt, ...);

#if MY_DEBUG_USE_PR
/** @addtogroup �������
  * @{
  */
/** @defgroup ��������ӿ�
  * @brief �������ӡ����
  * @{
  */
  
/** @brief  ���󼶱����
  * @param[in]  ...     �������
  * @retval None
  */  
#define pr_err(...)     pr(ERROR, name2str(ERROR), __VA_ARGS__)
/** @brief  ���漶�����
  * @param[in]  ...     �������
  * @retval None
  */      
#define pr_warn(...)    pr(WARN, name2str(WARN), __VA_ARGS__)

/** @brief  ��Ϣ�������
  * @param[in]  ...     �������
  * @retval None
  */  
#define pr_info(...)    pr(INFO, name2str(INFO), __VA_ARGS__)

/** @brief  entry�������
  * @param[in]  ...     �������
  * @retval None
  */  
#define pr_entry(inout) \
    pr(ENTRY, name2str(ENTRY), "%s() %s", __func__, #inout)
    
/** @brief  ���Լ������
  * @param[in]  ...     �������
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


