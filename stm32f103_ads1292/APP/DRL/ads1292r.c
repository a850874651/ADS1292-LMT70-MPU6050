/**
  ******************************************************************************
  * @file           : ads1292r.c
  * @brief          : ads1292r����Դ�ļ�
  * @details        : ��ads1292rоƬ�Ļ���Ӳ����������ʼ�����Ĵ�����д��adת��
  * @author         : 
  * @date           : 2020/9/2
  * @version        : V0.1
  * @copyright      : Copyright (C) 
  ******************************************************************************
  * @attention
  * -�������ھ���Ӳ����ͨ�����ø��ײ�ӿ�ʵ�ֹ��ܡ�
  ******************************************************************************
  * @verbatim
  * �޸���ʷ:    
  *      1. ���ڣ�2020/9/2
  *         ���ߣ�Charmander
  *         �޸ģ�
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
    uint8_t id ;            /* id��ads1292r�̶�Ϊ0x73 */
    uint8_t cfg1 ;          /* ���üĴ��� */
    uint8_t cfg2 ;          /* ���üĴ��� */
    uint8_t loff ;          /* ���� */
    uint8_t ch1set ;        /* ͨ��һ���� */
    uint8_t ch2set ;        /* ͨ�������� */
    uint8_t rld_sens ;      /* �������� */
    uint8_t loff_sens ;     /* ���� */
    uint8_t loff_stat ;     /* ���� */
    uint8_t resp1 ;         /* ���� */
    uint8_t resp2 ;         /* ���� */
    uint8_t gpio ;          /* gpio1��2�Ŀ��� */
}ads1292r_regs_s ;

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
/* �ֲ�ȫ�ֱ���������ads1292�Ĵ���Ĭ��ֵ */
static ads1292r_regs_s ads1292r_reg = {        /* Ĭ�ϲ��� */
                                0x73,   /* Ĭ�ϵ�ַ0x73 */
                                0x02,   /* ����ת����500sps������ */
                                0x80,   /* ��������Ƚ����أ��ڲ��ο���ѹ�أ�2.42v�ο���ѹ����������أ������źŹأ������ź�Ƶ��Ϊ0HZ */
                                0x10,   /* ����Ƚ���������ֵΪ95%������Ϊ5%������ģʽ������С6na��Ƶ��Ϊ0HZ */
                                0x00,   /* ͨ��һ�رգ�6�����棬�����缫���� */
                                0x00,   /* ͨ�����رգ�6�����棬�����缫���� */
                                0x00,   /* δ���� */
                                0x00,   /* δ���� */
                                0x00,   /* fmodΪclk�ķ�Ƶ������δ�� */
                                0x02,   /* ����������� */
                                0x03,   /* ����������� */
                                0x0c    /* gpio1��2��Ϊ����ģʽ */
                                } ;
/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
/* ����Ҫ��������Ҫ���⿪�����º�����������ó�static���� */
                                
/* ads1292r����ָ�� */
uint8_t ads1292r_send_cmd( uint8_t cmd)
{
    uint8_t rx = 0 ;
    
	ADS1292_CS_RESET() ;    /* ѡ���豸 */   
	port_delay_us(100) ;
    
	rx = port_spi_transmit_receive(cmd) ;
	
    port_delay_us(100) ;
	ADS1292_CS_SET() ;      /* �ͷ��豸 */
    
    return rx ;
}

/* ads1292r��д�Ĵ������Զ�����ָ���������ֶ���д���� */
uint8_t ads1292r_rw_reg(uint8_t cmd, uint8_t data)	
{
	uint8_t rx = 0 ;
    
	ADS1292_CS_RESET() ;    /* ѡ���豸 */
	port_delay_us(1);
    
	port_spi_transmit_receive(cmd) ;	/* ���Ͷ�дָ�� */
	port_spi_transmit_receive(0X00) ;	/* ֻдһ������ */
    
	if( ( cmd & ADS1292R_COMMAND_RREG) == ADS1292R_COMMAND_RREG)  /* �ж�ָ������ */
		rx = port_spi_transmit_receive(0X00);	/* ���ؼĴ���ֵ */
	else
		rx = port_spi_transmit_receive(data);	/* д����ֵ */
    
	port_delay_us(1);
	ADS1292_CS_SET() ;    /* �ͷ��豸 */
    
	return rx ;
}

