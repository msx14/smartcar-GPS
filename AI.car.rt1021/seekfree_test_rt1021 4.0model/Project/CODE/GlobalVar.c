#include <GlobalVar.h>
#include "headfile.h"

int ad1,ad2,ad3,ad4,ad5,ad6,ad7;//用于无线传输（电感） 
int g_convert_flag =0; //flag=0时为短前瞻，flag=1时为模型						
int adc_read=0; //奇数更新峰值，偶数舵机打脚
		
float LO_L=-1,LI_L=-1,M_L=-1,RI_L=-1,RO_L=-1,LO_L_r1=0.01,LI_L_r1=0.01,M_L_r1=0.01,RI_L_r1=0.01,RO_L_r1=0.01;//短前瞻电感及归一
float belly_R_L=-1,belly_L_L=-1,belly_R_L_r1=0.01,belly_L_L_r1=0.01;//腹部电感及归一值

int initR=29,W_LO=29,W_LI=26,W_M=21,W_RI=27,W_RO=28,W_belly_R=37,W_belly_L=28;//数字电位器自稳电阻
float Exp_LO_L=960,Exp_LI_L=2000,Exp_M_L=3360,Exp_RI_L=2000,Exp_RO_L=960,Exp_belly_R_L=1152,Exp_belly_L_L=1152;//期望电感值

int stop_judge=-1,stop_tiktok=1,global_judge=0;//停车 
int exp_num = 1,spdExp0 = 20,spdExp1 = 22,spdExp2 = 24,spdExp = 16;//选择期望速度
float leftExpect,rightExpect;			//左右轮期望速度
int KDet = 14;//左右轮差速控制系数
		
float g_speed_p = 1400,g_speed_i = 35,g_speed_d = 0.0;
float curSpeed = 0;//编码器反馈均速
int lCurSpeed = 0,rCurSpeed = 0;//编码器反馈左右轮速度
SPEED leftDrv = { 0, 0, 0, 0, 0 };//结构体变量（左轮）
SPEED rightDrv = { 0, 0, 0, 0, 0 };//结构体变量（右轮）
int leftSpeedOut = 0, rightSpeedOut = 0;//左右轮最终速度

float g_steer_p_right=291.0,g_steer_d_right=59.0,g_steer_p_left=226.0,g_steer_d_left=46.0;//舵机pid
float g_steer_error = 0.0,g_steer_error_last=0.0,smotor_angle_temp=0;//舵机error
int smotor_angle=0,vc_flag=0;			//舵机最终打脚
				