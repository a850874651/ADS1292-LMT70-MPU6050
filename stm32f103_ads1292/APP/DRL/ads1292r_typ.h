/**
  ******************************************************************************
  * @file           : ads1292r_typ.h
  * @brief          : ads1292r相关数据类型定义
  * @details        : 寄存器标、命令表、
  * @author         :  
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
#ifndef __ADS1292_TYP_H
#define __ADS1292_TYP_H	  

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/** @defgroup ADS1292R_TYP  ADS1292R TYP
  * @{
  */
/* Exported types ------------------------------------------------------------*/
/** @addtogroup ADS1292R_TYP_Exported_types ADS1292R TYP Exported types 
  * @{
  */
  
/** @brief  寄存器地址枚举
  * @details 11个寄存器
  */  
typedef enum
{
    ADS1292R_REG_ID = 0x00 ,
    ADS1292R_REG_CONFIG1 = 0x01 ,
    ADS1292R_REG_CONFIG2 = 0x02 ,
    ADS1292R_REG_LOFF = 0x03 ,
    ADS1292R_REG_CH1SET = 0x04 ,
    ADS1292R_REG_CH2SET = 0x05 ,
    ADS1292R_REG_RLDSENS = 0x06 ,
    ADS1292R_REG_LOFFSENS = 0x07 ,
    ADS1292R_REG_LOFFSTAT = 0x08 ,
    ADS1292R_REG_RESP1 = 0x09 ,
    ADS1292R_REG_RESP2 = 0x0A ,
    ADS1292R_REG_GPIO = 0x0B 
}ADS1292R_REG_E ;

/**
  * @}
  */

/** @addtogroup ADS1292R_TYP_Exported_constants ADS1292R TYP Exported constants 
  * @brief  一下内容也可以全部由位域+枚举实现，考虑到不是所有编译器都支持，
  * 采用宏+掩码方式实现。
  * @{
  */
   
/* Exported constants --------------------------------------------------------*/
#define ADS1292R_REG_SIZE_MAX 12    /* ADS1292R寄存器数量 */

/** @addtogroup ADS1292R_TYP_REG_CONTENT ADS1292R TYP Exported content 
  * @brief  各寄存器内容
  * @{
  */
/* 芯片ID */
#define ADS1292R_ID 0x73

/* 属于ADS1292R_REG_CONFIG1的寄存器设置 */
#define ADS1292R_SINGLE_SHOT_OFF 0  /* 连续转换模式,默认 */
#define ADS1292R_SINGLE_SHOT_ON 1   /* 单次转换模式 */
/* 采样率，该模块采用fclk为512k，0分频模式，其他配置下采样率会改变 */
#define ADS1292R_OVERSAMPLING_125SPS 0
#define ADS1292R_OVERSAMPLING_250SPS 1
#define ADS1292R_OVERSAMPLING_500SPS 2  /* 默认 */
#define ADS1292R_OVERSAMPLING_1000SPS 3
#define ADS1292R_OVERSAMPLING_2000SPS 4
#define ADS1292R_OVERSAMPLING_4000SPS 5
#define ADS1292R_OVERSAMPLING_8000SPS 6
#define ADS1292R_OVERSAMPLING_NONESPS 7

/* 属于ADS1292R_REG_CONFIG2的寄存器设置 */
#define ADS1292R_PDB_LOFF_COMP_OFF 0   /* 导联脱落比较器关，默认 */
#define ADS1292R_PDB_LOFF_COMP_ON 1    /* 导联脱落比较器开 */
#define ADS1292R_PDB_REFBUF_OFF 0   /* 内部参考电压关，默认 */
#define ADS1292R_PDB_REFBUF_ON 1    /* 内部参考电压开 */
#define ADS1292R_VREF_2420MV 0      /* 选择参考电压为2.42v，默认 */
#define ADS1292R_VREF_4033MV 1      /* 选择参考电压为4.033v */
#define ADS1292R_CLK_OUTPUT_OFF 0   /* 时钟输出关，默认 */
#define ADS1292R_CLK_OUTPUT_ON 1    /* 时钟输出开 */
#define ADS1292R_INT_TEST_OFF 0   /* 内部测试电压关，默认 */
#define ADS1292R_INT_TEST_ON 1    /* 内部测试电压开 */
#define ADS1292R_INT_FREQ_DC 0   /* 直流，默认 */
#define ADS1292R_INT_FREQ_AC 1    /* 1HZ方波 */

