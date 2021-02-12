#ifndef __GLOBALVAR_H__
#define __GLOBALVAR_H__

#define SMOTOR_CENTER   3162			//2902+260			//舵机中值
#define SMOTOR_RANGE    400	//舵机极限值
#define SPEED_OUT_MAX  49999  //速度+极限
#define SPEED_OUT_MIN -49999  //速度-极限


extern int ad1,ad2,ad3,ad4,ad5,ad6,ad7;//ad 数据 
extern int g_convert_flag;
extern int adc_read;

extern float LO_L,LI_L,M_L,RI_L,RO_L,LO_L_r1,LI_L_r1,M_L_r1,RI_L_r1,RO_L_r1;   //短电感及其归一值
extern float belly_R_L,belly_L_L,belly_R_L_r1,belly_L_L_r1;    //腹部电感及其归一值

extern int initR,W_LO,W_LI,W_M,W_RI,W_RO,W_belly_R,W_belly_L;   //数字电位器的阻值
extern float Exp_LO_L,Exp_LI_L, Exp_M_L,Exp_RI_L,Exp_RO_L,Exp_belly_R_L,Exp_belly_L_L;   //电感期望值

extern int stop_judge,stop_tiktok,global_judge;
extern int exp_num,spdExp0,spdExp1,spdExp2,spdExp;
extern float leftExpect,rightExpect;
	
extern int KDet;

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

extern float g_steer_p_left,g_steer_d_left,g_steer_p_right,g_steer_d_right;//舵机的pd				
extern float g_steer_error,g_steer_error_last;
extern float smotor_angle_temp;
extern int smotor_angle,vc_flag;			//舵机控制变量
	
#endif  