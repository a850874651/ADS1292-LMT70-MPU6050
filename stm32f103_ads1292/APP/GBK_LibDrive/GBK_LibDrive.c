 

#include "GBK_LibDrive.h"	
#include "stm32f10x.h"	



//////////////////////////////////////////////////////////////////////////////////	



//�����ֿ�--��������	   

//DevEBox  ��Խ����
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com	

//********************************************************************************

////////////////////////////////////////////////////////////////////////////////// 	 


void GBK_Lib_Init(void)
{
	 	
	 #if    Used_FontIO
	  
	
	  GPIO_InitTypeDef  GPIO_InitStructure;	
	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOF, ENABLE);//ʹ��GPIOB,Fʱ��

		//PB1--SCLK ��ʼ������
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;            //PB1����Ϊ�������
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	  GPIO_Init(GPIOB, &GPIO_InitStructure);               //��ʼ��
	
    //PB2--MISO ��ʼ������
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;            //PB2 ����Ϊ��������
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		   //��������
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
    GPIO_Init(GPIOB, &GPIO_InitStructure);               //��ʼ��

		
		//PF11--CS ��ʼ������  //PF9--MOSI ��ʼ������
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_11;     //PF11�����������
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		        //�������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		         //IO���ٶ�Ϊ50MHz
	  GPIO_Init(GPIOF, &GPIO_InitStructure);                      //��ʼ��	
				
		FCLK_SET;//����״̬Ϊ�ߵ�ƽ
		
		#endif
		
		GBK_ReadID();	//��ȡ���ܹؼ��ֽ�. --ʹ���ֿ�ǰ�������ȶ�ȡһ���ֿ�ؼ��ַ�����
                  //ȷ���ֿ��Ѿ���������������ȱʧ�ַ�������
}


//////////////////////////////////////////////////////////////////////////////////	

//��ʱ����--��������	   

//DevEBox  ��Խ����
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com	

//********************************************************************************

////////////////////////////////////////////////////////////////////////////////// 	

void GBK_delay(unsigned char Time)
{
     unsigned char m,n;
	
     for(n=0;n<Time;n++)
	   {
      for(m=0;m<100;m++);
		 }
}

//////////////////////////////////////////////////////////////////////////////////	

//IO�ӿڶ�д����--��������	   

//DevEBox  ��Խ����
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com	

//********************************************************************************

////////////////////////////////////////////////////////////////////////////////// 


#if    Used_FontIO

unsigned char Font_SPI_WR(unsigned char byte)
{
	unsigned char bit_ctr;
	
	for(bit_ctr=0;bit_ctr<8;bit_ctr++)  // ���8λ
	{
		
		
		if((byte&0x80)==0x80)FDI_SET; 			// MSB TO MOSI
			else FDI_CLR; 

		FCLK_CLR;
		
		byte=(byte<<1);					// shift next bit to MSB
				
		byte|=FDO_IN;	        		// capture current MISO bit
		
		FCLK_SET;
		
	}
	
	FCLK_SET;//����״̬Ϊ�ߵ�ƽ
	
	return byte;
	
}

#endif




//********************************************************************************
//������void FontLib_Read(u8* pBuffer,u32 ReadAddr,u16 Num_Read) 
//��ȡSPI FLASH  
//��ָ����ַ��ʼ��ȡָ�����ȵ�����
//pBuffer:���ݴ洢��
//ReadAddr:��ʼ��ȡ�ĵ�ַ(24bit)
//Num_Read:Ҫ��ȡ���ֽ���(���65535)

//DevEBox  ��Խ����
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com	
//********************************************************************************

void FontLib_Read(u8* pBuffer,u32 ReadAddr,u16 Num_Read)   
{ 
 	  u16 i;  
	
	  Font_CS_EN;                           //ʹ������  
	
    Font_SPI_WR(FontRead_CMD);            //���Ͷ�ȡ����   
    Font_SPI_WR((u8)((ReadAddr)>>16));    //����24bit��ַ    
    Font_SPI_WR((u8)((ReadAddr)>>8));   
    Font_SPI_WR((u8)ReadAddr);   
    for(i=0;i<Num_Read;i++)
	  { 
        pBuffer[i]=Font_SPI_WR(0xFF);   //ѭ������  
    }
		
 	  Font_CS_SN;  		                      //ʧ������  
		
}