/* 属于ADS1292R_REG_LOFF的寄存器设置 */

/* 属于ADS1292R_REG_CH1SET，与ADS1292R_REG_CH2SET的寄存器设置 */
#define ADS1292R_CHx_OFF 1          /* 禁止使用通道一 */
#define ADS1292R_CHx_ON 0           /* 使用通道一，默认 */

#define ADS1292R_GAIN_6 0           /* 使用通道一6倍增益，默认 */
#define ADS1292R_GAIN_1 1           /* 使用通道一1倍增益 */
#define ADS1292R_GAIN_2 2           /* 使用通道一2倍增益 */
#define ADS1292R_GAIN_3 3           /* 使用通道一3倍增益 */
#define ADS1292R_GAIN_4 4           /* 使用通道一4倍增益 */
#define ADS1292R_GAIN_8 5           /* 使用通道一8倍增益 */
#define ADS1292R_GAIN_12 6          /* 使用通道一12倍增益 */
/* 选择通道一的输入 */
#define ADS1292R_CHx_INPUT_NORMAL 0     /* 正常电极输入，默认 */
#define ADS1292R_CHx_INPUT_SHORTED 1    /* 短路，测偏执用 */
#define ADS1292R_CHx_INPUT_RLD 2        /* 右腿驱动 */
/* For channel 1, (MVDDP – MVDDN) is [0.5(AVDD + AVSS)]; for channel 2, (MVDDP – MVDDN) is DVDD / 4. */
/* For channel 2,VDD / 2 for supply measurement */
#define ADS1292R_CHx_INPUT_MVDD 3       
#define ADS1292R_CHx_INPUT_TEMP 4       /* 板载温度 */
#define ADS1292R_CHx_INPUT_TEST 5       /* 内部测试信号 */
#define ADS1292R_CHx_INPUT_RLDDRP 6     
#define ADS1292R_CHx_INPUT_RLDDRM 7
#define ADS1292R_CHx_INPUT_RLDDRPM 8
#define ADS1292R_CHx_INPUT_ROUTE 9      /* 连接到通道三 */
#define ADS1292R_CHx_INPUT_RESERVED 10  /* 预留 */

/* 属于ADS1292R_REG_RLDSENS的寄存器设置 */
#define ADS1292R_CHOP_FREQ_DIV4 3       /* PGA斩波频率未fMOD/4 */
#define ADS1292R_PDB_RLD_OFF 0          /* 右腿驱动电源关，默认 */
#define ADS1292R_PDB_RLD_ON 1           /* 右腿驱动电源开 */
#define ADS1292R_PDB_RLD_SENSE_OFF 0          /* 右腿驱动导联脱落检测关，默认 */
#define ADS1292R_PDB_RLD_SENSE_ON 1           /* 右腿驱动导联脱落检测开 */
#define ADS1292R_RLD2N_OFF 0    /* 通道二负极为右腿输入关，默认 */
#define ADS1292R_RLD2N_ON 1    /* 通道二负极为右腿输入开 */
#define ADS1292R_RLD2P_OFF 0    /* 通道二正极为右腿输入关，默认 */
#define ADS1292R_RLD2P_ON 1    /* 通道二正极为右腿输入开 */
#define ADS1292R_RLD1N_OFF 0    /* 通道一负极为右腿输入关，默认 */
#define ADS1292R_RLD1N_ON 1    /* 通道一负极为右腿输入开 */
#define ADS1292R_RLD1P_OFF 0    /* 通道一正极为右腿输入关，默认 */
#define ADS1292R_RLD1P_ON 1    /* 通道一正极为右腿输入开 */

/* 属于ADS1292R_REG_LOFFSENS的寄存器设置 */
#define ADS1292R_FLIP2_OFF 0    /* 导联脱落检测通道二电流方向关，默认 */
#define ADS1292R_FLIP2_ON 1     /* 导联脱落检测通道二电流方向开 */
#define ADS1292R_FLIP1_OFF 0    /* 导联脱落检测通道一电流方向关，默认 */
#define ADS1292R_FLIP1_ON 1     /* 导联脱落检测通道一电流方向开 */
#define ADS1292R_LOFF2N_OFF 0    /* 通道二负极导联脱落检测关，默认 */
#define ADS1292R_LOFF2N_ON 1     /* 通道二负极导联脱落检测开 */
#define ADS1292R_LOFF2P_OFF 0    /* 通道二正极导联脱落检测关，默认 */
#define ADS1292R_LOFF2P_ON 1     /* 通道二正极导联脱落检测开 */
#define ADS1292R_LOFF1N_OFF 0    /* 通道一负极导联脱落检测关，默认 */
#define ADS1292R_LOFF1N_ON 1     /* 通道一负极导联脱落检测开 */
#define ADS1292R_LOFF1P_OFF 0    /* 通道一正极导联脱落检测关，默认 */
#define ADS1292R_LOFF1P_ON 1     /* 通道一正极导联脱落检测开 */

