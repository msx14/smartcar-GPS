#ifndef __GLOBALVAR_H__
#define __GLOBALVAR_H__

#define SMOTOR_CENTER   3162			//3162+74			//�����ֵ
#define SMOTOR_RANGE    420	//�������ֵ
#define SPEED_OUT_MAX  49999  //�ٶ�+����
#define SPEED_OUT_MIN -49999  //�ٶ�-����

//==========================ģ�ͼ���=================================//
extern int count;
extern int count_flag;
//		extern int cie_data[7];
		extern int ad1,ad2,ad3,ad4,ad5,ad6,ad7;//ad ���� 
		extern int smotor_num;
//==========================ѵ���ɼ��л�==================================//
		extern int g_convert_flag;
//============================���=================================//
		extern int adc_read; 
		extern float straight_k,small_curve_k,large_curve_k;//·��ģ��pid
		extern float edge1,edge2;//·����ֵ
		/*********************ǰհ���************************/
				extern float LO_L,LI_L,M_L,RI_L,RO_L;   //�̵��
				extern float LO_L_r1,LI_L_r1,M_L_r1,RI_L_r1,RO_L_r1;   //�̵�й�һֵ
				extern float LO_L_r1_last,LI_L_r1_last,M_L_r1_last,RI_L_r1_last,RO_L_r1_last;
				extern float belly_R_L,belly_L_L;    //�������
				extern float belly_R_L_r1,belly_L_L_r1;   //������й�һֵ
				extern float belly_R_L_r1_last,belly_L_L_r1_last;
				extern float outL_L,outM_L,outR_L;//��ǰհ���
				extern float outL_L_r1,outM_L_r1,outR_L_r1;//��ǰհ��й�һֵ
				extern float outM_L_r1_last,outL_L_r1_last,outR_L_r1_last;
		/************************���ֵ�λ�����ȵ��***********************/
        extern int initR,W_LO,W_LI,W_M,W_RI,W_RO,W_belly_R,W_belly_L;   //��ж�Ӧ���ֵ�λ������ֵ
        extern float Exp_LO_L,Exp_LI_L, Exp_M_L,Exp_RI_L,Exp_RO_L,Exp_belly_R_L,Exp_belly_L_L;   //�������ֵ
/*=====================================�ٶȻ�========================================*/
		/******************************ͣ��***************************************/
				extern int stop_judge,stop_tiktok,global_judge;
		/*****************************�ٶ�����**************************************/
				extern int exp_num;
				extern int spdExp0,spdExp1,spdExp2,spdExp;
				extern float leftExpect,rightExpect;
		/******************************����***************************************/			
				extern int KDet;
				extern float smotor_k_last;
		/******************************�ٿ�*********************************/
				extern float g_speed_p,g_speed_i,g_speed_d;//�ٿص�pid
				extern float curSpeed;
				extern int lCurSpeed,rCurSpeed;
				typedef struct
				{
					float error_1;
					float error_2;
					float error_3;
					int d_duty;
					float p;
					float i;
					float d;
				}SPEED;

				extern SPEED leftDrv;
				extern SPEED rightDrv;
				extern int leftSpeedOut,rightSpeedOut;
		/*************************���***************************/
				extern float g_steer_p_left,g_steer_d_left;//��ǰհ�������pd				
				extern float g_steer_p_right,g_steer_d_right;//��ǰհ�������pd
				extern float s_steer_p_left,s_steer_d_left;//��ǰհ�������pd				
				extern float s_steer_p_right,s_steer_d_right;//��ǰհ�������pd
				extern float g_steer_error,g_steer_error_last;
				extern float smotor_angle_temp;
				extern int smotor_angle;			//������Ʊ���
#endif  