//********************************************************************************
//������void GBK_ReadID(void)

//�������ܣ���ȡ�ֿ���Ϣ�������ֿ���ã��������

//���ֿ��ͺ�ID--ʹ���ֿ�ǰ�������ȶ�ȡһ���ֿ⣬
//ȷ���ֿ��Ѿ���������������ȱʧ�ַ�������

//DevEBox  ��Խ����
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com	
//********************************************************************************
void GBK_ReadID(void)
{
	u8 Temp[24];
	u8 i;
	
	LCD_Clear(WHITE);//�����Ļ
	
	for(i=0;i<24;i++)Temp[i]=0;//��ʼ��������

  FontLib_Read(Temp,0,17);  
  DrawFont_GBK16B(16,16,RED,Temp);
	
	for(i=0;i<24;i++)Temp[i]=0;//��ʼ��������
  FontLib_Read(Temp,20,8);   	
	DrawFont_GBK16B(16,32,RED,Temp);
	
	for(i=0;i<24;i++)Temp[i]=0;//��ʼ��������
  FontLib_Read(Temp,30,8);   	
	DrawFont_GBK16B(16,48,RED,Temp);

  delay_ms(500);	//��ʱ��ʾ	--��ʾ���ֿ��Բ���ʾ����ȡ�Ǳ����
	
	
} 

//////////////////////////   ��ȡ����ASCII�����ַ� //////////////////////////////////////////////////////
//������void GBK_GetASC_Point(uint8_t *code, uint8_t *Pdot, uint8_t Font, uint16_t Num)
//*code���ַ�ָ�뿪ʼ-�ַ����Ŀ�ʼ��ַ,GBK��-���ֿ��в��ҳ���ģ
//*Pdot�����ݴ�ŵ�ַ (size/8+((size%8)?1:0))*(size) bytes��С	
// Font: �����ͺ�
// Num : �����С

//DevEBox  ��Խ����
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com	
//********************************************************************************

////////////////////////////////////////////////////////////////////////////////// 	 

void GBK_GetASC_Point(uint8_t *code, uint8_t *Pdot, uint8_t Font, uint16_t Num)
{		    
	 uint8_t QW;    //ASC�����
	 uint32_t  ADDRESS;
	
	 QW=*code;//��λ��--��ȡ���
	
	 //csize=(size/8+((size%8)?1:0))*(size/2);//�õ�����һ���ַ���Ӧ������ռ���ֽ���	 
	
	switch(Font)
	{

		case 12:
			ADDRESS=((unsigned long)QW*Num)+ASCII6x12_ST;	  //�õ��ֿ��е��ֽ�ƫ����  	
			break;
		case 16:
			ADDRESS=((unsigned long)QW*Num)+ASCII8x16_ST;	  //�õ��ֿ��е��ֽ�ƫ����  	
			break;
		case 24:
			ADDRESS=((unsigned long)QW*Num)+ASCII12x24_ST;	//�õ��ֿ��е��ֽ�ƫ����  
			break;
		case 32:
			ADDRESS=((unsigned long)QW*Num)+ASCII16x32_ST;	//�õ��ֿ��е��ֽ�ƫ����  
			break;
		case 48:
			ADDRESS=((unsigned long)QW*Num)+ASCII24x48_ST;	//�õ��ֿ��е��ֽ�ƫ����  
			break;
		case 64:
			ADDRESS=((unsigned long)QW*Num)+ASCII32x64_ST;	//�õ��ֿ��е��ֽ�ƫ����  
			break;
		
    default: return;
		
			
	} 

	FontLib_Read(Pdot,ADDRESS,Num);//��ȡ�����ַ�
	
}  


//////////////////////////   ��ָ��λ����ʾASCII�� �ַ�--�����ַ� //////////////////////////////////////////////////////
//������void GBK_ShowASCII(uint16_t x, uint16_t y, uint8_t *N_Word, uint8_t size, uint16_t D_Color, uint16_t B_Color, uint8_t mode)
//��ʾһ��ָ����С��ASC�ַ�

//x,y    : ASCII������--16λ
//N_Word : ASCII--���--8λ
//size   : �����С-�ֺ�-8λ
//D_Color����������ɫ--16λ
//B_Color��������ɫ--16λ
//mode:  0,������ʾ,1,������ʾ	--8λ