/* 属于ADS1292R_REG_LOFFSTAT的寄存器设置 */
#define ADS1292R_CLK_DIV4 0             /* 0 = fMOD = fCLK / 4 (default, use when fCLK = 512 kHz) */
#define ADS1292R_CLK_DIV16 1            /* 1 = fMOD = fCLK / 16 (use when fCLK = 2.048 MHz) */

/* 属于ADS1292R_REG_RESP1的寄存器设置 */
#define ADS1292R_DEMOD_EN1_OFF 0    /* 通道一上的呼吸解调电路关，默认 */
#define ADS1292R_DEMOD_EN1_ON 1     /* 通道一上的呼吸解调电路开 */
#define ADS1292R_DEMOD_EN_OFF 0     /* 通道一上的呼吸调制电路关，默认 */
#define ADS1292R_DEMOD_EN_ON 1      /* 通道一上的呼吸调制电路开 */
#define ADS1292R_RESPPH_0 0         /* 解调信号相位偏移0，默认 */
#define ADS1292R_RESPPH_135 0x0c    /* 解调信号相位偏移135度 */
#define ADS1292R_RESP_CTRL_INT 0    /* 内部呼吸内部时钟，默认 */
#define ADS1292R_RESP_CTRL_EXT 1     /* 内部呼吸外部时钟 */

/* 属于ADS1292R_REG_RESP2的寄存器设置 */
#define ADS1292R_CALIB_ON_OFF 0    /* 校准关，默认 */
#define ADS1292R_CALIB_ON_ON 1     /* 校准开 */
#define ADS1292R_RESP_FREQ_36 0     /* 通道一上的呼吸调制电路关，默认 */
#define ADS1292R_RESP_FREQ_64 1      /* 通道一上的呼吸调制电路开 */
#define ADS1292R_RLDREF_EXT 0       /* 右腿驱动参考电压选择外部反馈，默认 */
#define ADS1292R_RLDREF_INT 1       /* 右腿驱动参考电压选择内部信号 */

/* 属于ADS1292R_REG_GPIO的寄存器设置 */
/**
  * @}
  */

/** @addtogroup ADS1292R_TYP_REG_MASK ADS1292R TYP Reg Mask 
  * @brief  各寄存器值与位置掩码，被ADS1292R_GET_BITS与ADS1292R_SET_BITS函数调用
  * @{
  */
#define ADS1292R_ID_POS 0
#define ADS1292R_ID_MASK 0xFF

#define ADS1292R_SINGLE_SHOT_POS 7
#define ADS1292R_SINGLE_SHOT_MASK 0x80
#define ADS1292R_DR_POS 0
#define ADS1292R_DR_MASK 0x07

#define ADS1292R_PDB_LOFF_COMP_POS 6
#define ADS1292R_PDB_LOFF_COMP_MASK 0x40
#define ADS1292R_PDB_REFBUF_POS 5
#define ADS1292R_PDB_REFBUF_MASK 0x20
#define ADS1292R_VREF_4V_POS 4
#define ADS1292R_VREF_4V_MASK 0x10
#define ADS1292R_CLK_EN_POS 3
#define ADS1292R_CLK_EN_MASK 0x80
#define ADS1292R_INT_TEST_POS 1   
#define ADS1292R_INT_TEST_MASK 0x02    
#define ADS1292R_INT_FREQ_POS 0   
#define ADS1292R_INT_FREQ_MASK 0x01   

#define ADS1292R_PDx_POS 7
#define ADS1292R_PDx_MASK 0x80
#define ADS1292R_GAINx_POS 4
#define ADS1292R_GAINx_MASK 0x70
#define ADS1292R_MUXx_POS 0
#define ADS1292R_MUXx_MASK 0x0F

