#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "key.h"
#include "lcd.h"
#include "mpu6050.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h" 

//ALIENTEK ̽����STM32F407������ ʵ��32
//MPU6050���ᴫ���� ʵ�� -�⺯���汾
//����֧�֣�www.openedv.com
//�Ա����̣�http://eboard.taobao.com  
//������������ӿƼ����޹�˾  
//���ߣ�����ԭ�� @ALIENTEK

//����1����1���ַ� 
//c:Ҫ���͵��ַ�
void usart1_send_char(u8 c)
{

	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET); 
    USART_SendData(USART1,c);   

} 
//�������ݸ�����������λ�����(V2.6�汾)
//fun:������. 0XA0~0XAF
//data:���ݻ�����,���28�ֽ�!!
//len:data����Ч���ݸ���
void usart1_niming_report(u8 fun,u8*data,u8 len)
{
	u8 send_buf[32];
	u8 i;
	if(len>28)return;	//���28�ֽ����� 
	send_buf[len+3]=0;	//У��������
	send_buf[0]=0X88;	//֡ͷ
	send_buf[1]=fun;	//������
	send_buf[2]=len;	//���ݳ���
	for(i=0;i<len;i++)send_buf[3+i]=data[i];			//��������
	for(i=0;i<len+3;i++)send_buf[len+3]+=send_buf[i];	//����У���	
	for(i=0;i<len+4;i++)usart1_send_char(send_buf[i]);	//�������ݵ�����1 
}
//���ͼ��ٶȴ��������ݺ�����������
//aacx,aacy,aacz:x,y,z������������ļ��ٶ�ֵ
//gyrox,gyroy,gyroz:x,y,z�������������������ֵ
void mpu6050_send_data(short aacx,short aacy,short aacz,short gyrox,short gyroy,short gyroz)
{
	u8 tbuf[12]; 
	tbuf[0]=(aacx>>8)&0XFF;
	tbuf[1]=aacx&0XFF;
	tbuf[2]=(aacy>>8)&0XFF;
	tbuf[3]=aacy&0XFF;
	tbuf[4]=(aacz>>8)&0XFF;
	tbuf[5]=aacz&0XFF; 
	tbuf[6]=(gyrox>>8)&0XFF;
	tbuf[7]=gyrox&0XFF;
	tbuf[8]=(gyroy>>8)&0XFF;
	tbuf[9]=gyroy&0XFF;
	tbuf[10]=(gyroz>>8)&0XFF;
	tbuf[11]=gyroz&0XFF;
	usart1_niming_report(0XA1,tbuf,12);//�Զ���֡,0XA1
}	
//ͨ������1�ϱ���������̬���ݸ�����
//aacx,aacy,aacz:x,y,z������������ļ��ٶ�ֵ
//gyrox,gyroy,gyroz:x,y,z�������������������ֵ
//roll:�����.��λ0.01�ȡ� -18000 -> 18000 ��Ӧ -180.00  ->  180.00��
//pitch:������.��λ 0.01�ȡ�-9000 - 9000 ��Ӧ -90.00 -> 90.00 ��
//yaw:�����.��λΪ0.1�� 0 -> 3600  ��Ӧ 0 -> 360.0��
void usart1_report_imu(short aacx,short aacy,short aacz,short gyrox,short gyroy,short gyroz,short roll,short pitch,short yaw)
{
	u8 tbuf[28]; 
	u8 i;
	for(i=0;i<28;i++)tbuf[i]=0;//��0
	tbuf[0]=(aacx>>8)&0XFF;
	tbuf[1]=aacx&0XFF;
	tbuf[2]=(aacy>>8)&0XFF;
	tbuf[3]=aacy&0XFF;
	tbuf[4]=(aacz>>8)&0XFF;
	tbuf[5]=aacz&0XFF; 
	tbuf[6]=(gyrox>>8)&0XFF;
	tbuf[7]=gyrox&0XFF;
	tbuf[8]=(gyroy>>8)&0XFF;
	tbuf[9]=gyroy&0XFF;
	tbuf[10]=(gyroz>>8)&0XFF;
	tbuf[11]=gyroz&0XFF;	
	tbuf[18]=(roll>>8)&0XFF;
	tbuf[19]=roll&0XFF;
	tbuf[20]=(pitch>>8)&0XFF;
	tbuf[21]=pitch&0XFF;
	tbuf[22]=(yaw>>8)&0XFF;
	tbuf[23]=yaw&0XFF;
	usart1_niming_report(0XAF,tbuf,28);//�ɿ���ʾ֡,0XAF
} 
int main(void)
{
	char unStepCount=0;             //��ʼ����
	unsigned long unStepCountTmp=0;
	int rt;
	float juli=0.0;    //�ⶨ����
	short temp;       
	float bushu;    //����

    delay_init(168);                     //��ʱ������ʼ��          
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);         //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);   //���ڳ�ʼ��Ϊ115200
	LED_Init();          //LED�˿ڳ�ʼ��
	LCD_Init();          //LCD��ʼ��
	MPU_Init();          //mpu6050��ʼ��
	KEY_Init();          //������ʼ��

	POINT_COLOR=RED;     //��������Ϊ��ɫ   
	LCD_ShowString(30,50,200,24,24,"Pedometer");
	LCD_ShowString(50,90,200,24,24,"Powered by WU");

	POINT_COLOR=BLUE;                                  //��������Ϊ��ɫ
	LCD_ShowString(30,200,200,16,16," Temp:    . C");       
	LCD_ShowString(30,220,200,16,16," bushu:    ");
	LCD_ShowString(30,240,200,16,16," juli:      m");

	while(mpu_dmp_init())  //���MPU6050��û������
	{
		 LCD_ShowString(30,130,200,16,16,"mpu6050 error");
		 delay_ms(200);
		 LCD_Fill(30,130,239,130+16,WHITE);                      //ʣ��λ��lcd��ɫ���
		 delay_ms(200);
	}
	
	LCD_ShowString(30,130,200,16,16,"mpu6050 ok");            //dmp��ʼ��
	dmp_set_pedometer_step_count(unStepCount);                //���üƲ���������ֵΪ0
	
	while(1)
	{
		temp = MPU_Get_Temperature();        //�õ��¶�ֵ
		if(temp<0)
		{
			LCD_ShowChar(30+48,200,'-',16,0);      //��ʾ����
			temp=-temp;                //תΪ����
		}
		else
		{
			LCD_ShowChar(30+48,200,' ',16,0);                //ȥ������
		}			
		
		LCD_ShowNum(30+48+8,200,temp/100,3,16);                //��ʾ��������            
		LCD_ShowNum(30+48+40,200,temp%10,1,16);                //��ʾС������
	
	    rt = dmp_get_pedometer_step_count(&unStepCountTmp);   //�õ�����    ����0��ʾ�������óɹ�
	    if(rt == 0)
		 {
		     if(unStepCountTmp != unStepCount)  //�ͼ�����ֵ�Ƚ�
			 {
				 bushu = unStepCountTmp;        //��Ų���
				  //unStepCount = unStepCountTmp;
				  LCD_ShowNum(30+48+8,220,bushu,3,16);                   //��ʾ��������            
								 printf("step:%.3f\n",bushu);
			
				 juli = 0.6 * bushu;
				 printf("instance:%.3f\n",juli);			   
				delay_ms(1000);
				 LCD_ShowNum(30+48+8,240,juli,3,16);                     //��ʾ��������           
//				 LCD_ShowNum(30+48+8,240,juli%10,1,16);                     //��ʾ��������    				 
			  }
		  }
	}
}
  
