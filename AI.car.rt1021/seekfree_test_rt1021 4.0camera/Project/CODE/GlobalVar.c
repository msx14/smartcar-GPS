#include <GlobalVar.h>
#include "headfile.h"

unsigned char camera_error = 1;
//========================模型计算===================================//
//		int cie_data[7];
		int ad1,ad2,ad3,ad4,ad5,ad6,ad7;//用于无线传输（电感） 
		int smotor_num=0;//用于无线传输（舵机打脚）
//=========================训练采集切换=============================//
		int g_convert_flag =0; //flag=0时为长电感采集，此时由长前瞻电感控制舵机
													//flag=1时为短电感采集，此时由短前瞻电感控制舵机
													//flag=2时为模型训练，由周围的电感控制舵机
													//flag=3时为手动模式，直接手动控制舵机打脚
//============================电感=================================//
		int adc_read=0; //adc_read%2=1的时候为最大最小值更新
										//adc_read%2=0时为控制，此时舵机开始打脚
		float edge1=0.71,edge2=0.35;//路况判断（目前无用）
		float straight_k=0.74,small_curve_k=0.74,large_curve_k=0.74;//模糊pid（目前无用）
		/******************以下为短前瞻的五个电感***************************/
				float LO_L=-1,LI_L=-1,M_L=-1,RI_L=-1,RO_L=-1;
				float LO_L_r1=0.01,LI_L_r1=0.01,M_L_r1=0.01,RI_L_r1=0.01,RO_L_r1=0.01;
		/*****************以下为腹部的两个电感****************************/
				float belly_R_L=-1,belly_L_L=-1;
				float belly_R_L_r1=0.01,belly_L_L_r1=0.01; 
		/*******************以下为长前瞻的五个电感***********************/
				float outL_L=-1,outM_L=-1,outR_L=-1;
				float outL_L_r1=0.01,outM_L_r1=0.01,outR_L_r1=0.01;
		/*******************数字电位器自稳电感***********************/
int   initR=29,W_LO=21,W_LI=16,W_M=16,W_RI=17,W_RO=19,W_belly_R=27,W_belly_L=22;
float Exp_LO_L=/*75*/60*16,Exp_LI_L=/*150*/125*16,Exp_M_L=/*225*/210*16,Exp_RI_L=125*16,Exp_RO_L=60*16,Exp_belly_R_L=/*81*/72*16,Exp_belly_L_L=72*16;
/*=====================================速度环========================================*/
		/******************************停车***************************************/
				int stop_judge=-1,stop_tiktok=1,global_judge=0;
		/*****************************速度期望**************************************/ 
				int exp_num = 1;				//选择期望速度
				int spdExp0 = 0; 	//固定0，停车用
				int spdExp1 = 18;				//弯道速度
				int spdExp2 = 18;				//直道速度
				int spdExp = 16;				//速度读取写入
				float leftExpect,rightExpect;			//左右轮期望速度
		/******************************差速***************************************/
				int KDet = 14;//左右轮差速控制系数

		/*************************速控****************************/
				float g_speed_p = 1400,g_speed_i = 35,g_speed_d = 0.0;
				float curSpeed = 0;//编码器反馈均速
				int lCurSpeed = 0,rCurSpeed = 0;//编码器反馈左右轮速度
				SPEED leftDrv = { 0, 0, 0, 0, 0 };//结构体变量（左轮）
				SPEED rightDrv = { 0, 0, 0, 0, 0 };//结构体变量（右轮）
				int leftSpeedOut = 0, rightSpeedOut = 0;//左右轮最终速度
		/*************************舵机***************************/
				float g_steer_p_right=291.0,g_steer_d_right=59.0;
				float g_steer_p_left=226.0,g_steer_d_left=46.0;
				float g_steer_error = 0.0,g_steer_error_last=0.0;
				float smotor_angle_temp=0;//舵机控制中间变量
				int smotor_angle=0;			//舵机最终打脚
				