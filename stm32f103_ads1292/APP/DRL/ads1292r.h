/**
  ******************************************************************************
  * @file           : ads1292r.h
  * @brief          : ads1292r驱动头文件
  * @details        : 对ads1292r芯片的基本硬件操作，初始化，寄存器读写，ad转换
  * @author         :  
  * @date           : 2020/9/2
  * @version        : V0.1
  * @copyright      : Copyright (C) 
  ******************************************************************************
  * @attention
  * -不依赖于具体硬件，通过调用个底层接口实现功能。
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
#ifndef __ADS1292R_H
#define __ADS1292R_H	  

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

/** @brief  初始化ads1292（未开始采集）
  * @details    大约需要3秒左右的初始化时间，设置成停止连续读模式。
  * 在该函数调用后需要调用以adc_start结尾的函数，以开始转换。
  * @param[in]  timeout  超时转换时间 timeout*200ms
  * @retval 
  * -非0初始化成功
  * -0初始化失败
  */
uint8_t ads1292r_init( uint8_t timeout) ;

/** @brief  开启双通道正常模式采样，用于心电采集
  * @details    500sps，6倍增益，调用该函数后需调用读函数，读取ad数据
  * @retval NONE
  */
void ads1292r_normal_adc_start(void) ;

/** @brief  开启双测试信号adc转换。
  * @details    500sps，6倍增益，1HZ方波，调用该函数后需调用读函数，读取ad数据
  * @retval NONE
  */
void ads1292r_test_adc_start(void) ;

/** @brief  获取转换后的ad原始数据,轮询方式读取(暂不支持读通道三数据，待升级)
  * @details 之所以不对数据进行直接处理，是因为后续需要不同的处理方式。
  * @param[in]  ad_buf 指向存储数据缓冲区的指针，缓冲区大小应不小于9byte
  * [0:2]为状态值，[3:5]为通道一结果，[6:8]为通道二结果。其他通道依次以
  * 三字节往后排。
  * @retval NONE
  */
void ads1292r_get_value( uint8_t *ad_buf) ;

/**
  * @}
  */
  
/**
  * @}
  */

#ifdef __cplusplus
}
#endif
  
#endif /* __ADS1292R_H */



