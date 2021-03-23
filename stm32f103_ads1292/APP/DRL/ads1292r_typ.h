/**
  ******************************************************************************
  * @file           : ads1292r_typ.h
  * @brief          : ads1292r����������Ͷ���
  * @details        : �Ĵ����ꡢ�����
  * @author         :  
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
  
/** @brief  �Ĵ�����ַö��
  * @details 11���Ĵ���
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
  * @brief  һ������Ҳ����ȫ����λ��+ö��ʵ�֣����ǵ��������б�������֧�֣�
  * ���ú�+���뷽ʽʵ�֡�
  * @{
  */
   
/* Exported constants --------------------------------------------------------*/
#define ADS1292R_REG_SIZE_MAX 12    /* ADS1292R�Ĵ������� */

/** @addtogroup ADS1292R_TYP_REG_CONTENT ADS1292R TYP Exported content 
  * @brief  ���Ĵ�������
  * @{
  */
/* оƬID */
#define ADS1292R_ID 0x73

/* ����ADS1292R_REG_CONFIG1�ļĴ������� */
#define ADS1292R_SINGLE_SHOT_OFF 0  /* ����ת��ģʽ,Ĭ�� */
#define ADS1292R_SINGLE_SHOT_ON 1   /* ����ת��ģʽ */
/* �����ʣ���ģ�����fclkΪ512k��0��Ƶģʽ�����������²����ʻ�ı� */
#define ADS1292R_OVERSAMPLING_125SPS 0
#define ADS1292R_OVERSAMPLING_250SPS 1
#define ADS1292R_OVERSAMPLING_500SPS 2  /* Ĭ�� */
#define ADS1292R_OVERSAMPLING_1000SPS 3
#define ADS1292R_OVERSAMPLING_2000SPS 4
#define ADS1292R_OVERSAMPLING_4000SPS 5
#define ADS1292R_OVERSAMPLING_8000SPS 6
#define ADS1292R_OVERSAMPLING_NONESPS 7

/* ����ADS1292R_REG_CONFIG2�ļĴ������� */
#define ADS1292R_PDB_LOFF_COMP_OFF 0   /* ��������Ƚ����أ�Ĭ�� */
#define ADS1292R_PDB_LOFF_COMP_ON 1    /* ��������Ƚ����� */
#define ADS1292R_PDB_REFBUF_OFF 0   /* �ڲ��ο���ѹ�أ�Ĭ�� */
#define ADS1292R_PDB_REFBUF_ON 1    /* �ڲ��ο���ѹ�� */
#define ADS1292R_VREF_2420MV 0      /* ѡ��ο���ѹΪ2.42v��Ĭ�� */
#define ADS1292R_VREF_4033MV 1      /* ѡ��ο���ѹΪ4.033v */
#define ADS1292R_CLK_OUTPUT_OFF 0   /* ʱ������أ�Ĭ�� */
#define ADS1292R_CLK_OUTPUT_ON 1    /* ʱ������� */
#define ADS1292R_INT_TEST_OFF 0   /* �ڲ����Ե�ѹ�أ�Ĭ�� */
#define ADS1292R_INT_TEST_ON 1    /* �ڲ����Ե�ѹ�� */
#define ADS1292R_INT_FREQ_DC 0   /* ֱ����Ĭ�� */
#define ADS1292R_INT_FREQ_AC 1    /* 1HZ���� */

/* ����ADS1292R_REG_LOFF�ļĴ������� */

/* ����ADS1292R_REG_CH1SET����ADS1292R_REG_CH2SET�ļĴ������� */
#define ADS1292R_CHx_OFF 1          /* ��ֹʹ��ͨ��һ */
#define ADS1292R_CHx_ON 0           /* ʹ��ͨ��һ��Ĭ�� */

