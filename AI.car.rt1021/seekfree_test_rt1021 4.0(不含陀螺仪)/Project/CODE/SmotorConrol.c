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
void train_smotor_control(void)
{
if(outM_L_r1-outM_L_r1_last<0.01&&outM_L_r1-outM_L_r1_last>-0.01)
	outM_L_r1=outM_L_r1_last;
if(outR_L_r1-outR_L_r1_last<0.01&&outR_L_r1-outR_L_r1_last>-0.01)
	outR_L_r1=outR_L_r1_last;
if(outL_L_r1-outL_L_r1_last<0.01&&outL_L_r1-outL_L_r1_last>-0.01)
	outL_L_r1=outL_L_r1_last;
if(RO_L_r1-RO_L_r1_last<0.01&&RO_L_r1-RO_L_r1_last>-0.01)
	RO_L_r1=RO_L_r1_last;
if(RI_L_r1-RI_L_r1_last<0.01&&RI_L_r1-RI_L_r1_last>-0.01)
	RI_L_r1=RI_L_r1_last;
if(M_L_r1-M_L_r1_last<0.01&&M_L_r1-M_L_r1_last>-0.01)
	M_L_r1=M_L_r1_last;
if(LI_L_r1-LI_L_r1_last<0.01&&LI_L_r1-LI_L_r1_last>-0.01)
	LI_L_r1=LI_L_r1_last;
if(LO_L_r1-LO_L_r1_last<0.01&&LO_L_r1-LO_L_r1_last>-0.01)
	LO_L_r1=LO_L_r1_last;
if(belly_R_L_r1-belly_R_L_r1_last<0.01&&belly_R_L_r1-belly_R_L_r1_last>-0.01)
	belly_R_L_r1=belly_R_L_r1_last;
if(belly_L_L_r1-belly_L_L_r1_last<0.01&&belly_L_L_r1-belly_L_L_r1_last>-0.01)
	belly_L_L_r1=belly_L_L_r1_last;

outM_L_r1_last=outM_L_r1;
outR_L_r1_last=outR_L_r1;
outL_L_r1_last=outL_L_r1;
RO_L_r1_last=RO_L_r1;
RI_L_r1_last=RI_L_r1;
M_L_r1_last=M_L_r1;
LI_L_r1_last=LI_L_r1;
LO_L_r1_last=LO_L_r1;
belly_R_L_r1_last=belly_R_L_r1;
belly_L_L_r1_last=belly_L_L_r1;

if(outM_L_r1<0.1)
	outM_L_r1=0.03;

	//===========舵机控制error=================================
	if (outM_L_r1<1.02 && M_L_r1<1.02)
	{
		if (outL_L_r1>1.02 || outR_L_r1>1.02)
		{
			assist_adc_judge();
			if (smotor_angle_temp>25)
				smotor_angle_temp = 25;	
			else if (smotor_angle_temp<-25)
				smotor_angle_temp = -25;
			
		smotor_angle=(int16)smotor_angle_temp;
		}
		else
		{
		if(outM_L_r1>=edge1&&outM_L_r1<1.02)  //straightaway
      g_steer_error=(outL_L_r1-outR_L_r1)/((outM_L_r1+0.02)*straight_k);
    else if(outM_L_r1<edge1&&outM_L_r1>=edge2)//inner curve
      g_steer_error=((outL_L_r1-outR_L_r1)/((outM_L_r1+0.02)*small_curve_k));
    else if(outM_L_r1<edge1)//outer curve
      g_steer_error=(outL_L_r1-outR_L_r1)/((outM_L_r1+0.02)*large_curve_k);	
		
		if(outL_L_r1<outR_L_r1)
			smotor_angle_temp=g_steer_p_right*g_steer_error+g_steer_d_right*(g_steer_error-g_steer_error_last);
		else if(outL_L_r1>=outR_L_r1)
			smotor_angle_temp=g_steer_p_left*g_steer_error+g_steer_d_left*(g_steer_error-g_steer_error_last);
		g_steer_error_last=g_steer_error;
	  }
	}
	else
	{
		if (outM_L_r1>=1.02 && M_L_r1<1.02)	
			assist_adc_judge();
		else if (outM_L_r1>=1.02 && M_L_r1>=1.02)
			smotor_angle_temp = 0;
		else if (outM_L_r1<1.02 && M_L_r1>=1.02)
		{
			g_steer_error=((outL_L_r1-outR_L_r1)/((outM_L_r1+0.02)*small_curve_k));
			if(outL_L_r1<outR_L_r1)
			smotor_angle_temp=g_steer_p_right*g_steer_error+g_steer_d_right*(g_steer_error-g_steer_error_last);
		else if(outL_L_r1>=outR_L_r1)
			smotor_angle_temp=g_steer_p_left*g_steer_error+g_steer_d_left*(g_steer_error-g_steer_error_last);
			g_steer_error_last=g_steer_error;
		}
		
		if (smotor_angle_temp>25)
			smotor_angle_temp = 25;
		else if( smotor_angle_temp<-25)
			 		smotor_angle_temp = -25;

			smotor_angle=(int16)smotor_angle_temp;
  }		
//
	smotor_angle = (int16)limit(smotor_angle_temp,SMOTOR_RANGE);//限幅保护避免舵机出现卡死 导致舵机烧毁
    pwm_duty(PWM1_MODULE0_CHB_C27,smotor_angle+SMOTOR_CENTER);	//输出控制量	
				exp_num=velocity_type_choose();
}