//DevEBox  ��Խ����
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com	
//********************************************************************************

////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 	

void GBK_ShowASCII(uint16_t x, uint16_t y, uint8_t *N_Word, uint8_t size, uint16_t D_Color, uint16_t B_Color, uint8_t mode)
{
	
	uint16_t csize; //�õ�����һ���ַ���Ӧ������ռ���ֽ���	 
	
	uint8_t temp;
	
	uint16_t t,t1;
	
	uint16_t y0=y;
	
	uint8_t dzk[256];  
	
	csize=(size/8+((size%8)?1:0))*(size/2);		//ASCII�ַ���Сռ������ֵĿ�ȣ��õ�����һ���ַ���Ӧ������ռ���ֽ���		 
	
	if(size!=12&&size!=16&&size!=24&&size!=32&&size!=48&&size!=64)return;	//��֧�ֵ�size
	
	GBK_GetASC_Point(N_Word,dzk,size,csize);	              //�õ���Ӧ��С�ĵ������� 
	
	for(t=0;t<csize;t++)
	{
		
		temp=dzk[t];			//�õ���������   
		
		for(t1=0;t1<8;t1++)//�������������ʾ����Ļ
		{
			if(temp&0x80) LCD_Fast_DrawPoint(x,y,D_Color);   //��ʾ�ַ�����
			
			else if(mode==0)LCD_Fast_DrawPoint(x,y,B_Color); //��ʾ������ɫ
			
			temp<<=1;
			
			y++;
			
			if((y-y0)==size)
			{
				y=y0;
				x++;
				break;
			}
		}  	 
	}  
}



 
//////////////////////////   ��ȡ������GBK�ֿ�--�����ַ� //////////////////////////////////////////////////////
//������void GBK_Lib_GetHz(uint8_t *code, uint8_t *Pdot, uint8_t Font, uint16_t Num)
//*code���ַ�ָ�뿪ʼ-�ַ����Ŀ�ʼ��ַ,GBK��-���ֿ��в��ҳ���ģ
//*Pdot�����ݴ�ŵ�ַ (size/8+((size%8)?1:0))*(size) bytes��С	
// Font: �����ͺ�
// Num : �����ַ�����

//DevEBox  ��Խ����
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com	
//********************************************************************************

////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 	


void GBK_Lib_GetHz(uint8_t *code, uint8_t *Pdot, uint8_t Font, uint16_t Num)
{		    
	 
	 uint8_t   qh,ql;
	 uint16_t   i;	
	 uint32_t  foffset;
	 uint32_t  ADDRESS;
	
	 //csize=(size/8+((size%8)?1:0))*(size);//�õ�����һ���ַ���Ӧ������ռ���ֽ���	 
	
	 qh=*code;       //����ַ�����λ��
	 ql=*(++code);   //����ַ�����λ��
	
	 if(qh<0x81||ql<0x40||ql==0xff||qh==0xff)//�ǳ��ú���
		{   		    
				for(i=0;i<Num;i++)*Pdot++=0x00;   //�������--0����ʾ
				return;                            //��������
		} 

		
		if(ql<0x7f)ql-=0x40;  //ע��!
		  else ql-=0x41;

		  qh-=0x81;

	
	foffset=((unsigned long)190*qh+ql)*Num;	//�õ��ֿ��е��ֽ�ƫ����  	
	
	switch(Font)
	{
    case 12:
			ADDRESS=foffset+GBK12x12_ST;     //����  16x16 �������ʼλ��
			break;
		case 16:
			ADDRESS=foffset+GBK16x16_ST;     //����  16x16 �������ʼλ��
			break;
		case 24:
			ADDRESS=foffset+GBK24x24_ST;     //����  24x24 �������ʼλ��
			break;
		case 32:
			ADDRESS=foffset+GBK32x32_ST;     //����  32x32 �������ʼλ��
			break;
		 default: return;
			
	} 

	FontLib_Read(Pdot,ADDRESS,Num);//��ȡ�����ַ�
	
} 


//////////////////////////   ��ָ��λ����ʾ�����ַ�--�����ַ� //////////////////////////////////////////////////////
//������void GBK_Show_Font(uint16_t x, uint16_t y, uint8_t *font, uint8_t size, uint16_t D_Color, uint16_t B_Color, uint8_t mode)

