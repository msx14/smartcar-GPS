#include <GlobalVar.h>
#include "headfile.h"

int ad1,ad2,ad3,ad4,ad5,ad6,ad7;//�������ߴ��䣨��У� 
int g_convert_flag =0; //flag=0ʱΪ��ǰհ��flag=1ʱΪģ��						
int adc_read=0; //�������·�ֵ��ż��������
		
float LO_L=-1,LI_L=-1,M_L=-1,RI_L=-1,RO_L=-1,LO_L_r1=0.01,LI_L_r1=0.01,M_L_r1=0.01,RI_L_r1=0.01,RO_L_r1=0.01;//��ǰհ��м���һ
float belly_R_L=-1,belly_L_L=-1,belly_R_L_r1=0.01,belly_L_L_r1=0.01;//������м���һֵ

int initR=29,W_LO=29,W_LI=26,W_M=21,W_RI=27,W_RO=28,W_belly_R=37,W_belly_L=28;//���ֵ�λ�����ȵ���
float Exp_LO_L=960,Exp_LI_L=2000,Exp_M_L=3360,Exp_RI_L=2000,Exp_RO_L=960,Exp_belly_R_L=1152,Exp_belly_L_L=1152;//�������ֵ

int stop_judge=-1,stop_tiktok=1,global_judge=0;//ͣ�� 
int exp_num = 1,spdExp0 = 20,spdExp1 = 22,spdExp2 = 24,spdExp = 16;//ѡ�������ٶ�
float leftExpect,rightExpect;			//�����������ٶ�
int KDet = 14;//�����ֲ��ٿ���ϵ��
		
float g_speed_p = 1400,g_speed_i = 35,g_speed_d = 0.0;
float curSpeed = 0;//��������������
int lCurSpeed = 0,rCurSpeed = 0;//�����������������ٶ�
SPEED leftDrv = { 0, 0, 0, 0, 0 };//�ṹ����������֣�
SPEED rightDrv = { 0, 0, 0, 0, 0 };//�ṹ����������֣�
int leftSpeedOut = 0, rightSpeedOut = 0;//�����������ٶ�

float g_steer_p_right=291.0,g_steer_d_right=59.0,g_steer_p_left=226.0,g_steer_d_left=46.0;//���pid
float g_steer_error = 0.0,g_steer_error_last=0.0,smotor_angle_temp=0;//���error
int smotor_angle=0,vc_flag=0;			//������մ��
				