void assist_adc_judge()
{
if((((LO_L_r1+LI_L_r1-RO_L_r1-RI_L_r1)<0.05)&&((LO_L_r1+LI_L_r1-RO_L_r1-RI_L_r1)>-0.05))||M_L_r1>=1.02)
			g_steer_error=0;
		else
      g_steer_error=(LO_L_r1+LI_L_r1-RO_L_r1-RI_L_r1)/((M_L_r1+0.02)*straight_k);
		
	if(LO_L_r1+LI_L_r1-RO_L_r1-RI_L_r1<0)
		smotor_angle_temp=s_steer_p_right*g_steer_error+s_steer_d_right*(g_steer_error-g_steer_error_last);
	else if(LO_L_r1+LI_L_r1-RO_L_r1-RI_L_r1>=0)
		smotor_angle_temp=s_steer_p_left*g_steer_error+s_steer_d_left*(g_steer_error-g_steer_error_last);
	g_steer_error_last=g_steer_error;
}

void short_adc_judge()
{
		if((((LO_L_r1+LI_L_r1-RO_L_r1-RI_L_r1)<0.1)&&((LO_L_r1+LI_L_r1-RO_L_r1-RI_L_r1)>-0.1))||M_L_r1>=1.02)
			g_steer_error=0;
		else
      g_steer_error=(LO_L_r1+LI_L_r1-RO_L_r1-RI_L_r1)/((M_L_r1+0.02)*straight_k);
		
	if(LO_L_r1+LI_L_r1-RO_L_r1-RI_L_r1<0)
		smotor_angle_temp=s_steer_p_right*g_steer_error+s_steer_d_right*(g_steer_error-g_steer_error_last);
	else if(LO_L_r1+LI_L_r1-RO_L_r1-RI_L_r1>=0)
		smotor_angle_temp=s_steer_p_left*g_steer_error+s_steer_d_left*(g_steer_error-g_steer_error_last);
	g_steer_error_last=g_steer_error;
	
	smotor_angle = (int16)limit(smotor_angle_temp,SMOTOR_RANGE);//限幅保护避免舵机出现卡死 导致舵机烧毁
//	systick_delay_us(1750);
	pwm_duty(PWM1_MODULE0_CHB_C27,smotor_angle+SMOTOR_CENTER);	//输出控制量	
	exp_num=velocity_type_choose();;
}