//��ʾһ��ָ����С�ĺ���
//x,y    : ASCII������     --16λ
//N_Word : ASCII--���     --8λ
//size   : �����С-�ֺ�   --8λ
//D_Color����������ɫ      --16λ
//B_Color��������ɫ        --16λ
//mode:  0,������ʾ,1,������ʾ	--8λ
	
//DevEBox  ��Խ����
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com	
//********************************************************************************

////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 	

void GBK_Show_Font(uint16_t x, uint16_t y, uint8_t *font, uint8_t size, uint16_t D_Color, uint16_t B_Color, uint8_t mode)
{
	
	uint16_t  csize;                                    //�õ�����һ���ַ���Ӧ������ռ���ֽ���	 
	uint8_t   temp,t,t1;
	uint16_t  y0=y;
	uint8_t   dzk[128];  
	
	csize=(size/8+((size%8)?1:0))*(size);              //�õ�����һ���ַ���Ӧ������ռ���ֽ���	 
	
	if(size!=12&&size!=16&&size!=24&&size!=32)return;	 //��֧�ֵ�size
	
	GBK_Lib_GetHz(font,dzk,size,csize);	                   //�õ���Ӧ��С�ĵ������� 
	
	for(t=0;t<csize;t++)
	 {   												   
		  temp=dzk[t];			                             //�õ���������   
		
			for(t1=0;t1<8;t1++)
			{
				if(temp&0x80)LCD_Fast_DrawPoint(x,y,D_Color);//��ʾ�ַ�����
				
				else if(mode==0)LCD_Fast_DrawPoint(x,y,B_Color); //��ʾ������ɫ
				
				temp<<=1;
				
				y++;
				
				if((y-y0)==size)
				{
					y=y0;
					x++;
					break;
				}
			}  	 
	}  
}




/////////////////////////////////////��ָ��λ����ʾ�ַ���///////////////////////////////////////////////////////////////////////////// 
//������void GBK_Show_Str(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t *str, uint8_t size, uint16_t D_Color, uint16_t B_Color, uint8_t mode)
//��ָ��λ�ÿ�ʼ��ʾһ���ַ���	    
//֧���Զ�����
//(x,y):��ʼ����
//width,height:������ʾ�ַ�������
//str  :�ַ���
//size :�����С
//D_Color����������ɫ      --16λ
//B_Color��������ɫ        --16λ
//mode:0,�ǵ��ӷ�ʽ;1,���ӷ�ʽ 

//DevEBox  ��Խ����
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com	
//********************************************************************************

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void GBK_Show_Str(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t *str, uint8_t size, uint16_t D_Color, uint16_t B_Color, uint8_t mode)
{					
	uint16_t x0=x;
	uint16_t y0=y;							  	  
  uint8_t bHz=0;     //�ַ���������  	    			

	
    while(*str!=0)//����δ����
    { 
        if(!bHz)
        {
	        if(*str>0x80)bHz=1;//���� 
	        else              //�ַ�
	        {      
            if(x>(x0+width-size/2))//����
							{				   
								y+=size;
								x=x0;	   
							}	
							
		        if(y>(y0+height-size))break;//Խ�緵��    
							
		        if(*str==13)//���з���
							{         
									y+=size;
									x=x0;
									str++; 
							}  
		        else GBK_ShowASCII(x, y, str, size, D_Color, B_Color, mode);  //LCD_ShowChar(x,y,*str,size,mode);//��Ч����д�� 
				    str++; 
		        x+=size/2; //�ַ�,Ϊȫ�ֵ�һ�� 
	        }
        }
				else//���� 
        {     
          bHz=0;//�к��ֿ�    
										
          if(x>(x0+width-size))//����
					{	    
						y+=size;
						x=x0;		  
					}
	        
					if(y>(y0+height-size))break;  //Խ�緵��  	
					
	        GBK_Show_Font(x,y,str,size, D_Color, B_Color, mode); //��ʾ�������,������ʾ 
					
	        str+=2; 
	        x+=size;//��һ������ƫ��	    
        }						 
    }   
}  

/////////////////////////////////////��ָ����ȵ��м���ʾ�ַ���///////////////////////////////////////////////////////////////////////////// 

//������void GBK_Show_StrMid(uint16_t x,uint16_t y, uint8_t size, uint8_t len, uint16_t D_Color, uint16_t B_Color,uint8_t*str)

