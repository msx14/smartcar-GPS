#ifndef __ADCOLLECTION_H__
#define __ADCOLLECTION_H__

//��Ӧ��ϵ		LO_L =ad1;
//            LI_L =ad2;
//            M_L   =ad5;
//            RI_L = ad3;
//            RO_L =ad4;	
//	          belly_R_L=ad6;
//            belly_L_L=ad7;

void train_ad_collection();

#define LO_L_com ADC1_CH3_B17
#define LI_L_com ADC1_CH4_B19
#define M_L_com ADC2_CH4_B20
#define RI_L_com ADC1_CH6_B22
#define RO_L_com ADC1_CH5_B21
#define belly_L_L_com ADC2_CH3_B18
#define belly_R_L_com ADC1_CH7_B23

static float ad1_m=0;
static float ad2_m=0;
static float ad3_m=0;
static float ad4_m=0;
static float ad5_m=0;
static float ad6_m=0;
static float ad7_m=0;
		/*********************����Ϊ��ǰհ��������************************/
				static float LO_Lmax=-200;   //��T | ��ѵ��������ֵ
				static float LO_Lmin=200;   //��T | ��ѵ�������Сֵ
				static float LI_Lmax=-200;   //��T - ��ѵ��������ֵ
				static float LI_Lmin=200;   //��T - ��ѵ�������Сֵ
				static float M_Lmax=-200;   //�б�ѵ��������ֵ
				static float M_Lmin=200;   //�б�ѵ�������Сֵ
				static float RI_Lmax=-200;   //��T | ��ѵ��������ֵ
				static float RI_Lmin=200;   //��T | ��ѵ�������Сֵ
				static float RO_Lmax=-200;   //��T - ��ѵ��������ֵ
				static float RO_Lmin=200;   //��T - ��ѵ�������Сֵ
		/*************************����Ϊ�������������**************************/
				static float belly_R_Lmax=-200;   //�����ҵ�����ֵ
				static float belly_R_Lmin=200;   //�����ҵ����Сֵ
				static float belly_L_Lmax=-200;   //�����������ֵ
				static float belly_L_Lmin=200;   //����������Сֵ
				
#endif