#define ADS1292R_CHOP_POS 6
#define ADS1292R_CHOP_MASK 0xC0
#define ADS1292R_PDB_RLD_POS 5
#define ADS1292R_PDB_RLD_MASK 0x20
#define ADS1292R_RLD_LOFF_SENSE_POS 4
#define ADS1292R_RLD_LOFF_SENSE_MASK 0x10
#define ADS1292R_RLD2N_POS 3
#define ADS1292R_RLD2N_MASK 0x08
#define ADS1292R_RLD2P_POS 2
#define ADS1292R_RLD2P_MASK 0x04
#define ADS1292R_RLD1N_POS 1
#define ADS1292R_RLD1N_MASK 0x02
#define ADS1292R_RLD1P_POS 0
#define ADS1292R_RLD1P_MASK 0x01

#define ADS1292R_FLIP2_POS 5
#define ADS1292R_FLIP2_MASK 0x20
#define ADS1292R_FLIP1_POS 4
#define ADS1292R_FLIP1_MASK 0x10
#define ADS1292R_LOFF2N_POS 3
#define ADS1292R_LOFF2N_MASK 0x08
#define ADS1292R_LOFF2P_POS 2
#define ADS1292R_LOFF2P_MASK 0x04
#define ADS1292R_LOFFN_POS 1
#define ADS1292R_LOFF1N_MASK 0x02
#define ADS1292R_LOFF1P_POS 0
#define ADS1292R_LOFF1P_MASK 0x01

#define ADS1292R_CLK_DIV_POS 6
#define ADS1292R_CLK_DIV_MASK 0x40

#define ADS1292R_RESP_DEMOD_EN1_POS 7
#define ADS1292R_RESP_DEMOD_EN1_MASK 0x80
#define ADS1292R_RESP_MOD_EN_POS 6
#define ADS1292R_RESP_MOD_EN_MASK 0x40
#define ADS1292R_RESP_PH_POS 2
#define ADS1292R_RESP_PH_MASK 0x3c
#define ADS1292R_RESP_CTRL_POS 0
#define ADS1292R_RESP_CTRL_MASK 0x01

#define ADS1292R_CALIB_ON_POS 7
#define ADS1292R_CALIB_ON_MASK 0x80
#define ADS1292R_RESP_FREQ_POS 2
#define ADS1292R_RESP_FREQ_MASK 0x04
#define ADS1292R_RLDREF_INT_POS 1
#define ADS1292R_RLDREF_INT_MASK 0x02

/**
  * @}
  */

/** @addtogroup ADS1292R_TYP_COMMAND ADS1292R TYP COMMAND 
  * @brief  命令
  * @{
  */
/* System Commands */
#define ADS1292R_COMMAND_WAKEUP 0x02
#define ADS1292R_COMMAND_STANDBY 0x04
#define ADS1292R_COMMAND_RESET 0x06 
#define ADS1292R_COMMAND_START 0x08 
#define ADS1292R_COMMAND_STOP 0x0A 
#define ADS1292R_COMMAND_OFFSETCAL 0x1A 

/* Data Read Commands */
#define ADS1292R_COMMAND_RDATAC 0x10
#define ADS1292R_COMMAND_SDATAC  0x11
#define ADS1292R_COMMAND_RDATA 0x12

/* Register Read Commands，最后5位为读写的地址 */
#define ADS1292R_COMMAND_RREG 0x20
#define ADS1292R_COMMAND_WREG 0x40
/**
  * @}
  */
  
/**
  * @}
  */

/**
  * @}
  */
  
/* Exported macro ------------------------------------------------------------*/
/** @brief  读取ADS1292R的指定寄存器的指定位
  * @details 
  * @param[in]  bitname  位名字 
  * @param[in]  reg  寄存器名字
  * @retval 该位的值
  */ 
#define ADS1292R_GET_BITS(bitname, reg) ((reg & bitname##_MASK) >> bitname##_POS)

/** @brief  设置ADS1292R的指定寄存器的指定位
  * @details    
  * @param[in]  reg  寄存器名字
  * @param[in]  bitname  位名字
  * @param[in]  val  要设置的值
  * @retval NONE
  */
#define ADS1292R_SET_BITS(reg, bitname, val) ((reg & ~bitname##_MASK) \
                                                | ((val << bitname##_POS) & bitname##_MASK))
/* Exported functions --------------------------------------------------------*/

  
/**
  * @}
  */

#ifdef __cplusplus
}
#endif
  
#endif /* __ADS1292_TYP_H */


