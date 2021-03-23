/**
  ******************************************************************************
  * @file           : mcp3421.h
  * @brief          : mcp3421 18λ�ֱ��� ���� ADC adc����ͷ�ļ�
  * @details        : ��Ҫ���õײ�iic�ӿ�
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

typedef enum						/* ���� */
{
	gain1 = 0x00 ,                  
	gain2 = 0x01 ,
	gain4 = 0x02 ,
	gain8 = 0x03 
}mcp3421_gain_e ;

typedef enum						/* ת������ */
{
	rate12bit = 0x00 ,              /* 240SPS */
	rate14bit = 0x04 ,              /* 60SPS */
	rate16bit = 0x08 ,              /* 15SPS */
	rate18bit = 0x0C                /* 3.75SPS */
}mcp3421_rate_e ;

typedef enum						/* ת��ģʽ */
{
	oneshot_mode = 0x00 ,           /* ����ת��ģʽ */
	continuous_mode = 0x10 ,        /* ����ת��ģʽ */
}mcp3421_mode_e;

typedef enum						/* ת����־λ */
{
	ready = 0x00 ,
	nready_or_start = 0x80 ,
}mcp3421_ready_e ;

/** @brief  mcp3421�ṹ��
  * @details 
  * -address ��ַ Ĭ��Ϊ MCP3421_ADDR
  * -gain    ���� 1��2��4��8 Ĭ��Ϊ1������ @ref mcp3421_gain_e
  * -sampling_rate ������ 240 SPS (12 bits)��60 SPS (14 bits)��
  * 15 SPS (16 bits)��Ĭ��3.75 SPS (18 bits) @ref mcp3421_rate_e
  *	-conversion_mode ת��ģʽ   Continuous Conversion�� 
  * Ĭ��One-Shot Conversion @ref mcp3421_mode_e
  * -ready_flag ״̬��־λ 0��ʾת���������ݴ���ȡ��
  * 1��ʾת�����ڽ��л���������ת�� @ref mcp3421_ready_e
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

/** @brief  ��ʼ��mcp3421
  * @details ���iicӲ����ʼ����mcp3421�����Ļ�������
  * @param[in]  mcp mcp3421���
  * @retval NONE
  */ 
void mcp3421_init ( mcp3421_s* mcp) ;               					

/** @brief  �޸�mcp3421������
  * @details �ڵ���mcp3421_one_conversion����ʱ��ɲ�������ʽд��
  * @param[in]  mcp mcp3421���
  * @param[in]  gain ���� @ref mcp3421_gain_e
  * @retval NONE
  */ 
void mcp3421_write_gain ( mcp3421_s* mcp, uint8_t gain) ;			

/** @brief  �޸�mcp3421�Ĳ����ʺͷֱ���
  * @details �ڵ���mcp3421_one_conversion����ʱ��ɲ�������ʽд��
  * @param[in]  mcp mcp3421���
  * @param[in]  rate ������ @ref mcp3421_rate_e
  * @retval NONE
  */ 
void mcp3421_write_rate ( mcp3421_s* mcp, uint8_t rate) ;		

/** @brief  �޸�mcp3421��ת��ģʽ
  * @details �ڵ���mcp3421_one_conversion����ʱ��ɲ�������ʽд��
  * @param[in]  mcp mcp3421���
  * @param[in]  mode ת��ģʽ @ref mcp3421_mode_e
  * @retval NONE
  */ 
void mcp3421_write_mode ( mcp3421_s* mcp, uint8_t mode) ;	

/** @brief  �޸�mcp3421��״̬��־λ
  * @details �ڵ���mcp3421_one_conversion����ʱ��ɲ�������ʽд��
  * @param[in]  mcp mcp3421���
  * @param[in]  flag ״̬��־ @ref mcp3421_ready_e
  * @retval NONE
  */ 
void mcp3421_write_flag ( mcp3421_s* mcp, uint8_t flag) ;			

/** @brief  ��ȡmcp3421������
  * @details 
  * @param[in]  mcp mcp3421���
  * @retval ����mcp3421������ @ref mcp3421_gain_e
  */ 
uint8_t mcp3421_read_gain ( mcp3421_s* mcp) ;			

/** @brief  ��ȡmcp3421�Ĳ�����
  * @details 
  * @param[in]  mcp mcp3421���
  * @retval ����mcp3421������ @ref mcp3421_rate_e
  */ 
uint8_t mcp3421_read_rate ( mcp3421_s* mcp) ;	

/** @brief  ��ȡmcp3421��ת��ģʽ
  * @details 
  * @param[in]  mcp mcp3421���
  * @retval ����mcp3421������ @ref mcp3421_mode_e
  */
uint8_t mcp3421_read_mode ( mcp3421_s* mcp) ;	

/** @brief  ��ȡmcp3421��״̬��־λ
  * @details 
  * @param[in]  mcp mcp3421���
  * @retval ����mcp3421������ @ref mcp3421_ready_e
  */
uint8_t mcp3421_read_flag ( mcp3421_s* mcp) ;		

/** @brief  ����mcp3421Ϊ����ת������ȡת���������
  * @details ʹ��mcp�еĲ�������mcap3421����ʼ����ת��
  * @param[in]  mcp mcp3421���
  * @retval ת���������λΪV
  */
float mcp3421_one_conversion( mcp3421_s* mcp) ;						

/** @brief  ����mcp3421Ϊ����ת������ȡת���������
  * @details ʹ��mcp�еĲ�������mcap3421����ʼ����ת��
  * @param[in]  mcp mcp3421���
  * @retval ת���������λΪV����Χ-2.048--+��2.048-1LSB��
  */
void mcp3421_continuous_conversion ( mcp3421_s* mcp, uint8_t times, float *adval) ;

#ifdef __cplusplus
}
#endif

#endif  /* __MCP3421_H__ */






