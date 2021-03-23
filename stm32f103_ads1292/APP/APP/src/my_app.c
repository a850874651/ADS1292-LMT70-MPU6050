/**
  ******************************************************************************
  * @file           : my_app.c
  * @brief          : ����Ӧ�ó���Դ�ļ�
  * @details        : ��ʾ���ʹ��ads1292�ӿں�����˫ͨ��ͨ��һ�����������Σ�ͨ����
  *                   �����ĵ粨�Σ�2.42v�ڲ��ο���ѹ��500sps�����ʣ�ͨ��һͨ������
  *                   �棬�����������档�ϵ�2-3���ʼ������ݡ��������ṩ��
  *                   ��λ���������ɷֱ𿴵�����ͼ���ĵ�ͼ��ע�⣺������δ���������˲�
  *                   ��ԭʼ�ź����Ի��й�Ƶ���ţ�ʹ�õ�أ�������Դ��������߰ε�����
  *                   ���������������͸��š�
  * @author         : WJXZZ
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

/* Includes ------------------------------------------------------------------*/
#include "my_app.h"
#include "lcd.h"
#include "ads1292r.h"
#include "delay.h"
#include "usart2.h"
/** @addtogroup My_App
  * @{
  */
/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
#define WINDOWS_LENGTH 300
uint8_t ad_b[9] ;   /* �洢ԭʼ���� */
int32_t ad_rr[2] ;  /* ת�����i32���� */
int32_t ad_rr2[2] ;  /* ת�����i32���� */
uint8_t ads_frame_tx[11] = { 0xAA, 0xAA} ;  /* Э�� */
int heart_sum[300]= {0}; ///��������ڴ�˵����
float h_freq=0;
//float min;
//int h_i=0;

/////ת�����ַ����õ����� ��ʵ������
char h_str[80];
char h_str2[150];
char h_str3[80];
char h_str4[80];

//// forѭ��ʹ�õ�ֵ////
int h_j;
//float j[5]={500,500,500,500,500};
double heart_avg=0;//ƽ��ֵ
double yu=0; ///��ֵ
//	int heart_max=0;//���ֵ
int h_index=0; //��һ�����ֵ��x��

int h_instance=0;//������ľ���
double all_avg=0;  ///��38�����ʵ�ƽ��ֵ
int all_flag=0; //�ж�38�������flag
double all_sum=0;//����38�����ʵ��ܺ�
char h_all_avg[80]; //��������ƽ��ֵ������ ת��Ϊchar���õ�
int tmp=0; //����ı���ֵ
int h_x=0;
int h_windows=0;
u8 end=0;
u8 end2=0;
unsigned long hea_sum=0;
typedef struct heart_max  ///������ʵĽṹ��
{
    int value;
    int index;
} heart_max_list;
heart_max_list max;
/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/

/* 24λ�з�����ת����24λ�޷���������� */
int32_t i24toi32( uint8_t *p_i32)
{
    int32_t rev = 0 ;

    rev = ( ( (int32_t)p_i32[0]) << 16)
          | ( ( (int32_t) p_i32[1]) << 8) | ( (int32_t) p_i32[2]) ;

    if ( ( p_i32[0] & 0x80) == 0x80)
    {
        rev |= 0xFF000000 ;
    }

    return rev ;
}

/* ����λ������ads���ݣ����Ժ��� */
void tx_ads_data( uint8_t *str, int32_t *ad)
{
    uint8_t i ;

    str[2] = ad[0] >> 24 ;  /* ���ͨ��һ���ݣ���� */
    str[3] = ad[0] >> 16 ;
    str[4] = ad[0] >> 8 ;
    str[5] = ad[0] ;

    str[6] = ad[1] >> 24 ;  /* ���ͨ�������ݣ���� */
    str[7] = ad[1] >> 16 ;
    str[8] = ad[1] >> 8 ;
    str[9] = ad[1] ;

    /* �������� */
    for ( i = 0; i < 10; i++)
    {
        while((USART1->SR&0X40)==0) ;   /* ѭ������,ֱ��������� */
        USART1->DR = str[i] ;
    }
}