//int main(void)
//{ 
//	u8 t=0,report=1;			//Ĭ�Ͽ����ϱ�
//	u8 key;
//	float pitch,roll,yaw; 		//ŷ����
//	short aacx,aacy,aacz;		//���ٶȴ�����ԭʼ����
//	short gyrox,gyroy,gyroz;	//������ԭʼ����
//	short temp;					//�¶�
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
//	delay_init(168);  //��ʼ����ʱ����
//	uart_init(115200);		//��ʼ�����ڲ�����Ϊ500000
//	LED_Init();					//��ʼ��LED 
//	KEY_Init();					//��ʼ������
// 	LCD_Init();					//LCD��ʼ��
//	MPU_Init();					//��ʼ��MPU6050
// 	POINT_COLOR=RED;//��������Ϊ��ɫ 
//	LCD_ShowString(30,50,200,16,16,"Explorer STM32F4");	
//	LCD_ShowString(30,70,200,16,16,"MPU6050 TEST");	
//	LCD_ShowString(30,90,200,16,16,"ATOM@ALIENTEK");
//	LCD_ShowString(30,110,200,16,16,"2014/5/9");
//	while(mpu_dmp_init())
//	{
//		LCD_ShowString(30,130,200,16,16,"MPU6050 Error");
//		delay_ms(200);
//		LCD_Fill(30,130,239,130+16,WHITE);
// 		delay_ms(200);
//	}
//	LCD_ShowString(30,130,200,16,16,"MPU6050 OK");
//	LCD_ShowString(30,150,200,16,16,"KEY0:UPLOAD ON/OFF");
//	POINT_COLOR=BLUE;//��������Ϊ��ɫ 
// 	LCD_ShowString(30,170,200,16,16,"UPLOAD ON ");	 
// 	LCD_ShowString(30,200,200,16,16," Temp:    . C");	
// 	LCD_ShowString(30,220,200,16,16,"Pitch:    . C");	
// 	LCD_ShowString(30,240,200,16,16," Roll:    . C");	 
// 	LCD_ShowString(30,260,200,16,16," Yaw :    . C");	 
// 	while(1)
//	{
//		key=KEY_Scan(0);
//		if(key==KEY0_PRES)
//		{
//			report=!report;
//			if(report)LCD_ShowString(30,170,200,16,16,"UPLOAD ON ");
//			else LCD_ShowString(30,170,200,16,16,"UPLOAD OFF");
//		}
//		if(mpu_dmp_get_data(&pitch,&roll,&yaw)==0)
//		{ 
//			temp=MPU_Get_Temperature();	//�õ��¶�ֵ
//			MPU_Get_Accelerometer(&aacx,&aacy,&aacz);	//�õ����ٶȴ���������
//			MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);	//�õ�����������
//			if(report)mpu6050_send_data(aacx,aacy,aacz,gyrox,gyroy,gyroz);//���Զ���֡���ͼ��ٶȺ�������ԭʼ����
//			if(report)usart1_report_imu(aacx,aacy,aacz,gyrox,gyroy,gyroz,(int)(roll*100),(int)(pitch*100),(int)(yaw*10));
//			if((t%10)==0)
//			{ 
//				if(temp<0)
//				{
//					LCD_ShowChar(30+48,200,'-',16,0);		//��ʾ����
//					temp=-temp;		//תΪ����
//				}else LCD_ShowChar(30+48,200,' ',16,0);		//ȥ������ 
//				LCD_ShowNum(30+48+8,200,temp/100,3,16);		//��ʾ��������	    
//				LCD_ShowNum(30+48+40,200,temp%10,1,16);		//��ʾС������ 
//				temp=pitch*10;
//				if(temp<0)
//				{
//					LCD_ShowChar(30+48,220,'-',16,0);		//��ʾ����
//					temp=-temp;		//תΪ����
//				}else LCD_ShowChar(30+48,220,' ',16,0);		//ȥ������ 
//				LCD_ShowNum(30+48+8,220,temp/10,3,16);		//��ʾ��������	    
//				LCD_ShowNum(30+48+40,220,temp%10,1,16);		//��ʾС������ 
//				temp=roll*10;
//				if(temp<0)
//				{
//					LCD_ShowChar(30+48,240,'-',16,0);		//��ʾ����
//					temp=-temp;		//תΪ����
//				}else LCD_ShowChar(30+48,240,' ',16,0);		//ȥ������ 
//				LCD_ShowNum(30+48+8,240,temp/10,3,16);		//��ʾ��������	    
//				LCD_ShowNum(30+48+40,240,temp%10,1,16);		//��ʾС������ 
//				temp=yaw*10;
//				if(temp<0)
//				{
//					LCD_ShowChar(30+48,260,'-',16,0);		//��ʾ����
//					temp=-temp;		//תΪ����
//				}else LCD_ShowChar(30+48,260,' ',16,0);		//ȥ������ 
//				LCD_ShowNum(30+48+8,260,temp/10,3,16);		//��ʾ��������	    
//				LCD_ShowNum(30+48+40,260,temp%10,1,16);		//��ʾС������  
//				t=0;
//				LED0=!LED0;//LED��˸
//			}
//		}
//		t++; 
//	} 	
//}
