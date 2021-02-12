#ifndef _SEEKFREE_OELD_H
#define _SEEKFREE_OELD_H

#include "common.h"





/******************************************************/
/********************  ���ɽӿ�    ********************/
/**********t********************************************/


//----�궨��OLED����----	 
#define  OLED_SCL_PIN	B10
#define  OLED_SDA_PIN	B12
#define  OLED_RST_PIN	B8
#define  OLED_DC_PIN	B9
#define  OLED_CS_PIN	B11





#define Dot_Size 2                  // С�������λ



   


/*-----------------*OLEDдһ���ַ���*-----------------*/      

void OLED_Write_String(unsigned char x,unsigned char y,signed char String[]);

/*-----------------*OLEDдһ���ַ�*-------------------*/      

void OLED_Write_Char  (unsigned char x,unsigned char y,signed char Asc); 
// ���ø�ʽOLED_Write_Char(�У��У�ASCII��)
// OLED_Write_Char(1,1,'a')�ڵ�һ�У���һ�п�ʼ��ʾa

/*-----------------*OLEDдһ���ַ�*-------------------*/      

void OLED_Write_Draw  (unsigned char x,unsigned char y,signed char Asc); 
// ���ø�ʽOLED_Write_Draw(�У��У�ͼ�α��)
// OLED_Write_Draw(1,1,10)�ڵ�һ�У���һ����ʾ������
                                            
/*----------------*OLEDдһ����������*----------------*/      

void OLED_Write_Int   (unsigned char x,unsigned char y,signed int Number);

/*---------------*OLEDдһ������������*---------------*/

void OLED_Write_Float (unsigned char x,unsigned char y,float Number);

    
extern unsigned char Draw[];


/******************************************************/
/*******************  ASCII���ֿ�    ******************/
/******************************************************/
    
extern const unsigned char Font_8x16[1520];
extern const unsigned char gImage_xmdx[512];
extern const unsigned char gImage_xmdx1[512];
extern const unsigned char gImage_xmdx128[2048]; 

/******************************************************/
/********************  OLED����    ********************/
/******************************************************/

#define X_WIDTH 128
#define Y_WIDTH 64

/*--------------------*OLEDд����*--------------------*/

void OLED_Write_Data(unsigned char Data);


/*--------------------*OLEDд����*--------------------*/

void OLED_Write_Command(unsigned char Cmd);


/*-------------------*����ת�ַ���*-------------------*/

void OLED_Set_Pos(unsigned char x,unsigned char y);
 

/*-------------------*����ת�ַ���*-------------------*/

void OLED_Fill(unsigned char Bmp_data);


/*---------------------*OLED����*---------------------*/

void OLED_Clear(void);

  void OLED_IO_Init(void);
	void OLED_Init(void) ;
 

/*-------------------*����ת�ַ���*-------------------*/

signed int Int_To_String(signed long Int_Num,signed char String[]);


/*------------------*������ת�ַ���*------------------*/

signed int Float_To_String(float Float_Num,signed char String[]);
// Dot_SizeΪС�����߱���λ��
// �����ַ�������



/******************************************************/
/********************  ���ɽӿ�    ********************/
/******************************************************/

/*-----------------*OLEDдһ���ַ���*-----------------*/      

void OLED_Write_String(unsigned char x,unsigned char y,signed char String[]);


/*-----------------*OLEDдһ���ַ�*-------------------*/      

void OLED_Write_Char(unsigned char x,unsigned char y,signed char Asc); 


/*-----------------*OLEDдһ���ַ�*-------------------*/      

void OLED_Write_Draw(unsigned char x,unsigned char y,signed char Asc); 
      
              
                                               
/*----------------*OLEDдһ����������*----------------*/      

void OLED_Write_Int(unsigned char x,unsigned char y,signed int Number);


/*---------------*OLEDдһ������������*---------------*/

void OLED_Write_Float(unsigned char x,unsigned char y,float Number);

void Dis_Cursor(unsigned char Position,signed char Number);


/*---------------*OLEDдһ��16x16��*---------------*/
void Dis_Chinese16x16(unsigned char x,unsigned char y,unsigned char character_line);


#endif