#define ADS1292R_GAIN_6 0           /* ʹ��ͨ��һ6�����棬Ĭ�� */
#define ADS1292R_GAIN_1 1           /* ʹ��ͨ��һ1������ */
#define ADS1292R_GAIN_2 2           /* ʹ��ͨ��һ2������ */
#define ADS1292R_GAIN_3 3           /* ʹ��ͨ��һ3������ */
#define ADS1292R_GAIN_4 4           /* ʹ��ͨ��һ4������ */
#define ADS1292R_GAIN_8 5           /* ʹ��ͨ��һ8������ */
#define ADS1292R_GAIN_12 6          /* ʹ��ͨ��һ12������ */
/* ѡ��ͨ��һ������ */
#define ADS1292R_CHx_INPUT_NORMAL 0     /* �����缫���룬Ĭ�� */
#define ADS1292R_CHx_INPUT_SHORTED 1    /* ��·����ƫִ�� */
#define ADS1292R_CHx_INPUT_RLD 2        /* �������� */
/* For channel 1, (MVDDP �C MVDDN) is [0.5(AVDD + AVSS)]; for channel 2, (MVDDP �C MVDDN) is DVDD / 4. */
/* For channel 2,VDD / 2 for supply measurement */
#define ADS1292R_CHx_INPUT_MVDD 3       
#define ADS1292R_CHx_INPUT_TEMP 4       /* �����¶� */
#define ADS1292R_CHx_INPUT_TEST 5       /* �ڲ������ź� */
#define ADS1292R_CHx_INPUT_RLDDRP 6     
#define ADS1292R_CHx_INPUT_RLDDRM 7
#define ADS1292R_CHx_INPUT_RLDDRPM 8
#define ADS1292R_CHx_INPUT_ROUTE 9      /* ���ӵ�ͨ���� */
#define ADS1292R_CHx_INPUT_RESERVED 10  /* Ԥ�� */

/* ����ADS1292R_REG_RLDSENS�ļĴ������� */
#define ADS1292R_CHOP_FREQ_DIV4 3       /* PGAն��Ƶ��δfMOD/4 */
#define ADS1292R_PDB_RLD_OFF 0          /* ����������Դ�أ�Ĭ�� */
#define ADS1292R_PDB_RLD_ON 1           /* ����������Դ�� */
#define ADS1292R_PDB_RLD_SENSE_OFF 0          /* ������������������أ�Ĭ�� */
#define ADS1292R_PDB_RLD_SENSE_ON 1           /* �����������������⿪ */
#define ADS1292R_RLD2N_OFF 0    /* ͨ��������Ϊ��������أ�Ĭ�� */
#define ADS1292R_RLD2N_ON 1    /* ͨ��������Ϊ�������뿪 */
#define ADS1292R_RLD2P_OFF 0    /* ͨ��������Ϊ��������أ�Ĭ�� */
#define ADS1292R_RLD2P_ON 1    /* ͨ��������Ϊ�������뿪 */
#define ADS1292R_RLD1N_OFF 0    /* ͨ��һ����Ϊ��������أ�Ĭ�� */
#define ADS1292R_RLD1N_ON 1    /* ͨ��һ����Ϊ�������뿪 */
#define ADS1292R_RLD1P_OFF 0    /* ͨ��һ����Ϊ��������أ�Ĭ�� */
#define ADS1292R_RLD1P_ON 1    /* ͨ��һ����Ϊ�������뿪 */

/* ����ADS1292R_REG_LOFFSENS�ļĴ������� */
#define ADS1292R_FLIP2_OFF 0    /* ����������ͨ������������أ�Ĭ�� */
#define ADS1292R_FLIP2_ON 1     /* ����������ͨ������������ */
#define ADS1292R_FLIP1_OFF 0    /* ����������ͨ��һ��������أ�Ĭ�� */
#define ADS1292R_FLIP1_ON 1     /* ����������ͨ��һ�������� */
#define ADS1292R_LOFF2N_OFF 0    /* ͨ������������������أ�Ĭ�� */
#define ADS1292R_LOFF2N_ON 1     /* ͨ�����������������⿪ */
#define ADS1292R_LOFF2P_OFF 0    /* ͨ������������������أ�Ĭ�� */
#define ADS1292R_LOFF2P_ON 1     /* ͨ�����������������⿪ */
#define ADS1292R_LOFF1N_OFF 0    /* ͨ��һ��������������أ�Ĭ�� */
#define ADS1292R_LOFF1N_ON 1     /* ͨ��һ�������������⿪ */
#define ADS1292R_LOFF1P_OFF 0    /* ͨ��һ��������������أ�Ĭ�� */
#define ADS1292R_LOFF1P_ON 1     /* ͨ��һ�������������⿪ */

