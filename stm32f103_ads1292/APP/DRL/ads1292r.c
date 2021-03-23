/**
  ******************************************************************************
  * @file           : ads1292r.c
  * @brief          : ads1292r驱动源文件
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

/* Includes ------------------------------------------------------------------*/
#include "ads1292r.h"
#include "ads1292r_typ.h"

#include "port_gpio.h"
#include "port_delay.h"
#include "port_debug.h"
#include "port_spi.h"

/** @addtogroup ADS1292R
  * @{
  */
/* Private typedef -----------------------------------------------------------*/
typedef struct 
{
    uint8_t id ;            /* id，ads1292r固定为0x73 */
    uint8_t cfg1 ;          /* 设置寄存器 */
    uint8_t cfg2 ;          /* 设置寄存器 */
    uint8_t loff ;          /* 导联 */
    uint8_t ch1set ;        /* 通道一设置 */
    uint8_t ch2set ;        /* 通道二设置 */
    uint8_t rld_sens ;      /* 右腿驱动 */
    uint8_t loff_sens ;     /* 导联 */
    uint8_t loff_stat ;     /* 导联 */
    uint8_t resp1 ;         /* 呼吸 */
    uint8_t resp2 ;         /* 呼吸 */
    uint8_t gpio ;          /* gpio1，2的控制 */
}ads1292r_regs_s ;

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
/* 局部全局变量，包含ads1292寄存器默认值 */
static ads1292r_regs_s ads1292r_reg = {        /* 默认参数 */
                                0x73,   /* 默认地址0x73 */
                                0x02,   /* 连续转换，500sps采样率 */
                                0x80,   /* 导联脱落比较器关，内部参考电压关，2.42v参考电压，晶振输出关，测试信号关，测试信号频率为0HZ */
                                0x10,   /* 脱落比较器正端阈值为95%，负端为5%，引出模式电流大小6na，频率为0HZ */
                                0x00,   /* 通道一关闭，6倍增益，正常电极输入 */
                                0x00,   /* 通道二关闭，6倍增益，正常电极输入 */
                                0x00,   /* 未启用 */
                                0x00,   /* 未启用 */
                                0x00,   /* fmod为clk四分频，其他未用 */
                                0x02,   /* 呼吸相关配置 */
                                0x03,   /* 呼吸相关配置 */
                                0x0c    /* gpio1、2皆为输入模式 */
                                } ;
/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
/* 不必要，尽量不要对外开放以下函数，最好设置成static类型 */
                                
/* ads1292r发送指令 */
uint8_t ads1292r_send_cmd( uint8_t cmd)
{
    uint8_t rx = 0 ;
    
	ADS1292_CS_RESET() ;    /* 选中设备 */   
	port_delay_us(100) ;
    
	rx = port_spi_transmit_receive(cmd) ;
	
    port_delay_us(100) ;
	ADS1292_CS_SET() ;      /* 释放设备 */
    
    return rx ;
}

/* ads1292r读写寄存器，自动根据指令类型区分读和写操作 */
uint8_t ads1292r_rw_reg(uint8_t cmd, uint8_t data)	
{
	uint8_t rx = 0 ;
    
	ADS1292_CS_RESET() ;    /* 选中设备 */
	port_delay_us(1);
    
	port_spi_transmit_receive(cmd) ;	/* 发送读写指令 */
	port_spi_transmit_receive(0X00) ;	/* 只写一个数据 */
    
	if( ( cmd & ADS1292R_COMMAND_RREG) == ADS1292R_COMMAND_RREG)  /* 判断指令类型 */
		rx = port_spi_transmit_receive(0X00);	/* 返回寄存器值 */
	else
		rx = port_spi_transmit_receive(data);	/* 写入数值 */
    
	port_delay_us(1);
	ADS1292_CS_SET() ;    /* 释放设备 */
    
	return rx ;
}

