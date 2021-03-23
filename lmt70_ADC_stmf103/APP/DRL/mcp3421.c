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

/* Includes ------------------------------------------------------------------*/
#include "mcp3421.h" 
#include "port_iic.h"

/** @addtogroup MCP3421
  * @{
  */
/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/

/* MCP3421初始化 */
void mcp3421_init ( mcp3421_s* mcp)
{	
	mcp->address = MCP3421_ADDR ;
	mcp->gain = gain1 ;
	mcp->sampling_rate = rate18bit ;
	mcp->conversion_mode = oneshot_mode ; 
	mcp->ready_flag = nready_or_start ;
	
	iic_init() ;
}

/* 修改增益 */
void mcp3421_write_gain ( mcp3421_s* mcp, uint8_t gain)						
{
	mcp->gain = gain ;
}

/* 修改采样率 */
void mcp3421_write_rate ( mcp3421_s* mcp, uint8_t rate)
{	
	mcp->sampling_rate = rate ;
}

/* 修改转换模式 */
void mcp3421_write_mode ( mcp3421_s* mcp, uint8_t mode)
{
	mcp->conversion_mode = mode ;
}

/* 修改转换标志位 */
void mcp3421_write_flag ( mcp3421_s* mcp, uint8_t flag)
{
	mcp->ready_flag = flag ;
}

/* 读取增益 */
uint8_t mcp3421_read_gain ( mcp3421_s* mcp)
{
	return mcp->gain ;
}

/* 读取转换速率 */
uint8_t mcp3421_read_rate ( mcp3421_s* mcp)
{
	return mcp->sampling_rate ;
}

/* 读取模式 */
uint8_t mcp3421_read_mode ( mcp3421_s* mcp)
{
	return mcp->conversion_mode ;
}

/* 读取标志位 */
uint8_t mcp3421_read_flag ( mcp3421_s* mcp)
{
	return mcp->ready_flag ;
}

/* 获得MCP3421的单次转换结果，ad转换结果，范围-2.048--+（2.048-1LSB）单位V */
float mcp3421_one_conversion ( mcp3421_s* mcp)
{
	uint8_t cofbit =0 ;
    uint8_t ad_buf[3] ;
	uint32_t temp = 0 ;
	float val = 0 ; 
	
	mcp->ready_flag = nready_or_start ;
	cofbit = (mcp->gain) | (mcp->sampling_rate) | (mcp->conversion_mode) | (mcp->ready_flag) ;		
    
	switch (mcp->sampling_rate)							
	{
		case rate12bit :
			iic_master_receive ( mcp->address, cofbit, ad_buf, 2, 100) ;
        
            temp = ( temp << 8) | ad_buf[0] ;                  
			temp = ( temp << 8) | ad_buf[1] ;
			temp &= (uint32_t)0x000fff ;
			
			if( (temp >> 11))
			{
				temp = ~temp ;
				val = ( ( temp & (uint32_t)0x000fff) + 1) * 1.0 ;
				val = - val ;
			}
			else
				val = temp * 1.0 ; 
				
			break ;
		case rate14bit :
			iic_master_receive ( mcp->address, cofbit, ad_buf, 2, 100) ;
        
            temp = ( temp << 8) | ad_buf[0] ;                  
			temp = ( temp << 8) | ad_buf[1] ;
			temp &= (uint32_t)0x003fff ;	

			if( (temp >> 13))
			{
				temp = ~temp ;
				val = ( ( temp & (uint32_t)0x003fff) + 1) * 0.250 ;
				val = - val ;
			}
			else
				val = temp * 0.250 ; 
			
			break ;
		case rate16bit :
			iic_master_receive ( mcp->address, cofbit, ad_buf, 2, 100) ;
        
            temp = ( temp << 8) | ad_buf[0] ;                  
			temp = ( temp << 8) | ad_buf[1] ;
			temp &= (uint32_t)0x00ffff ;	
		
			if( (temp >> 15))
			{
				temp = ~temp ;
				val = ( ( temp & (uint32_t)0x00ffff) + 1) * 0.0625 ;
				val = - val ;
			}
			else
				val = temp * 0.0625 ; 
		
			break ;
		case rate18bit :
            iic_master_receive ( mcp->address, cofbit, ad_buf, 3, 100) ;
        
            temp = ( temp << 8) | ad_buf[0] ;                  
			temp = ( temp << 8) | ad_buf[1] ;                 			
			temp = ( temp << 8) | ad_buf[2] ;

			temp &= (uint32_t)0x03ffff ; 
			
			if( (temp >> 17))
			{
				temp = ~temp ;
				val = ( ( temp & (uint32_t)0x03ffff) + 1) * 0.015625 ;
				val = - val ;
			}
			else
				val = temp * 0.015625 ; 
		
			break ;
	}
	
	switch(mcp->gain)
	{
		case gain1 :
			val /= 1 ;
			break ;
		case gain2 :
			val /= 2 ;
			break ;
		case gain4 :
			val /= 4 ;
			break ;
		case gain8 :
			val /= 8 ;
			break ;
	}
	
	return val ;	
}

/**
  * @}
  */






