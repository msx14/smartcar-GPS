#include "common.h"
#include  "CameraDisplay.h"
#include <GlobalVar.h>
#include "SEEKFREE_MT9V032.h"


unsigned char image_double[75][188],threshold=120;
signed int middleline[64];
//
//  @brief: ��64*80����ת��Ϊ8*80�����ݸ�Һ����ʾ
//  @param: unsigned char img64x80[], unsigned char img8x80[]
//  return: void
//  @note:  void    
//
extern float image_threshold;
void Screen_64x80Transform8x80(unsigned char img64x80[], unsigned char img8x80[])
{
	unsigned char *p_img64x80;
	unsigned char *p_img8x80;
	unsigned char temp_bit = 0;
	
  	p_img64x80 = img64x80;
	for(signed int i = 0; i < 64; i++)
	{
	  	p_img8x80 = &img8x80[80*(i>>3)];
	  	temp_bit = g_Bit_Val_Up[i & 0x07];
		for(signed int j = 0; j < 80; j++)
		{
			if( *(p_img64x80) == 0)
			  	*(p_img8x80) &= (~temp_bit);
			else
			  	*(p_img8x80) |= (temp_bit);
			p_img64x80++;
			p_img8x80++;
		}
	}
}

//
//  @brief:		�������8*40�����飨8λ����ʾ��Һ����
//  @param:		unsigned char arr[], unsigned position	//��Ҫ��ʾ�����ݵ�����������ʾ����ʼ��
//  @return:	void
//  @note:		��Dis_Camera_Picture�������
//
void Dis_Play_Data8x80(unsigned char arr[], unsigned position)
{
	signed int i = 0, j = 0;
	unsigned char *p_arr = arr;
	for(i = 0; i < 8; i++)
	{
		OLED_Set_Pos(position,i);
		for(j = 0; j < 80; j++)
		{
			OLED_Write_Data(*p_arr);
			p_arr++;
		}
	}	
}





//
//  @brief:  �Ƚ������һά����ת��������Һ����ʾ��8*40������
//			�ٵ��ú���Dis_Play_Data8x40(unsigned char arr[], unsigned position)��ʾͼ��
//  @param:  unsigned char img[], unsigned char position	ԭʼ��һλ����ͷ��õ���ʼλ��
//  @return: void
//  @note:   ��ʾ��Ҫ�õ�128�е����ݣ�Զ������0
//
void Dis_Camera_Picture128x320(unsigned char img[], unsigned char position)
{
  	unsigned char *p_img;
  
	unsigned char temp_img_64x80[64*80];
	unsigned char *p_temp_img_64x80 = temp_img_64x80;
	
	unsigned char temp_img_8x80[8*80];
	
	signed int i = 0, j = 0;

	for(i = 0; i < 64; i++)
	{

		  p_img = &img[80*i];
                  p_img+= 40*40;
			for(j = 0; j < 40; j++)
			{
			  	//��λ
			  	if( (*(p_img) & 0xF0) == 0 &&  (*(p_img+40) & 0xF0) == 0 )
				{
					(*p_temp_img_64x80) = 1;	
				}
				else
				{
					(*p_temp_img_64x80) = 0;
				}
				p_temp_img_64x80++;
				//��λ
				if( (*(p_img) & 0x0F) == 0 &&  (*(p_img+40) & 0x0F) == 0 )
				{
					(*p_temp_img_64x80) = 1;	
				}
				else
				{
					(*p_temp_img_64x80) = 0;
				}
				p_temp_img_64x80++;
				
				p_img++;
			}	
	}	
	Screen_64x80Transform8x80(temp_img_64x80,temp_img_8x80);
	Dis_Play_Data8x80(temp_img_8x80,position);
}

//��ʾ��ֵ�����ͼ��
void DispalyBinary(uint8 *p, uint16 position)
{
  int row = 61, col = 188;
  unsigned char BinaryImg[64][94];
  for (int i = 0; i < row; ++i)
  {
    for (int j = 0; j < 94; ++j)
    {
      if (50 >= *(p + 2 * j) || 50 >= *(p + 2 * j + 1))
      {
        BinaryImg[i][j] = 0;
      }
      else BinaryImg[i][j] = 255;
    }
    p += 188;
  }
  
  unsigned char DisOLEDImg[8 * 94] = { 0 };
  for (int i = 0; i < 8; i++)
  {
    OLED_Set_Pos(position,i);
    for (int j = 0; j < 94; ++j)
    {
      for (int k = 0; k < 8; ++k)
      {
        if (BinaryImg[i * 8 + k][j] != 0)
          DisOLEDImg[i * 94 + j] |= g_Bit_Val_Up[k];
      }
      OLED_Write_Data(DisOLEDImg[i * 94 + j]);
    }
  }
}
      
void DisPlayImage(void)
{
  DispalyBinary(image[UP_EAGE], 0);
}
      




