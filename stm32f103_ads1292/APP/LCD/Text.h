#ifndef __Text_H__
#define __Text_H__	 

#include "sys.h"

#include "font.h"

//////////////////////////////////////////////////////////////////////////////////	 
 
//������ʾ ��������	

//DevEBox  ��Խ����
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com	
/******************************************************************************/		 
 					     
void Get_HzMat(u8 *code,u8 *mat,u8 size,u8 Font);			//�õ����ֵĵ�����

void Show_Font(u16 x,u16 y,u8 *font,u8 size,u16 color,u8 mode);					//��ָ��λ����ʾһ������

void Show_Str(u16 x,u16 y,u16 width,u16 height,u8*str,u8 size, u16 color, u8 mode);	//��ָ��λ����ʾһ���ַ��� 

void Draw_Font16B(u16 x,u16 y, u16 color, u8*str);//��ָ��λ��--��ʾ 16x16 ��С�ĵ����ַ���

void Draw_Font24B(u16 x,u16 y, u16 color, u8*str);//��ָ��λ��--��ʾ 24x24 ��С�ĵ����ַ���


#endif
