#include "sys.h" 
#include "lcd.h"
#include "Text.h"	
#include "string.h"												    
#include "usart.h"		

 

//////////////////////////////////////////////////////////////////////////////////	 
 
//������ʾ ��������	    

//DevEBox  ��Խ����
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com	
/******************************************************************************/								  


/**************************************************************************************/

//������ void Copy_Mem (unsigned char *P1, const unsigned char *P2,unsigned int Count)

//�������ܣ��ڲ��洢-��������

//DevEBox  ��Խ����
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com
/**************************************************************************************/

void Copy_Mem (unsigned char *P1, const unsigned char *P2,unsigned int Count)
{
   
   unsigned int i ;
   for(i=0;i<Count;i++)*P1++=*P2++;

  
}


/**************************************************************************************/

//������void Copy_HZK16(u8 *Dot, u8 num, u8 Q, u8 W)

//�������ܣ�������λ����ֺţ���ȡ��Ӧ�ĵ���

//DevEBox  ��Խ����
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com
/**************************************************************************************/

void Copy_HZK16(u8 *Dot, u8 num, u8 Q, u8 W)
{
	 unsigned short k;
	
	 for (k=0;k<hz16_num;k++) //�������ֿ�����Ҷ�Ӧ�ַ��Ĵ���
			{
			  if ((hz16[k].Index[0]==Q)&&(hz16[k].Index[1]== W))
			  {
					Copy_Mem(Dot,&hz16[k].Msk[0],num);
				}
			}
}

/**************************************************************************************/

//������void Copy_HZK16(u8 *Dot, u8 num, u8 Q, u8 W)

//�������ܣ�������λ����ֺţ���ȡ��Ӧ�ĵ���

//DevEBox  ��Խ����
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com
/**************************************************************************************/

void Copy_HZK24(u8 *Dot, u8 num, u8 Q, u8 W)
{
	 unsigned short k;
	
	 for (k=0;k<hz24_num;k++) //�������ֿ�����Ҷ�Ӧ�ַ��Ĵ���
			{
			  if ((hz24[k].Index[0]==Q)&&(hz24[k].Index[1]== W))
			  {
					Copy_Mem(Dot,&hz24[k].Msk[0],num);
				}
			}
}

/**************************************************************************************/
//������void Get_HzMat(u8 *code,u8 *mat,u8 size,u8 Font)
//�������ܣ�������λ����ֺţ���ȡ��Ӧ�ĵ���
//������ 
//code �ַ�ָ�뿪ʼ ���ֿ��в��ҳ���ģ
//mat  ���ݴ�ŵ�ַ (size/8+((size%8)?1:0))*(size) bytes��С	
//size:����������ݵĸ���
//Font:��������

//DevEBox  ��Խ����
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com
/**************************************************************************************/

void Get_HzMat(u8 *code, u8 *mat, u8 size, u8 Font)
{		    
	unsigned char qh,ql;
	unsigned char i;					  
	
		
	qh=*code;
	
	ql=*(++code);
	
	if(qh<0x81||ql<0x40||ql==0xff||qh==0xff)//�� ���ú���
	{   		    
	    for(i=0;i<size;i++)*mat++=0x00;//�������
	    return; //��������
	} 
	
	switch(Font)
	{
		case 12:
			//
			break;
		case 16:
			Copy_HZK16(mat,size, qh, ql);
			break;
		case 24:
			Copy_HZK24(mat,size, qh, ql);
			break;
			
	}     												    
}

/**************************************************************************************/
//������void Show_Font(u16 x,u16 y,u8 *font,u8 size,u16 color,u8 mode)
//�������ܣ���ʾһ��ָ����С�ĺ���
//������
//x,y :���ֵ�����
//font:������λ��
//size:�����С
//color,�ַ���ɫ

//mode:0,������ʾ,1,������ʾ	  

//DevEBox  ��Խ����
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com
/**************************************************************************************/

void Show_Font(u16 x,u16 y,u8 *font,u8 size,u16 color,u8 mode)
{
	u8 temp,t,t1;
	u16 x0=x;
	u8 dzk[72];
	u8 Num;
	
	Num=(size/8+((size%8)?1:0))*(size);//�õ�����һ���ַ���Ӧ������ռ���ֽ���	 
	
	if(size!=12&&size!=16&&size!=24)return;	//��֧�ֵ�size
	
	Get_HzMat(font,dzk,Num,size);	//�õ���Ӧ��С�ĵ������� 
	
	for(t=0;t<Num;t++)
	{   												   
		
		temp=dzk[t];			//�õ���������     
		
		for(t1=0;t1<8;t1++)
		{
			if(temp&0x80)LCD_Fast_DrawPoint(x,y,color);
			
			else if(mode==0)LCD_Fast_DrawPoint(x,y,BACK_COLOR);
			
			temp<<=1;
			
			x++;
			
			if((x-x0)==size)
			{
				x=x0;
				y++;
//				break;
			}
		}  	 
	}  
}

/**************************************************************************************/
//������Show_Str(u16 x,u16 y,u16 width,u16 height,u8*str,u8 size, u16 color, u8 mode)
//�������ܣ���ָ��λ�ÿ�ʼ��ʾһ���ַ�����֧���Զ�����	
//������
//(x,y):��ʼ����
//width,height:����
//str  :�ַ���
//size :�����С
//color,�ַ���ɫ
//mode:0,�ǵ��ӷ�ʽ;1,���ӷ�ʽ    	

//DevEBox  ��Խ����
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com
/**************************************************************************************/
void Show_Str(u16 x,u16 y,u16 width,u16 height, u8*str, u8 size, u16 color, u8 mode)
{					
	u16 x0=x;
	u16 y0=y;							  	  
  u8 bHz=0;     //�ַ���������  
		
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
		        else LCD_ShowChar(x,y,*str,size,color,mode);//��Ч����д�� 
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
						
	        if(y>(y0+height-size))break;//Խ�緵��  
						
	        Show_Font(x,y,str,size,color,mode); //��ʾ�������,������ʾ 
						
	        str+=2; 
	        x+=size;//��һ������ƫ��	    
        }						 
    }   
}

//**************************************************************************************/
//������Draw_Font16B(u16 x,u16 y, u16 color, u8*str)
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


void Draw_Font16B(u16 x,u16 y, u16 color, u8*str)
{
	u16 width;
	u16 height;
	
	width=lcddev.width-x;
	height=lcddev.height-y;
	
	Show_Str(x,y,width,height, str, 16, color, 0);
	
	
}

//**************************************************************************************/
//������void Draw_Font24B(u16 x,u16 y, u16 color, u8*str)
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

void Draw_Font24B(u16 x,u16 y, u16 color, u8*str)
{
	u16 width;
	u16 height;
	
	width=lcddev.width-x;
	height=lcddev.height-y;
	
	Show_Str(x,y,width,height, str, 24, color, 0);
	
	
}










/*******************************************************************************/

//DevEBox  ��Խ����

//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com
/*******************************************************************************/







		  