/* ����ADS1292R_REG_LOFFSTAT�ļĴ������� */
#define ADS1292R_CLK_DIV4 0             /* 0 = fMOD = fCLK / 4 (default, use when fCLK = 512 kHz) */
#define ADS1292R_CLK_DIV16 1            /* 1 = fMOD = fCLK / 16 (use when fCLK = 2.048 MHz) */

/* ����ADS1292R_REG_RESP1�ļĴ������� */
#define ADS1292R_DEMOD_EN1_OFF 0    /* ͨ��һ�ϵĺ��������·�أ�Ĭ�� */
#define ADS1292R_DEMOD_EN1_ON 1     /* ͨ��һ�ϵĺ��������·�� */
#define ADS1292R_DEMOD_EN_OFF 0     /* ͨ��һ�ϵĺ������Ƶ�·�أ�Ĭ�� */
#define ADS1292R_DEMOD_EN_ON 1      /* ͨ��һ�ϵĺ������Ƶ�·�� */
#define ADS1292R_RESPPH_0 0         /* ����ź���λƫ��0��Ĭ�� */
#define ADS1292R_RESPPH_135 0x0c    /* ����ź���λƫ��135�� */
#define ADS1292R_RESP_CTRL_INT 0    /* �ڲ������ڲ�ʱ�ӣ�Ĭ�� */
#define ADS1292R_RESP_CTRL_EXT 1     /* �ڲ������ⲿʱ�� */

/* ����ADS1292R_REG_RESP2�ļĴ������� */
#define ADS1292R_CALIB_ON_OFF 0    /* У׼�أ�Ĭ�� */
#define ADS1292R_CALIB_ON_ON 1     /* У׼�� */
#define ADS1292R_RESP_FREQ_36 0     /* ͨ��һ�ϵĺ������Ƶ�·�أ�Ĭ�� */
#define ADS1292R_RESP_FREQ_64 1      /* ͨ��һ�ϵĺ������Ƶ�·�� */
#define ADS1292R_RLDREF_EXT 0       /* ���������ο���ѹѡ���ⲿ������Ĭ�� */
#define ADS1292R_RLDREF_INT 1       /* ���������ο���ѹѡ���ڲ��ź� */

/* ����ADS1292R_REG_GPIO�ļĴ������� */
/**
  * @}
  */

/** @addtogroup ADS1292R_TYP_REG_MASK ADS1292R TYP Reg Mask 
  * @brief  ���Ĵ���ֵ��λ�����룬��ADS1292R_GET_BITS��ADS1292R_SET_BITS��������
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
  * @brief  ����
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

/* Register Read Commands�����5λΪ��д�ĵ�ַ */
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
/** @brief  ��ȡADS1292R��ָ���Ĵ�����ָ��λ
  * @details 
  * @param[in]  bitname  λ���� 
  * @param[in]  reg  �Ĵ�������
  * @retval ��λ��ֵ
  */ 
#define ADS1292R_GET_BITS(bitname, reg) ((reg & bitname##_MASK) >> bitname##_POS)

/** @brief  ����ADS1292R��ָ���Ĵ�����ָ��λ
  * @details    
  * @param[in]  reg  �Ĵ�������
  * @param[in]  bitname  λ����
  * @param[in]  val  Ҫ���õ�ֵ
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


