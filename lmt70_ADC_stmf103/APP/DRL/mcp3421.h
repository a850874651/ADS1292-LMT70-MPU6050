/**
  ******************************************************************************
  * @file           : mcp3421.h
  * @brief          : mcp3421 18位分辨率 ΔΣ ADC adc驱动头文件
  * @details        : 需要调用底层iic接口
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
#ifndef __MCP3421_H__
#define __MCP3421_H__ 

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "port_typ.h"

/** @defgroup MCP3421 MCP3421
  * @{
  */
/* Exported types ------------------------------------------------------------*/

typedef enum						/* 增益 */
{
	gain1 = 0x00 ,                  
	gain2 = 0x01 ,
	gain4 = 0x02 ,
	gain8 = 0x03 
}mcp3421_gain_e ;

typedef enum						/* 转换速率 */
{
	rate12bit = 0x00 ,              /* 240SPS */
	rate14bit = 0x04 ,              /* 60SPS */
	rate16bit = 0x08 ,              /* 15SPS */
	rate18bit = 0x0C                /* 3.75SPS */
}mcp3421_rate_e ;

typedef enum						/* 转换模式 */
{
	oneshot_mode = 0x00 ,           /* 单次转换模式 */
	continuous_mode = 0x10 ,        /* 连续转换模式 */
}mcp3421_mode_e;

typedef enum						/* 转换标志位 */
{
	ready = 0x00 ,
	nready_or_start = 0x80 ,
}mcp3421_ready_e ;

/** @brief  mcp3421结构体
  * @details 
  * -address 地址 默认为 MCP3421_ADDR
  * -gain    增益 1、2、4、8 默认为1倍增益 @ref mcp3421_gain_e
  * -sampling_rate 采样率 240 SPS (12 bits)、60 SPS (14 bits)、
  * 15 SPS (16 bits)、默认3.75 SPS (18 bits) @ref mcp3421_rate_e
  *	-conversion_mode 转换模式   Continuous Conversion、 
  * 默认One-Shot Conversion @ref mcp3421_mode_e
  * -ready_flag 状态标志位 0表示转换结束数据待读取、
  * 1表示转换正在进行或启动单次转换 @ref mcp3421_ready_e
  * @retval None
  */
typedef struct
{
	uint8_t address ;
	
	uint8_t gain ;
	uint8_t sampling_rate ;
	uint8_t conversion_mode ;
	uint8_t ready_flag ;
}mcp3421_s ;

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/
#define MCP3421_ADDR 0x68

/* Exported functions --------------------------------------------------------*/

/** @brief  初始化mcp3421
  * @details 完成iic硬件初始化和mcp3421参数的基本配置
  * @param[in]  mcp mcp3421句柄
  * @retval NONE
  */ 
void mcp3421_init ( mcp3421_s* mcp) ;               					

/** @brief  修改mcp3421的增益
  * @details 在调用mcp3421_one_conversion函数时完成参数的正式写入
  * @param[in]  mcp mcp3421句柄
  * @param[in]  gain 增益 @ref mcp3421_gain_e
  * @retval NONE
  */ 
void mcp3421_write_gain ( mcp3421_s* mcp, uint8_t gain) ;			

/** @brief  修改mcp3421的采样率和分辨率
  * @details 在调用mcp3421_one_conversion函数时完成参数的正式写入
  * @param[in]  mcp mcp3421句柄
  * @param[in]  rate 采样率 @ref mcp3421_rate_e
  * @retval NONE
  */ 
void mcp3421_write_rate ( mcp3421_s* mcp, uint8_t rate) ;		

/** @brief  修改mcp3421的转换模式
  * @details 在调用mcp3421_one_conversion函数时完成参数的正式写入
  * @param[in]  mcp mcp3421句柄
  * @param[in]  mode 转换模式 @ref mcp3421_mode_e
  * @retval NONE
  */ 
void mcp3421_write_mode ( mcp3421_s* mcp, uint8_t mode) ;	

/** @brief  修改mcp3421的状态标志位
  * @details 在调用mcp3421_one_conversion函数时完成参数的正式写入
  * @param[in]  mcp mcp3421句柄
  * @param[in]  flag 状态标志 @ref mcp3421_ready_e
  * @retval NONE
  */ 
void mcp3421_write_flag ( mcp3421_s* mcp, uint8_t flag) ;			

/** @brief  读取mcp3421的增益
  * @details 
  * @param[in]  mcp mcp3421句柄
  * @retval 返回mcp3421的增益 @ref mcp3421_gain_e
  */ 
uint8_t mcp3421_read_gain ( mcp3421_s* mcp) ;			

/** @brief  读取mcp3421的采样率
  * @details 
  * @param[in]  mcp mcp3421句柄
  * @retval 返回mcp3421的增益 @ref mcp3421_rate_e
  */ 
uint8_t mcp3421_read_rate ( mcp3421_s* mcp) ;	

/** @brief  读取mcp3421的转换模式
  * @details 
  * @param[in]  mcp mcp3421句柄
  * @retval 返回mcp3421的增益 @ref mcp3421_mode_e
  */
uint8_t mcp3421_read_mode ( mcp3421_s* mcp) ;	

/** @brief  读取mcp3421的状态标志位
  * @details 
  * @param[in]  mcp mcp3421句柄
  * @retval 返回mcp3421的增益 @ref mcp3421_ready_e
  */
uint8_t mcp3421_read_flag ( mcp3421_s* mcp) ;		

/** @brief  设置mcp3421为单次转换并读取转换后的数据
  * @details 使用mcp中的参数配置mcap3421并开始单次转换
  * @param[in]  mcp mcp3421句柄
  * @retval 转换结果，单位为V
  */
float mcp3421_one_conversion( mcp3421_s* mcp) ;						

/** @brief  设置mcp3421为连续转换并读取转换后的数据
  * @details 使用mcp中的参数配置mcap3421并开始连续转换
  * @param[in]  mcp mcp3421句柄
  * @retval 转换结果，单位为V，范围-2.048--+（2.048-1LSB）
  */
void mcp3421_continuous_conversion ( mcp3421_s* mcp, uint8_t times, float *adval) ;

#ifdef __cplusplus
}
#endif

#endif  /* __MCP3421_H__ */