/* 从指定寄存器开始读写一定数量的寄存器 */
void ads1292r_write_multiregs( uint8_t reg, uint8_t *ch, uint8_t size)
{
    uint8_t i ;

    ADS1292_CS_RESET() ;    /* 选中设备 */	
    port_delay_us(100) ;

    port_spi_transmit_receive( ADS1292R_COMMAND_WREG | reg) ;
    port_delay_us(100);
    port_spi_transmit_receive(size - 1) ;
    
    for( i = 0; i < size; i++)
    {
        port_delay_us(100) ;		
        port_spi_transmit_receive(*ch) ;
        ch++ ;				
    }			
    
    port_delay_us(100) ;	
    ADS1292_CS_SET() ;   
}

/* 从指定寄存器开始读写一定数量的寄存器 */
void ads1292r_read_multiregs( uint8_t reg, uint8_t *ch, uint8_t size)
{
    uint8_t i ;

    ADS1292_CS_RESET() ;    /* 选中设备 */	
    port_delay_us(100) ;

    port_spi_transmit_receive( ADS1292R_COMMAND_RREG | reg) ;
    port_delay_us(100);
    port_spi_transmit_receive(size - 1) ;
    
    for( i = 0; i < size; i++)
    {
        port_delay_us(100) ;		
        *ch = port_spi_transmit_receive(0) ;
        ch++;
    }
    
    port_delay_us(100) ;	
    ADS1292_CS_SET() ;   
}
/* 如非必须，尽量不要对外开放以上函数，最好设置成static类型 */

/* 初始化ads1292r，超时时间为timeout*200ms，返回0表示初始化失败 */
uint8_t ads1292r_init( uint8_t timeout)
{
    uint8_t id ;
    
    /* gpio接口初始化，针对非hal库版本需要再此添加代码 */
    port_gpio_init() ;
    
    /* spi接口初始化 */
    port_spi_init() ;
    
    ADS1292_CS_SET() ;
    
    ADS1292_REST_RESET() ;
    ADS1292_START_RESET() ;
    port_delay_ms(1000) ;
    ADS1292_REST_SET() ;
    port_delay_ms(100) ;    /* 硬件复位 */
    
	ads1292r_send_cmd(ADS1292R_COMMAND_SDATAC) ;    /* 软件复位，并停止连续读状态 */
    port_delay_ms(100) ;
    ads1292r_send_cmd(ADS1292R_COMMAND_RESET) ;
    port_delay_ms(1000) ;
    ads1292r_send_cmd(ADS1292R_COMMAND_SDATAC) ;
    port_delay_ms(100) ;
    
    while( ( id != ads1292r_reg.id) && ( timeout > 0))       /* 识别芯片型号，1292r为0x73 */
	{        
        id = ads1292r_rw_reg(ADS1292R_COMMAND_RREG|ADS1292R_REG_ID, 0) ;
        
        timeout-- ;
        port_delay_ms(200) ;
	}
    
    /* 500sps采样率 */
    ads1292r_reg.cfg1 = ADS1292R_SET_BITS(ads1292r_reg.cfg1, ADS1292R_DR, ADS1292R_OVERSAMPLING_500SPS) ;
    
    /* 导联脱落比较器开，内部2.42v参考电压 */
    ads1292r_reg.cfg2 = ADS1292R_SET_BITS(ads1292r_reg.cfg2, ADS1292R_PDB_LOFF_COMP, ADS1292R_PDB_LOFF_COMP_ON) ;  
    ads1292r_reg.cfg2 = ADS1292R_SET_BITS(ads1292r_reg.cfg2, ADS1292R_PDB_REFBUF, ADS1292R_PDB_REFBUF_ON) ;       
    ads1292r_reg.cfg2 = ADS1292R_SET_BITS(ads1292r_reg.cfg2, ADS1292R_VREF_4V, ADS1292R_VREF_2420MV) ;      
    
    /* 通道二导联脱落检测功能开 */
    ads1292r_reg.loff_sens = ADS1292R_SET_BITS(ads1292r_reg.loff_sens, ADS1292R_LOFF2N, ADS1292R_LOFF2N_ON) ;
    ads1292r_reg.loff_sens = ADS1292R_SET_BITS(ads1292r_reg.loff_sens, ADS1292R_LOFF2P, ADS1292R_LOFF2P_ON) ;
    
    /* pga斩波频率4分频，右腿驱动电源开，开启通道二的右腿驱动输出 */
    ads1292r_reg.rld_sens = ADS1292R_SET_BITS(ads1292r_reg.rld_sens, ADS1292R_CHOP, ADS1292R_CHOP_FREQ_DIV4) ;
    ads1292r_reg.rld_sens = ADS1292R_SET_BITS(ads1292r_reg.rld_sens, ADS1292R_PDB_RLD, ADS1292R_PDB_RLD_ON) ;
    ads1292r_reg.rld_sens = ADS1292R_SET_BITS(ads1292r_reg.rld_sens, ADS1292R_RLD2N, ADS1292R_RLD2N_ON) ;
    ads1292r_reg.rld_sens = ADS1292R_SET_BITS(ads1292r_reg.rld_sens, ADS1292R_RLD2P, ADS1292R_RLD2P_ON) ;
    
    /* 右腿驱动参考电压选择内部信号 */
    ads1292r_reg.resp2 = ADS1292R_SET_BITS(ads1292r_reg.resp2, ADS1292R_RLDREF_INT, ADS1292R_RLDREF_INT) ;
    
    return timeout ;
}

