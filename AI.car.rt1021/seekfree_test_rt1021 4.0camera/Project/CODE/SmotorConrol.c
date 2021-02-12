#include  "headfile.h"
#include  "SmotorControl.h" 
#include  "GlobalVar.h"
			
int velocity_type_choose(void)
{
	int v_type;
	if(smotor_angle>-40&&smotor_angle<40)
				v_type=2;
	else
				v_type=1;	//���
	return v_type;
}
void train_smotor_control(void)
{
	//===========�������error=================================

	if (outM_L_r1<1.02 && M_L_r1<1.02)
	{
		if (outL_L_r1>1.02 || outR_L_r1>1.02)
		{
			short_adc_judge();
			if (smotor_angle_temp>30)
				smotor_angle = 30;	
		else if (smotor_angle_temp<-30)
				smotor_angle = -30;
			else smotor_angle=(int16)smotor_angle_temp;
		}
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
		
		smotor_angle = (int16)limit(smotor_angle_temp,SMOTOR_RANGE);//�޷��������������ֿ��� ���¶���ջ�
	}
	else
	{
		if (outM_L_r1>=1.02 && M_L_r1<1.02)	
			short_adc_judge();
		else if (outM_L_r1>=1.02 && M_L_r1>=1.02)
			smotor_angle = 0;
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
			smotor_angle = 25;
		 else if( smotor_angle_temp<-25)
			 		smotor_angle = -25;
		else smotor_angle=(int16)smotor_angle_temp;
//	smotor_angle=(int16)limit(smotor_angle_temp,30);
  }

		
	//���������	
    pwm_duty(PWM1_MODULE0_CHB_C27,smotor_angle+SMOTOR_CENTER);
				exp_num=velocity_type_choose();
}


void short_adc_judge()
{
		if(M_L_r1>=1.1)	
			g_steer_error=0;
		else if(M_L_r1>=edge1&&M_L_r1<1.1)  //straightaway
      g_steer_error=(LO_L_r1+LI_L_r1-RO_L_r1-RI_L_r1)/((M_L_r1+0.02)*straight_k);
    else if(M_L_r1<edge1&&M_L_r1>=edge2)//inner curve
      g_steer_error=((LO_L_r1+LI_L_r1-RO_L_r1-RI_L_r1)/((M_L_r1+0.02)*small_curve_k));
    else if(outM_L_r1<edge1)//outer curve
      g_steer_error=(LO_L_r1+LI_L_r1-RO_L_r1-RI_L_r1)/((M_L_r1+0.02)*large_curve_k);
		
	if(LO_L_r1+LI_L_r1-RO_L_r1-RI_L_r1<0)
		smotor_angle_temp=g_steer_p_right*g_steer_error+g_steer_d_right*(g_steer_error-g_steer_error_last);
	else if(LO_L_r1+LI_L_r1-RO_L_r1-RI_L_r1>0)
		smotor_angle_temp=g_steer_p_left*g_steer_error+g_steer_d_left*(g_steer_error-g_steer_error_last);
	g_steer_error_last=g_steer_error;
	smotor_angle = (int16)limit(smotor_angle_temp,SMOTOR_RANGE);//�޷��������������ֿ��� ���¶���ջ�
	
	pwm_duty(PWM1_MODULE0_CHB_C27,smotor_angle+SMOTOR_CENTER);	//���������	
	exp_num=velocity_type_choose();
}

