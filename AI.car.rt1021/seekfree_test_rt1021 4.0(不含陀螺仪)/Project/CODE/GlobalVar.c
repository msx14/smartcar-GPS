#include <GlobalVar.h>
#include "headfile.h"
//========================ģ�ͼ���===================================//
int count=0;
int count_flag=0;
//		int cie_data[7];
		int ad1,ad2,ad3,ad4,ad5,ad6,ad7;//�������ߴ��䣨��У� 
		int smotor_num=0;//�������ߴ��䣨�����ţ�
//=========================ѵ���ɼ��л�=============================//
		int g_convert_flag =0; //flag=0ʱΪ����вɼ�����ʱ�ɳ�ǰհ��п��ƶ��
													//flag=1ʱΪ�̵�вɼ�����ʱ�ɶ�ǰհ��п��ƶ��
													//flag=2ʱΪģ��ѵ��������Χ�ĵ�п��ƶ��
													//flag=3ʱΪ�ֶ�ģʽ��ֱ���ֶ����ƶ�����
//============================���=================================//
		int adc_read=0; //adc_read%2=1��ʱ��Ϊ�����Сֵ����
										//adc_read%2=0ʱΪ���ƣ���ʱ�����ʼ���
		float edge1=0.71,edge2=0.35;//·���жϣ�Ŀǰ���ã�
		float straight_k=0.74,small_curve_k=0.74,large_curve_k=0.74;//ģ��pid��Ŀǰ���ã�
		/******************����Ϊ��ǰհ��������***************************/
				float LO_L=-1,LI_L=-1,M_L=-1,RI_L=-1,RO_L=-1;
				float LO_L_r1=0.01,LI_L_r1=0.01,M_L_r1=0.01,RI_L_r1=0.01,RO_L_r1=0.01;
				float LO_L_r1_last=0.0,LI_L_r1_last=0.0,M_L_r1_last=0.0,RI_L_r1_last=0.0,RO_L_r1_last=0.0;
		/*****************����Ϊ�������������****************************/
				float belly_R_L=-1,belly_L_L=-1;
				float belly_R_L_r1=0.01,belly_L_L_r1=0.01; 
				float belly_R_L_r1_last=0.0,belly_L_L_r1_last=0.0;
		/*******************����Ϊ��ǰհ��������***********************/
				float outL_L=-1,outM_L=-1,outR_L=-1;
				float outL_L_r1=0.01,outM_L_r1=0.01,outR_L_r1=0.01;
				float outM_L_r1_last=0.0,outR_L_r1_last=0.0,outL_L_r1_last=0.0;
		/*******************���ֵ�λ�����ȵ��***********************/
int   initR=29,W_LO=40,W_LI=35,W_M=27,W_RI=36,W_RO=36,W_belly_L=29,W_belly_R=28;
float Exp_LO_L=60/*75*/,Exp_LI_L=125/*150*/,Exp_M_L=210/*225*/,Exp_RI_L=125,Exp_RO_L=60,Exp_belly_R_L=72/*81*/,Exp_belly_L_L=72;
/*=====================================�ٶȻ�========================================*/
		/******************************ͣ��***************************************/
				int stop_judge=-1,stop_tiktok=1,global_judge=0;
		/*****************************�ٶ�����**************************************/ 
				int exp_num = 1;				//ѡ�������ٶ�
				int spdExp0 = 0; 	//�̶�0��ͣ����
				int spdExp1 = 20;				//����ٶ�
				int spdExp2 = 20;				//ֱ���ٶ�
				int spdExp = 16;				//�ٶȶ�ȡд��
				float leftExpect,rightExpect;			//�����������ٶ�
		/******************************����***************************************/
				int KDet = 18;//�����ֲ��ٿ���ϵ��
				float smotor_k_last=0;
		/*************************�ٿ�****************************/
				float g_speed_p = 1400,g_speed_i = 35,g_speed_d = 0.0;
				float curSpeed = 0;//��������������
				int lCurSpeed = 0,rCurSpeed = 0;//�����������������ٶ�
				SPEED leftDrv = { 0, 0, 0, 0, 0 };//�ṹ����������֣�
				SPEED rightDrv = { 0, 0, 0, 0, 0 };//�ṹ����������֣�
				int leftSpeedOut = 0, rightSpeedOut = 0;//�����������ٶ�
		/*************************���***************************/
				float g_steer_p_right=237.0/*211*/,g_steer_d_right=2509.0/*2176.0*/;
				float g_steer_p_left=204.0/*159*/,g_steer_d_left=2496.0/*2166.0*/;
				float s_steer_p_right=147,s_steer_d_right=459.0;
				float s_steer_p_left=123,s_steer_d_left=446.0;
				float g_steer_error = 0.0,g_steer_error_last=0.0;
				float smotor_angle_temp=0;//��������м����
				int smotor_angle=0;			//������մ��
				