void ads1292r_normal_adc_start()
{
    /* 关闭内部测试信号 */
    ads1292r_reg.cfg2 = ADS1292R_SET_BITS(ads1292r_reg.cfg2, ADS1292R_INT_TEST, ADS1292R_INT_TEST_OFF) ; 
    ads1292r_reg.cfg2 = ADS1292R_SET_BITS(ads1292r_reg.cfg2, ADS1292R_INT_FREQ, ADS1292R_INT_FREQ_DC) ; 
    /* 打开通道一，两倍增益，正常电极输入 */
    ads1292r_reg.ch1set = ADS1292R_SET_BITS(ads1292r_reg.ch1set, ADS1292R_PDx, ADS1292R_CHx_ON) ;
    ads1292r_reg.ch1set = ADS1292R_SET_BITS(ads1292r_reg.ch1set, ADS1292R_GAINx, ADS1292R_GAIN_2) ;
    ads1292r_reg.ch1set = ADS1292R_SET_BITS(ads1292r_reg.ch1set, ADS1292R_MUXx, ADS1292R_CHx_INPUT_NORMAL) ;
    /* 打开通道二，六倍增益，正常电极输入 */    
    ads1292r_reg.ch2set = ADS1292R_SET_BITS(ads1292r_reg.ch2set, ADS1292R_PDx, ADS1292R_CHx_ON) ;
    ads1292r_reg.ch2set = ADS1292R_SET_BITS(ads1292r_reg.ch2set, ADS1292R_GAINx, ADS1292R_GAIN_6) ;
    ads1292r_reg.ch2set = ADS1292R_SET_BITS(ads1292r_reg.ch2set, ADS1292R_MUXx, ADS1292R_CHx_INPUT_NORMAL) ;
    /* 开启通道一呼吸检测功能 */
    ads1292r_reg.resp1 = ADS1292R_SET_BITS(ads1292r_reg.resp1, ADS1292R_RESP_DEMOD_EN1, ADS1292R_DEMOD_EN1_ON) ;
    ads1292r_reg.resp1 = ADS1292R_SET_BITS(ads1292r_reg.resp1, ADS1292R_RESP_MOD_EN, ADS1292R_DEMOD_EN_ON) ;
    ads1292r_reg.resp1 = ADS1292R_SET_BITS(ads1292r_reg.resp1, ADS1292R_RESP_PH, ADS1292R_RESPPH_135) ;
    ads1292r_reg.resp1 = ADS1292R_SET_BITS(ads1292r_reg.resp1, ADS1292R_RESP_CTRL, ADS1292R_RESP_CTRL_INT) ;
    
    ads1292r_send_cmd(ADS1292R_COMMAND_SDATAC) ; /* 进入停止连续读模式 */
    port_delay_ms(100) ;
    /* 写入配置 */
    ads1292r_write_multiregs( ADS1292R_REG_ID, (uint8_t *)&ads1292r_reg, 12) ;
    port_delay_ms(10) ;
    
    ads1292r_send_cmd(ADS1292R_COMMAND_RDATAC) ; /* 启动连续模式 */
    port_delay_ms(10) ;		
    ads1292r_send_cmd(ADS1292R_COMMAND_START) ;	/* 发送开始数据转换（等效于拉高START引脚） */	
    port_delay_ms(10) ;	
}

