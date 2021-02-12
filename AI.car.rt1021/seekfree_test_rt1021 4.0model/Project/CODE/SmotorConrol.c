#include  "headfile.h"
#include  "SmotorControl.h" 
#include  "GlobalVar.h"
			
int velocity_type_choose(void)
{
	int v_type;
	if(smotor_angle>-40&&smotor_angle<40)
				v_type=2;
	else
				v_type=1;	//弯道
	return v_type;
}

void short_adc_judge()
{
		if(M_L_r1>=1.1)	
			g_steer_error=0;
		else 
      g_steer_error=(LO_L_r1+LI_L_r1-RO_L_r1-RI_L_r1)/((M_L_r1+0.02)*0.74);
		
	if(LO_L_r1+LI_L_r1-RO_L_r1-RI_L_r1<=0)
		smotor_angle_temp=g_steer_p_right*g_steer_error+g_steer_d_right*(g_steer_error-g_steer_error_last);
	else if(LO_L_r1+LI_L_r1-RO_L_r1-RI_L_r1>0)
		smotor_angle_temp=g_steer_p_left*g_steer_error+g_steer_d_left*(g_steer_error-g_steer_error_last);
	g_steer_error_last=g_steer_error;
	
	smotor_angle = (int16)limit(smotor_angle_temp,SMOTOR_RANGE);//限幅保护避免舵机出现卡死 导致舵机烧毁
	
	pwm_duty(PWM1_MODULE0_CHB_C27,smotor_angle+SMOTOR_CENTER);	//输出控制量	
	exp_num=velocity_type_choose();
}

