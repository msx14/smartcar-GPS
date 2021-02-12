#include "GlobalVar.h"
#include "headfile.h"
#include "spd.h"

int speed_sum = 0;

void SpeedGet(void)
{
   //脉冲读取
        rCurSpeed = -qtimer_quad_get(QTIMER_1,QTIMER1_TIMER0_D0);
        lCurSpeed = qtimer_quad_get(QTIMER_1,QTIMER1_TIMER2_D2);
    curSpeed = (lCurSpeed+rCurSpeed)>>1;
	      qtimer_quad_clear(QTIMER_1,QTIMER1_TIMER0_D0);
        qtimer_quad_clear(QTIMER_1,QTIMER1_TIMER2_D2);
//    speed_sum += curSpeed;
     //舵机误差获取
//	g_steer_error =smotor_angle;
}



//=================================================================//
//  @brief:	计算期望速度
//  @param: 	
//  @retirn: 
//  @note: 
//=================================================================//
void ExpectSpeedGet()
{
	switch(exp_num)
 {
			case 0:		spdExp = spdExp0;		break;	//停车用
			case 1:		spdExp = spdExp1;		break;
			case 2:		spdExp = spdExp2;		break; 
			default:				break;	 
 }
}

//
//=================================================================//
//  @brief:	左轮pwm输出计算
//  @param: 	
//  @retirn: 
//  @note: 
//=================================================================//
void LeftPiCalc()
{
  float kdet =(float) KDet / 10000.0f ;
	float smotor_k=(float)smotor_angle;	
	if(smotor_k_last-smotor_k<40.0&&smotor_k_last-smotor_k>-40.0)
		smotor_k=smotor_k_last;
			leftExpect = (1- kdet*smotor_k)*spdExp;  
  leftDrv.error_1 = leftExpect - lCurSpeed;
  leftDrv.p = g_speed_p;
  leftDrv.i = g_speed_i ;
  leftDrv.d = g_speed_d; 
 leftDrv.d_duty = (int)(0.5 + leftDrv.p * (leftDrv.error_1 - leftDrv.error_2) + leftDrv.i * leftDrv.error_1 + leftDrv.d * (leftDrv.error_1 - 2 * leftDrv.error_2 + leftDrv.error_3));
  leftSpeedOut += leftDrv.d_duty;  
	leftDrv.error_3 = leftDrv.error_2;
  leftDrv.error_2 = leftDrv.error_1;
 
    if (leftSpeedOut > SPEED_OUT_MAX)
      leftSpeedOut = SPEED_OUT_MAX;
    else if (leftSpeedOut < SPEED_OUT_MIN)
      leftSpeedOut = SPEED_OUT_MIN;
}
//
//=================================================================//
//  @brief:	右轮pwm输出计算
//  @param: 	
//  @retirn: 
//  @note: 
//=================================================================//
void RightPiCalc()
{
     float kdet =(float)KDet / 10000.0f;
		float smotor_k=(float)smotor_angle;
	if(smotor_k_last-smotor_k<40.0&&smotor_k_last-smotor_k>-40.0)
		smotor_k=smotor_k_last;
				rightExpect = (1+kdet*smotor_k)*spdExp;  ;
		rightDrv.error_1 = rightExpect - rCurSpeed;
    rightDrv.p = g_speed_p;
    rightDrv.i = g_speed_i ;
    rightDrv.d = g_speed_d;
    rightDrv.d_duty = (int)(0.5 + rightDrv.p * (rightDrv.error_1 - rightDrv.error_2) + rightDrv.i * rightDrv.error_1 + rightDrv.d * (rightDrv.error_1 - 2 * rightDrv.error_2 + rightDrv.error_3));
    rightSpeedOut += rightDrv.d_duty;
    rightDrv.error_3 = rightDrv.error_2;
    rightDrv.error_2 = rightDrv.error_1;
		
    if (rightSpeedOut > SPEED_OUT_MAX)
      rightSpeedOut = SPEED_OUT_MAX;
    else if (rightSpeedOut < SPEED_OUT_MIN)
      rightSpeedOut = SPEED_OUT_MIN;
}

//
//=================================================================//
// @brief:    电机pwm输出
// @param: 	
//@retirn: 
// @note:
//=================================================================//
void GiveDriveDuty(void)
{
    //右轮
    if(rightSpeedOut>=0)
    { 
			pwm_duty(R_FORWARD,rightSpeedOut); //右正
      pwm_duty(R_BACKWARD,0);
    }
    else
    {
      pwm_duty(R_BACKWARD,-rightSpeedOut);//右反
			pwm_duty(R_FORWARD,0);
    }
   //左轮
    if(leftSpeedOut>=0)
    {
			 pwm_duty(L_FORWARD,leftSpeedOut);//左正
       pwm_duty(L_BACKWARD,0);  
    }
    else 
    {
       pwm_duty(L_BACKWARD,-leftSpeedOut);//左反
       pwm_duty(L_FORWARD,0);
    }
}


//
//=================================================================//
// @brief:    电机全参数归0
// @param: 	
//@retirn: 
// @note:
//=================================================================//
void CleanTmp(void)
{
    leftSpeedOut = 0;
    rightSpeedOut = 0;
    leftDrv.error_1 = 0;
    leftDrv.error_2 = 0;
    leftDrv.error_3 = 0;
    leftDrv.d_duty = 0;
    rightDrv.error_1 = 0;
    rightDrv.error_2 = 0;
    rightDrv.error_3 = 0;
    rightDrv.d_duty = 0;
}
void let_it_stop(void)
{
	pwm_duty(R_BACKWARD, 0);//右轮后转
	pwm_duty(R_FORWARD, 0);//右轮前转
	pwm_duty(L_FORWARD, 0);//左轮前转
	pwm_duty(L_BACKWARD, 0);//左轮后转
}
//
//=================================================================//
// @brief:    最终速度控制
// @param: 	
//@retirn: 
// @note:
//=================================================================//
void SpeedControl(void)
{
  if(gpio_get(D15)==1)//=1，电机打开
		{
        SpeedGet();//编码器获取值
        ExpectSpeedGet();//拨码开关判断	
       
				LeftPiCalc();//左轮速度计算
        RightPiCalc();//右轮速度计算
				smotor_k_last=(float)smotor_angle;
			if(outL_L_r1<0.03&&outR_L_r1<0.03&&g_convert_flag==0)	let_it_stop();
			else if(LO_L_r1<0.03&&RO_L_r1<0.03&&(g_convert_flag==1||g_convert_flag==2))		let_it_stop();
			else
			{
				if(global_judge==0)					GiveDriveDuty();//占空比赋值
				else if(global_judge==1)		let_it_stop();
			}
		}
  else if(gpio_get(D15)==0)
		{
			CleanTmp();		
			let_it_stop();
		}
}