/* Ӧ�����ʼ�� */
void my_app_init()
{
    while(ads1292r_init( 5) == 0) ; /* ��ʼ��ads1292 */

    /* ˫ͨ���ɼ��������ĵ��źţ�����ģʽ������Ҫ�������� */
    ads1292r_normal_adc_start() ;

    /* ˫ͨ����ʼ�ɼ��ڲ������ź�ͨ����1HZ������ */
    /* ads1292r_test_adc_start(void) ; */
}
void clear_point(u16 hang)
{
    u16 index_clear_lie = 0;
//	u8 jg=0;
    POINT_COLOR = WHITE;
    for(index_clear_lie = 0; index_clear_lie <320; index_clear_lie++)
    {
        lcd_huadian(hang,index_clear_lie);

    }

    POINT_COLOR=WHITE;
}
void my_app()
{
    ads1292r_get_value( ad_b) ; /* ��ȡԭʼ���� */
    ad_rr[1] = i24toi32(ad_b+6) ;  /* ת��ԭʼ���� */
    max.value=heart_sum[0];  //�����ֵ��ֵ����ֵ
    for(h_j=0; h_j<WINDOWS_LENGTH; h_j=h_j+1)
    {
        ads1292r_get_value( ad_b) ; /* ��ȡԭʼ���� */
        ad_rr[1] = i24toi32(ad_b+6) ;  /* ת��ԭʼ���� */
        tx_ads_data( ads_frame_tx, ad_rr)  ;    /* ����λ���������� */
        heart_sum[h_j]=ad_rr[1]; //���j��ֵ��ȥ
        hea_sum+=ad_rr[1]; //�����ֵ
			////////////////�����ֵ //////////////////
        if(max.value>heart_sum[h_j]) //�ѵ�һ��ֵ�����ж�  ���jλ�ϵ���ֵС�ڳ�ֵ
        {
            max.value=max.value;  //�����ֵ��ֵ����ֵ
            max.index=max.index;
        } else if(max.value<heart_sum[h_j])
        {
            max.value=heart_sum[h_j];
            max.index=h_j;
        }
        else if(max.value==heart_sum[h_j])
        {
            max.value=heart_sum[h_j];
            max.index=h_j;
        }
			////////////////�����ֵ //////////////////
    }
    heart_avg=hea_sum/300.0;//����ƽ��ֵ
    yu=max.value/heart_avg;//��ֵ
		
		//����ͨ����������ȥ������ֵ���ﵽ���ʼ����Ŀ��
//			sprintf(h_str2,"avg:%f,max:%d,index:%d,sum:%ld,yu:%lf\n",heart_avg,max.value,max.index,hea_sum,yu);
//			Usart2_SendStr_length(h_str2,65);
    hea_sum=0;


    if((yu>1.05&&yu<1.22)||(yu>1.3)) //��ֵ�ﵽ���һ������ʱ
    {
//        Usart2_SendStr_length("abc\n",4);
			if(end2==1) //�������ζ������岨  ^^
			{
				h_windows=2;//�ô��ڵ�ֵ���2
				h_index=max.index;
				h_instance=h_x+h_index;
				h_x=WINDOWS_LENGTH-h_index;
				end2=0;
				end=0;
			}
			else
			{
				h_windows++;//1 2  1  //���һ������
        h_index=max.index;//130 140  160  //��ǰλ��Ϊ���ֵλ��
        h_instance=h_x+h_index;//130  150+140  140+160  //����ľ�����ڵ�ǰλ�õĵ��´������λ��
        h_x=WINDOWS_LENGTH-h_index;//150 140 120  //�´������λ��
        end=0;
			}
       
				

    }
    if(yu<=1.03||(yu<=1.25&&yu>=1.18)) //�ж���ֵ�������岨ʱ
    {


            h_x+=300;  //ֱ�Ӽ��ϴ��ľ���
//            sprintf(h_str4,"h_instance:%d\n",h_instance);
//            Usart2_SendStr_length(h_str4,14);

    }

    if(h_windows==2)  //�������������
    {

        end=1;  //�ж�������ж�ֵ
				end2=1;  //�ж��Ƿ�����������������
//        tmp=300-h_index	;  //
        h_freq=h_instance;  //����ת�ɸ�����
 ///////////  ��ʾһ����û��ת���ɹ�  /////////////////////////
//        sprintf(h_str3,"freq1:%d\n",h_instance);
//        Usart2_SendStr_length(h_str3,12);
///////////     ///////////////////////////
        h_freq=60*500/h_freq;//�������������
        h_windows=0;  //�������������������

        h_instance=0;  //��ε�����������ľ�������
			
			if(h_freq<150&&h_freq>50){   //������ʴ���50С��150
        sprintf(h_str,"heart_rate:%.3f\n",h_freq);
        Usart2_SendStr_length(h_str,18);
				all_sum+=h_freq;//��������38���ܺ�
				all_flag++;
				if(all_flag%38==0){//ÿ��38���ͷ���ƽ��ֵ
					all_avg=all_sum/38;//����38�ε�ƽ��ֵ
					sprintf(h_all_avg,"HR_avg:%.3f\n",all_avg);
					Usart2_SendStr_length(h_all_avg,14);
					all_sum=0;
					all_flag=0;
				
				}
					
			}
    }

}
////  ������LCD����ʾ���� ///////  �������ע����
/* Ӧ�ó��� */
//void my_app()
//{
//    int j;
////		int hea_avg;
////		int hea_max;
////		int index;
////		int windows=0;
////		int windows_avg=0;
////	u32 ECG1,ECG_avg;
//    ads1292r_get_value( ad_b) ; /* ��ȡԭʼ���� */
//
//    ad_rr[0] = i24toi32(ad_b+3) ;  /* ת��ԭʼ���� */
//    ad_rr[1] = i24toi32(ad_b+6) ;  /* ת��ԭʼ���� */