//��ָ����ȵ��м���ʾ�ַ���
//����ַ����ȳ�����len,����GBK_Show__Str��ʾ
//len:ָ��Ҫ��ʾ�Ŀ��			  

//D_Color����������ɫ      --16λ
//B_Color��������ɫ        --16λ

//DevEBox  ��Խ����
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com	
//********************************************************************************

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void GBK_Show_StrMid(uint16_t x,uint16_t y, uint8_t size, uint8_t len, uint16_t D_Color, uint16_t B_Color,uint8_t*str)
{
	uint16_t strlenth=0;
		
  strlenth=strlen((const char*)str);
	strlenth*=size/2;
	if(strlenth>len)GBK_Show_Str(x,y,lcddev.width,lcddev.height,str,size,D_Color,B_Color,1);
	else
	{
		strlenth=(len-strlenth)/2;
	  GBK_Show_Str(strlenth+x,y,lcddev.width,lcddev.height,str,size,D_Color,B_Color,1);
	}
}   


//**************************************************************************************/
//������void DrawFont_GBK12B(u16 x,u16 y, u16 color, u8*str)
//�������ܣ���ָ��λ�ÿ�ʼ��ʾһ��12x12�����--�ַ�����֧���Զ�����(����Ļһ�е��յ���Զ�������һ��x���λ��)	
//������

//(x,y):��ʼ����
//color,�ַ���ɫ
//str  :�ַ���


//�ǵ��ӷ�ʽ;�ǵ����ַ��Ĳ��֣���䱳����ɫ

//DevEBox  ��Խ����
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com
//**************************************************************************************/


void DrawFont_GBK12B(u16 x,u16 y, u16 color, u8*str)
{
	u16 width;
	u16 height;
	
	width=lcddev.width-x;
	height=lcddev.height-y;
	
	GBK_Show_Str(x,y,width,height, str, 12, color,BACK_COLOR, 0);
	
	
}


//**************************************************************************************/
//������void DrawFont_GBK16B(u16 x,u16 y, u16 color, u8*str)
//�������ܣ���ָ��λ�ÿ�ʼ��ʾһ��16x16�����--�ַ�����֧���Զ�����(����Ļһ�е��յ���Զ�������һ��x���λ��)	
//������

//(x,y):��ʼ����
//color,�ַ���ɫ
//str  :�ַ���


//�ǵ��ӷ�ʽ;�ǵ����ַ��Ĳ��֣���䱳����ɫ

//DevEBox  ��Խ����
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com
//**************************************************************************************/


void DrawFont_GBK16B(u16 x,u16 y, u16 color, u8*str)
{
	u16 width;
	u16 height;
	
	width=lcddev.width-x;
	height=lcddev.height-y;
	
	GBK_Show_Str(x,y,width,height, str, 16, color,BACK_COLOR, 0);
	
	
}

//**************************************************************************************/
//������void DrawFont_GBK24B(u16 x,u16 y, u16 color, u8*str)
//�������ܣ���ָ��λ�ÿ�ʼ��ʾһ��24x24�����--�ַ�����֧���Զ�����(����Ļһ�е��յ���Զ�������һ��x���λ��)	
//������

//(x,y):��ʼ����
//color,�ַ���ɫ
//str  :�ַ���


//�ǵ��ӷ�ʽ;�ǵ����ַ��Ĳ��֣���䱳����ɫ

//DevEBox  ��Խ����
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com
//**************************************************************************************/

void DrawFont_GBK24B(u16 x,u16 y, u16 color, u8*str)
{
	u16 width;
	u16 height;
	
	width=lcddev.width-x;
	height=lcddev.height-y;
	
	GBK_Show_Str(x,y,width,height, str, 24, color,BACK_COLOR, 0);
	
	
}

//**************************************************************************************/
//������void DrawFont_GBK32B(u16 x,u16 y, u16 color, u8*str)
//�������ܣ���ָ��λ�ÿ�ʼ��ʾһ��32x32�����--�ַ�����֧���Զ�����(����Ļһ�е��յ���Զ�������һ��x���λ��)	
//������

//(x,y):��ʼ����
//color,�ַ���ɫ
//str  :�ַ���


//�ǵ��ӷ�ʽ;�ǵ����ַ��Ĳ��֣���䱳����ɫ

//DevEBox  ��Խ����
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com
//**************************************************************************************/