void ads1292r_test_adc_start()
{        
    /* 开启内部测试信号 */
    ads1292r_reg.cfg2 = ADS1292R_SET_BITS(ads1292r_reg.cfg2, ADS1292R_INT_TEST, ADS1292R_INT_TEST_ON) ; 
    ads1292r_reg.cfg2 = ADS1292R_SET_BITS(ads1292r_reg.cfg2, ADS1292R_INT_FREQ, ADS1292R_INT_FREQ_AC) ; 
    /* 打开通道一，六倍增益，通道一连接到通道一 */
    ads1292r_reg.ch1set = ADS1292R_SET_BITS(ads1292r_reg.ch1set, ADS1292R_PDx, ADS1292R_CHx_ON) ;
    ads1292r_reg.ch1set = ADS1292R_SET_BITS(ads1292r_reg.ch1set, ADS1292R_GAINx, ADS1292R_GAIN_6) ;
    ads1292r_reg.ch1set = ADS1292R_SET_BITS(ads1292r_reg.ch1set, ADS1292R_MUXx, ADS1292R_CHx_INPUT_TEST) ;
    /* 打开通道二，六倍增益，通道二连接到通道二 */    
    ads1292r_reg.ch2set = ADS1292R_SET_BITS(ads1292r_reg.ch2set, ADS1292R_PDx, ADS1292R_CHx_ON) ;
    ads1292r_reg.ch2set = ADS1292R_SET_BITS(ads1292r_reg.ch2set, ADS1292R_GAINx, ADS1292R_GAIN_6) ;
    ads1292r_reg.ch2set = ADS1292R_SET_BITS(ads1292r_reg.ch2set, ADS1292R_MUXx, ADS1292R_CHx_INPUT_TEST) ;
    
    /* 关闭通道一呼吸检测功能 */
    ads1292r_reg.resp1 = ADS1292R_SET_BITS(ads1292r_reg.resp1, ADS1292R_RESP_DEMOD_EN1, ADS1292R_DEMOD_EN1_OFF) ;
    ads1292r_reg.resp1 = ADS1292R_SET_BITS(ads1292r_reg.resp1, ADS1292R_RESP_MOD_EN, ADS1292R_DEMOD_EN_OFF) ;
    ads1292r_reg.resp1 = ADS1292R_SET_BITS(ads1292r_reg.resp1, ADS1292R_RESP_PH, ADS1292R_RESPPH_0) ;
    ads1292r_reg.resp1 = ADS1292R_SET_BITS(ads1292r_reg.resp1, ADS1292R_RESP_CTRL, ADS1292R_RESP_CTRL_EXT) ;      
    
    ads1292r_send_cmd(ADS1292R_COMMAND_SDATAC) ; /* 进入停止连续读模式 */
    port_delay_ms(100) ;
    /* 写入配置 */
    ads1292r_write_multiregs( ADS1292R_REG_ID, (uint8_t *)&ads1292r_reg, 12) ;
    port_delay_ms(10) ;
    
    ads1292r_send_cmd(ADS1292R_COMMAND_RDATAC) ; /* 启动连续模式 */
    port_delay_ms(10) ;		
    ads1292r_send_cmd(ADS1292R_COMMAND_START) ;	/* 发送开始数据转换（等效于拉高START引脚） */	
    port_delay_ms(10) ;	
}

/* 获取转换后的ad原始数据 */
void ads1292r_get_value( uint8_t *ad_buf)
{
    uint8_t i ;
    
    while ( ADS1292_DRDY_GET()) ;   /* 等待转换结束 */
    
    ADS1292_CS_RESET() ;

    for ( i = 0; i < 9; i++)        /* 读取转换结果 */
    {	
        *ad_buf = port_spi_transmit_receive(0X00) ;	
        ad_buf++ ;
    }

    ADS1292_CS_SET() ;
}    


/**
  * @}
  */