//			tx_ads_data( ads_frame_tx, ad_rr)  ;    /* ����λ���������� */
//    for(j=0; j<280; j=j+1)
//    {


////        arr=(ad_rr[0]-250000)/1000;//������y��

////        arr_2=(ad_rr[1]-1150000)/1000;//���ʵ�y��
//        ads1292r_get_value( ad_b) ; /* ��ȡԭʼ���� */
////        ad_rr[0] = i24toi32(ad_b+3) ;  /* ת��ԭʼ���� */
//        ad_rr[1] = i24toi32(ad_b+6) ;  /* ת��ԭʼ���� */
////        tx_ads_data( ads_frame_tx, ad_rr)  ;    /* ����λ���������� */
////        arr_21=(ad_rr[1]-1150000)/1000;//���ʵڶ��β�����y��
//        heart_sum[j]+=ad_rr; //���j��ֵ��ȥ
////        heart_sum[j+1]+=arr_21;		//���j+1��ֵ��ȥ��
////        if(j==49||j==99||j==199||j==249)
////        {
////            hea_avg=heart_avg(heart_sum,j);
////        }
////				if(arr_2>hea_avg)
////				{
////					index=j;
////			//			hea_max=arr_2;
////					windows++;
////				}
////				if(arr_21>hea_avg)
////				{
////					index=j+1;
////					windows++;
////			//			hea_max=arr_21;
////				}
////				if(j==279)
////				{
////					windows_avg=windows/60;
////				}
////						clear_point(j);
////						LCD_DrawPoint(j,arr_2);
////						LCD_DrawLine(j,320-arr_2,j+1,320-arr_21,BLACK);


//    }

//			printf("breath:%d",ad_rr[0]);
//		printf("breath:%d",ad_rr[1]);
//}

/**
  * @}
  */