void DrawFont_GBK32B(u16 x,u16 y, u16 color, u8*str)
{
	u16 width;
	u16 height;
	
	width=lcddev.width-x;
	height=lcddev.height-y;
	
	GBK_Show_Str(x,y,width,height, str, 32, color,BACK_COLOR, 0);
	
	
}

//**************************************************************************************/
//������void DrawFontASC_GBK48B(u16 x,u16 y, u16 color, u8*str)
//�������ܣ���ָ��λ�ÿ�ʼ��ʾһ��24x48�����--ACSII�� �����ֿ�ֻ֧��ASCII�룩��֧���Զ�����(����Ļһ�е��յ���Զ�������һ��x���λ��)	
//������

//(x,y):��ʼ����
//color,�ַ���ɫ
//str  :�ַ���


//�ǵ��ӷ�ʽ;�ǵ����ַ��Ĳ��֣���䱳����ɫ

//DevEBox  ��Խ����
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com
//**************************************************************************************/

void DrawFontASC_GBK48B(u16 x,u16 y, u16 color, u8*str)
{
	u16 width;
	u16 height;
	
	width=lcddev.width-x;
	height=lcddev.height-y;
	
	GBK_Show_Str(x,y,width,height, str, 48, color,BACK_COLOR, 0);
	
	
}


//**************************************************************************************/
//������void DrawFontASC_GBK64B(u16 x,u16 y, u16 color, u8*str)
//�������ܣ���ָ��λ�ÿ�ʼ��ʾһ��32x64�����--ACSII�� �����ֿ�ֻ֧��ASCII�룩��֧���Զ�����(����Ļһ�е��յ���Զ�������һ��x���λ��)	
//������

//(x,y):��ʼ����
//color,�ַ���ɫ
//str  :�ַ���


//�ǵ��ӷ�ʽ;�ǵ����ַ��Ĳ��֣���䱳����ɫ

//DevEBox  ��Խ����
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com
//**************************************************************************************/

void DrawFontASC_GBK64B(u16 x,u16 y, u16 color, u8*str)
{
	u16 width;
	u16 height;
	
	width=lcddev.width-x;
	height=lcddev.height-y;
	
	GBK_Show_Str(x,y,width,height, str, 64, color,BACK_COLOR, 0);
	
	
}




//****************************************************************************************/
//������void GBK_LibFont_Test(void)
//��������: GBK����������ʾ����


//DevEBox  ��Խ����
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com
/****************************************************************************************/

void GBK_LibFont_Test(void)
{
	
	LCD_Clear(WHITE);
	
	DrawFont_GBK16B(24,16,BLUE,"2: GBK�ֿ�--��ʾ����");
	delay_ms(1000);
	
	LCD_Clear(WHITE);
	
	GBK_Show_Str(24,0,240,32,"ʮ���ֿ����",32,BLUE,WHITE,0);	
	GBK_Show_Str(16,40,240,16,"��ƣ���Խ����",16,BLUE,WHITE,0);	
	GBK_Show_Str(16,56,240,16,"From: mcudev.taobao.com",16,BLUE,WHITE,0);
	
	DrawFont_GBK12B(16,72,BLUE,"Date: 2019/05/08");

	GBK_Show_StrMid(16,96,12,200,BLUE,WHITE,"������ʾ����: 2019/05/08");//������ʾ	
								
	GBK_Show_Str(16,120,240,12,"����12x12-GBK�ֿ⣺",12,BLUE,WHITE,0);	//��ʾ������ֽ�
				
				
	GBK_Show_Str(16,136,240,16,"����16x16�ֿ⣺",16,BLUE,WHITE,0);	//��ʾ������ֽ�
				

	GBK_Show_Str(16,156,240,24,"24x24�ֿ⣺",24,BLUE,WHITE,0);	//��ʾ������ֽ�
				
				
	DrawFont_GBK32B(16,184,BLUE,"32x32�ֿ⣺");	//��ʾ������ֽ�
						 	
	//GBK_Show_Str(16,220,240,48,"48",48,D_Color,B_Color,0);
  DrawFontASC_GBK48B(16,220,BLUE,"48");

  //GBK_Show_Str(120,220,240,64,"64",64,D_Color,B_Color,0);	
	DrawFontASC_GBK64B(120,220,BLUE,"64");
	
	
	delay_ms(3000);	
}











		  






