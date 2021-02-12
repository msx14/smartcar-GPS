/*!
 * 	@file       ZS_SD_Card.h
 * 	@brief      XMU SmartCar -> Group -> Camera
 * 	@author     ZP
 * 	@version    New Car
 * 	@date       The Tenth in 2015
 */

#ifndef _TF_CARD_H_
#define _TF_CARD_H_


#define SD_SAVE_FILE_NUM	1				//1Ϊ���ļ���0Ϊ���ļ�
#define	SD_PICTURE_NUM		98				//���ͼ������
#define SD_LINE_NUM		    239				//�ɼ������� 127+1

#define SD_SAVE_DATA_FLG    0
#if (SD_SAVE_DATA_FLG == 1)
    #define SD_DATA_NUM			GATHER_DATA_KIND*4	//�ɼ�����һ�е���������
#else
    #define SD_DATA_NUM			188				    //һ�е���������
#endif


extern unsigned int filebuffoffset;
extern unsigned char SD_Num[20];
void sd_init(void);
void SD_storage_Gray(unsigned char i,unsigned char sdarray[],unsigned char LINE_NUM_MAX);
void SD_Gather_Camera_Picture_120x188(void);
char Getchar(int buff,int frac);
void getData(void);





#endif