/* ��ָ���Ĵ�����ʼ��дһ�������ļĴ��� */
void ads1292r_write_multiregs( uint8_t reg, uint8_t *ch, uint8_t size)
{
    uint8_t i ;

    ADS1292_CS_RESET() ;    /* ѡ���豸 */	
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

/* ��ָ���Ĵ�����ʼ��дһ�������ļĴ��� */
void ads1292r_read_multiregs( uint8_t reg, uint8_t *ch, uint8_t size)
{
    uint8_t i ;

    ADS1292_CS_RESET() ;    /* ѡ���豸 */	
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
/* ��Ǳ��룬������Ҫ���⿪�����Ϻ�����������ó�static���� */

/* ��ʼ��ads1292r����ʱʱ��Ϊtimeout*200ms������0��ʾ��ʼ��ʧ�� */
uint8_t ads1292r_init( uint8_t timeout)
{
    uint8_t id ;
    
    /* gpio�ӿڳ�ʼ������Է�hal��汾��Ҫ�ٴ���Ӵ��� */
    port_gpio_init() ;
    
    /* spi�ӿڳ�ʼ�� */
    port_spi_init() ;
    
    ADS1292_CS_SET() ;
    
    ADS1292_REST_RESET() ;
    ADS1292_START_RESET() ;
    port_delay_ms(1000) ;
    ADS1292_REST_SET() ;
    port_delay_ms(100) ;    /* Ӳ����λ */
    
	ads1292r_send_cmd(ADS1292R_COMMAND_SDATAC) ;    /* �����λ����ֹͣ������״̬ */
    port_delay_ms(100) ;
    ads1292r_send_cmd(ADS1292R_COMMAND_RESET) ;
    port_delay_ms(1000) ;
    ads1292r_send_cmd(ADS1292R_COMMAND_SDATAC) ;
    port_delay_ms(100) ;
    
    while( ( id != ads1292r_reg.id) && ( timeout > 0))       /* ʶ��оƬ�ͺţ�1292rΪ0x73 */
	{        
        id = ads1292r_rw_reg(ADS1292R_COMMAND_RREG|ADS1292R_REG_ID, 0) ;
        
        timeout-- ;
        port_delay_ms(200) ;
	}
    
    /* 500sps������ */
    ads1292r_reg.cfg1 = ADS1292R_SET_BITS(ads1292r_reg.cfg1, ADS1292R_DR, ADS1292R_OVERSAMPLING_500SPS) ;
    
    /* ��������Ƚ��������ڲ�2.42v�ο���ѹ */
    ads1292r_reg.cfg2 = ADS1292R_SET_BITS(ads1292r_reg.cfg2, ADS1292R_PDB_LOFF_COMP, ADS1292R_PDB_LOFF_COMP_ON) ;  
    ads1292r_reg.cfg2 = ADS1292R_SET_BITS(ads1292r_reg.cfg2, ADS1292R_PDB_REFBUF, ADS1292R_PDB_REFBUF_ON) ;       
    ads1292r_reg.cfg2 = ADS1292R_SET_BITS(ads1292r_reg.cfg2, ADS1292R_VREF_4V, ADS1292R_VREF_2420MV) ;      
    
    /* ͨ�������������⹦�ܿ� */
    ads1292r_reg.loff_sens = ADS1292R_SET_BITS(ads1292r_reg.loff_sens, ADS1292R_LOFF2N, ADS1292R_LOFF2N_ON) ;
    ads1292r_reg.loff_sens = ADS1292R_SET_BITS(ads1292r_reg.loff_sens, ADS1292R_LOFF2P, ADS1292R_LOFF2P_ON) ;
    
    /* pgaն��Ƶ��4��Ƶ������������Դ��������ͨ����������������� */
    ads1292r_reg.rld_sens = ADS1292R_SET_BITS(ads1292r_reg.rld_sens, ADS1292R_CHOP, ADS1292R_CHOP_FREQ_DIV4) ;
    ads1292r_reg.rld_sens = ADS1292R_SET_BITS(ads1292r_reg.rld_sens, ADS1292R_PDB_RLD, ADS1292R_PDB_RLD_ON) ;
    ads1292r_reg.rld_sens = ADS1292R_SET_BITS(ads1292r_reg.rld_sens, ADS1292R_RLD2N, ADS1292R_RLD2N_ON) ;
    ads1292r_reg.rld_sens = ADS1292R_SET_BITS(ads1292r_reg.rld_sens, ADS1292R_RLD2P, ADS1292R_RLD2P_ON) ;
    
    /* ���������ο���ѹѡ���ڲ��ź� */
    ads1292r_reg.resp2 = ADS1292R_SET_BITS(ads1292r_reg.resp2, ADS1292R_RLDREF_INT, ADS1292R_RLDREF_INT) ;
    
    return timeout ;
}

void ads1292r_normal_adc_start()
{
    /* �ر��ڲ������ź� */
    ads1292r_reg.cfg2 = ADS1292R_SET_BITS(ads1292r_reg.cfg2, ADS1292R_INT_TEST, ADS1292R_INT_TEST_OFF) ; 
    ads1292r_reg.cfg2 = ADS1292R_SET_BITS(ads1292r_reg.cfg2, ADS1292R_INT_FREQ, ADS1292R_INT_FREQ_DC) ; 
    /* ��ͨ��һ���������棬�����缫���� */
    ads1292r_reg.ch1set = ADS1292R_SET_BITS(ads1292r_reg.ch1set, ADS1292R_PDx, ADS1292R_CHx_ON) ;
    ads1292r_reg.ch1set = ADS1292R_SET_BITS(ads1292r_reg.ch1set, ADS1292R_GAINx, ADS1292R_GAIN_2) ;
    ads1292r_reg.ch1set = ADS1292R_SET_BITS(ads1292r_reg.ch1set, ADS1292R_MUXx, ADS1292R_CHx_INPUT_NORMAL) ;
    /* ��ͨ�������������棬�����缫���� */    
    ads1292r_reg.ch2set = ADS1292R_SET_BITS(ads1292r_reg.ch2set, ADS1292R_PDx, ADS1292R_CHx_ON) ;
    ads1292r_reg.ch2set = ADS1292R_SET_BITS(ads1292r_reg.ch2set, ADS1292R_GAINx, ADS1292R_GAIN_6) ;
    ads1292r_reg.ch2set = ADS1292R_SET_BITS(ads1292r_reg.ch2set, ADS1292R_MUXx, ADS1292R_CHx_INPUT_NORMAL) ;
    /* ����ͨ��һ������⹦�� */
    ads1292r_reg.resp1 = ADS1292R_SET_BITS(ads1292r_reg.resp1, ADS1292R_RESP_DEMOD_EN1, ADS1292R_DEMOD_EN1_ON) ;
    ads1292r_reg.resp1 = ADS1292R_SET_BITS(ads1292r_reg.resp1, ADS1292R_RESP_MOD_EN, ADS1292R_DEMOD_EN_ON) ;
    ads1292r_reg.resp1 = ADS1292R_SET_BITS(ads1292r_reg.resp1, ADS1292R_RESP_PH, ADS1292R_RESPPH_135) ;
    ads1292r_reg.resp1 = ADS1292R_SET_BITS(ads1292r_reg.resp1, ADS1292R_RESP_CTRL, ADS1292R_RESP_CTRL_INT) ;
    
    ads1292r_send_cmd(ADS1292R_COMMAND_SDATAC) ; /* ����ֹͣ������ģʽ */
    port_delay_ms(100) ;
    /* д������ */
    ads1292r_write_multiregs( ADS1292R_REG_ID, (uint8_t *)&ads1292r_reg, 12) ;
    port_delay_ms(10) ;
    
    ads1292r_send_cmd(ADS1292R_COMMAND_RDATAC) ; /* ��������ģʽ */
    port_delay_ms(10) ;		
    ads1292r_send_cmd(ADS1292R_COMMAND_START) ;	/* ���Ϳ�ʼ����ת������Ч������START���ţ� */	
    port_delay_ms(10) ;	
}

void ads1292r_test_adc_start()
{        
    /* �����ڲ������ź� */
    ads1292r_reg.cfg2 = ADS1292R_SET_BITS(ads1292r_reg.cfg2, ADS1292R_INT_TEST, ADS1292R_INT_TEST_ON) ; 
    ads1292r_reg.cfg2 = ADS1292R_SET_BITS(ads1292r_reg.cfg2, ADS1292R_INT_FREQ, ADS1292R_INT_FREQ_AC) ; 
    /* ��ͨ��һ���������棬ͨ��һ���ӵ�ͨ��һ */
    ads1292r_reg.ch1set = ADS1292R_SET_BITS(ads1292r_reg.ch1set, ADS1292R_PDx, ADS1292R_CHx_ON) ;
    ads1292r_reg.ch1set = ADS1292R_SET_BITS(ads1292r_reg.ch1set, ADS1292R_GAINx, ADS1292R_GAIN_6) ;
    ads1292r_reg.ch1set = ADS1292R_SET_BITS(ads1292r_reg.ch1set, ADS1292R_MUXx, ADS1292R_CHx_INPUT_TEST) ;
    /* ��ͨ�������������棬ͨ�������ӵ�ͨ���� */    
    ads1292r_reg.ch2set = ADS1292R_SET_BITS(ads1292r_reg.ch2set, ADS1292R_PDx, ADS1292R_CHx_ON) ;
    ads1292r_reg.ch2set = ADS1292R_SET_BITS(ads1292r_reg.ch2set, ADS1292R_GAINx, ADS1292R_GAIN_6) ;
    ads1292r_reg.ch2set = ADS1292R_SET_BITS(ads1292r_reg.ch2set, ADS1292R_MUXx, ADS1292R_CHx_INPUT_TEST) ;
    
    /* �ر�ͨ��һ������⹦�� */
    ads1292r_reg.resp1 = ADS1292R_SET_BITS(ads1292r_reg.resp1, ADS1292R_RESP_DEMOD_EN1, ADS1292R_DEMOD_EN1_OFF) ;
    ads1292r_reg.resp1 = ADS1292R_SET_BITS(ads1292r_reg.resp1, ADS1292R_RESP_MOD_EN, ADS1292R_DEMOD_EN_OFF) ;
    ads1292r_reg.resp1 = ADS1292R_SET_BITS(ads1292r_reg.resp1, ADS1292R_RESP_PH, ADS1292R_RESPPH_0) ;
    ads1292r_reg.resp1 = ADS1292R_SET_BITS(ads1292r_reg.resp1, ADS1292R_RESP_CTRL, ADS1292R_RESP_CTRL_EXT) ;      
    
    ads1292r_send_cmd(ADS1292R_COMMAND_SDATAC) ; /* ����ֹͣ������ģʽ */
    port_delay_ms(100) ;
    /* д������ */
    ads1292r_write_multiregs( ADS1292R_REG_ID, (uint8_t *)&ads1292r_reg, 12) ;
    port_delay_ms(10) ;
    
    ads1292r_send_cmd(ADS1292R_COMMAND_RDATAC) ; /* ��������ģʽ */
    port_delay_ms(10) ;		
    ads1292r_send_cmd(ADS1292R_COMMAND_START) ;	/* ���Ϳ�ʼ����ת������Ч������START���ţ� */	
    port_delay_ms(10) ;	
}

/* ��ȡת�����adԭʼ���� */
void ads1292r_get_value( uint8_t *ad_buf)
{
    uint8_t i ;
    
    while ( ADS1292_DRDY_GET()) ;   /* �ȴ�ת������ */
    
    ADS1292_CS_RESET() ;

    for ( i = 0; i < 9; i++)        /* ��ȡת����� */
    {	
        *ad_buf = port_spi_transmit_receive(0X00) ;	
        ad_buf++ ;
    }

    ADS1292_CS_SET() ;
}    


/**
  * @}
  */


