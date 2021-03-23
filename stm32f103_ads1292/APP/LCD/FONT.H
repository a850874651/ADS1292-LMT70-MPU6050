#ifndef __FONT_H
#define __FONT_H 

/*******************************************************************************/

//DevEBox  ��Խ����

//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com
/*******************************************************************************/


extern const unsigned char asc2_1206[95][12]; //12*12 ASCII�ַ�������

extern const unsigned char asc2_1608[95][16]; //16*16 ASCII�ַ�������

extern const unsigned char asc2_2412[95][36]; //24*24 ASICII�ַ�������



//�����ֿ�洢����

struct typFNT_GB16
{
   unsigned char Index[2];	
   unsigned char Msk[32];
};



#define USE_ONCHIP_FLASH_FONT 1    //�����Ƿ���Ƭ���ֿ�

//����5��
#define hz16_num   56   //�˴������趨�ֿ⺺���ַ��Ĵ洢���ֵĸ����������ӻ��߼����ַ�����Ҫ����Ҳ��Ӧ�޸�

//���ӿƼ�Һ�����Գ�����ɫ���������ʾͼƬ��������ȫ�̼���֧��רע�����ɹ�

extern const struct typFNT_GB16 hz16[];


//�����ֿ�洢����

struct typFNT_GB24
{
       unsigned char Index[2];	
       unsigned char Msk[72];
};



#define hz24_num   9   //�˴������趨�ֿ⺺���ַ��Ĵ洢���ֵĸ����������ӻ��߼����ַ�����Ҫ����Ҳ��Ӧ�޸�

extern const struct typFNT_GB24 hz24[];




#endif




/*******************************************************************************/

//DevEBox  ��Խ����

//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com
/*******************************************************************************/




































