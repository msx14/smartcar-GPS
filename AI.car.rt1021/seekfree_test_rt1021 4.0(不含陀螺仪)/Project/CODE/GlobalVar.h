#ifndef __GLOBALVAR_H__
#define __GLOBALVAR_H__

#define SMOTOR_CENTER   3162			//3162+74			//舵机中值
#define SMOTOR_RANGE    420	//舵机极限值
#define SPEED_OUT_MAX  49999  //速度+极限
#define SPEED_OUT_MIN -49999  //速度-极限

//==========================模型计算=================================//
extern int count;
extern int count_flag;
//		extern int cie_data[7];
		extern int ad1,ad2,ad3,ad4,ad5,ad6,ad7;//ad 数据 
		extern int smotor_num;
//==========================训练采集切换==================================//
		extern int g_convert_flag;
//============================电感=================================//
		extern int adc_read; 
		extern float straight_k,small_curve_k,large_curve_k;//路况模糊pid
		extern float edge1,edge2;//路况阈值
		/*********************前瞻电感************************/
				extern float LO_L,LI_L,M_L,RI_L,RO_L;   //短电感
				extern float LO_L_r1,LI_L_r1,M_L_r1,RI_L_r1,RO_L_r1;   //短电感归一值
				extern float LO_L_r1_last,LI_L_r1_last,M_L_r1_last,RI_L_r1_last,RO_L_r1_last;
				extern float belly_R_L,belly_L_L;    //腹部电感
				extern float belly_R_L_r1,belly_L_L_r1;   //腹部电感归一值
				extern float belly_R_L_r1_last,belly_L_L_r1_last;
				extern float outL_L,outM_L,outR_L;//长前瞻电感
				extern float outL_L_r1,outM_L_r1,outR_L_r1;//长前瞻电感归一值
				extern float outM_L_r1_last,outL_L_r1_last,outR_L_r1_last;
		/************************数字电位器自稳电感***********************/
        extern int initR,W_LO,W_LI,W_M,W_RI,W_RO,W_belly_R,W_belly_L;   //电感对应数字电位器的阻值
        extern float Exp_LO_L,Exp_LI_L, Exp_M_L,Exp_RI_L,Exp_RO_L,Exp_belly_R_L,Exp_belly_L_L;   //电感期望值
/*=====================================速度环========================================*/
		/******************************停车***************************************/
				extern int stop_judge,stop_tiktok,global_judge;
		/*****************************速度期望**************************************/
				extern int exp_num;
				extern int spdExp0,spdExp1,spdExp2,spdExp;
				extern float leftExpect,rightExpect;
		/******************************差速***************************************/			
				extern int KDet;
				extern float smotor_k_last;
		/******************************速控*********************************/
				extern float g_speed_p,g_speed_i,g_speed_d;//速控的pid
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
		/*************************舵机***************************/
				extern float g_steer_p_left,g_steer_d_left;//长前瞻舵机的左pd				
				extern float g_steer_p_right,g_steer_d_right;//长前瞻舵机的右pd
				extern float s_steer_p_left,s_steer_d_left;//短前瞻舵机的左pd				
				extern float s_steer_p_right,s_steer_d_right;//短前瞻舵机的右pd
				extern float g_steer_error,g_steer_error_last;
				extern float smotor_angle_temp;
				extern int smotor_angle;			//舵机控制变量
#endif  