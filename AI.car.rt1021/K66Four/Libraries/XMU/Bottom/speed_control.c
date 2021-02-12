#include "headfile.h"
#include "speed_control.h"
#include <GlobalVar.h>


void FlagChange(int * flag)
{
  if(1 == *flag)
  {
    *flag=0;
    return ;
  }
  else if(0 == *flag)
  {
    *flag=1;
    return ;
  }
}

void SpeedGet(void)
{
    //�����ȡ
    rCurSpeed =-ftm_quad_get(ftm1);
    lCurSpeed = ftm_quad_get(ftm2);
    curSpeed = (lCurSpeed+rCurSpeed)>>1;
    ftm_quad_clean(ftm1);
    ftm_quad_clean(ftm2);
}

//=================================================================//
//  @brief:	���������ٶ�
//  @param: 	
//  @retirn: 
//  @note: 
//=================================================================//
void ExpectSpeedGet()
{
  
  switch(g_speed_type)
  {
    case 0:
          spdExp = spdExp0;    
          //g_speedUpFlg = 0;
          break;
    case 1:
          spdExp = spdExp1;   
          //g_speedUpFlg = 1;
          break;
    case 2:
          spdExp = spdExp2;    
         // g_speedUpFlg = 2;
          break; 
    case 3:
          spdExp = spdExp3; 
          //g_speedUpFlg = 3;
          break;
    case 4:
          spdExp = spdExp4; 
          //g_speedUpFlg = 4;
          break;
    case 5:
          spdExp = spdExp5; 
          //g_speedUpFlg = 5;
          break;
    default:
          spdExp = spdExp0;      
         // g_speedUpFlg = 0;
    
  }
    
}

////=================================================================//
////  @brief:	��������ʽPI����
////  @param: 	
////  @retirn: 
////  @note: 
//========================================================//
void IncrementalRightPidCalc(void)
{
   int error,d_error,dd_error;
   float kdet =(float)KDet / 10000.0f;
   rightExpect =spdExp;   //������ٵ������ٶ�
   
   error = rightExpect - rCurSpeed;        	//����ƫ��
   d_error = error - rightDrv.pre_error;    	//����ƫ��΢��
   dd_error = d_error - rightDrv.pre_derror; 	//����ƫ��΢�ֵ�΢��
   
   rightDrv.pre_error = error;  
   rightDrv.pre_derror = d_error;
   
   rightDrv.p = g_speed_p;      //��ȡP,I,D����
   rightDrv.i = g_speed_i;
   rightDrv.d = g_speed_d;
   
   if(0)  // ��������
   {
     
   }
   else
   {
     rightSpeedOut += (int)(rightDrv.p * d_error + rightDrv.i * error + rightDrv.d * dd_error);
   }
   
   
    if (rightSpeedOut > SPEED_OUT_MAX)
    {
        rightSpeedOut = SPEED_OUT_MAX;
    }
    else if (rightSpeedOut < SPEED_OUT_MIN)
    {
        rightSpeedOut = SPEED_OUT_MIN;
    }
}

////=================================================================//
////  @brief:	��������ʽPI����
////  @param: 	
////  @retirn: 
////  @note: 
//========================================================//
void IncrementalLeftPidCalc(void)
{
   int error,d_error,dd_error;
   float kdet =(float) KDet / 10000.0f;
   leftExpect = spdExp;  
   
   
   error = leftExpect - lCurSpeed;        //����ƫ��
   d_error=error - leftDrv.pre_error;    //����ƫ��΢��
   dd_error = d_error-leftDrv.pre_derror; //����ƫ��΢�ֵ�΢��
   
   leftDrv.pre_error = error;
   leftDrv.pre_derror = d_error;
   
    leftDrv.p = g_speed_p;
    leftDrv.i = g_speed_i;
    leftDrv.d = g_speed_d;
   
   if(0)  // ��������
   {
     ;
   }
   else
   {
     leftSpeedOut += (int)(leftDrv.p*d_error+leftDrv.i * error+leftDrv.d*dd_error);
   }
   
   
    //����޷�������ж�
    if (leftSpeedOut > SPEED_OUT_MAX)
    {
        leftSpeedOut = SPEED_OUT_MAX;
        lOverflowFlg = 1;
    }
    else if(leftSpeedOut < SPEED_OUT_MIN)
    {
        leftSpeedOut = SPEED_OUT_MIN;
        lOverflowFlg = -1;
    }
}

//=================================================================//
// @brief:    ���pwm���
// @param: 	
//@retirn: 
// @note: 
//=================================================================//
void GiveDriveDuty()
{
//  
//    if(g_speed_type == 3 && rCurSpeed>10&&lCurSpeed>10 && !g_stop) 
//    {
//        if(rCurSpeed>10)
//        {
//          ftm_pwm_duty(FTM0, FTM_CH5,0);
//          ftm_pwm_duty(FTM0, FTM_CH4,9999);//����
//        }
//        else
//        {
//          ftm_pwm_duty(FTM0, FTM_CH5,0);
//          ftm_pwm_duty(FTM0, FTM_CH4,0);//����
//        }
//        if(lCurSpeed>10)
//        {
//          ftm_pwm_duty(FTM0, FTM_CH7,9999);//��
//          ftm_pwm_duty(FTM0, FTM_CH6,0);
//        }
//        else
//        {
//          ftm_pwm_duty(FTM0, FTM_CH7,0);//��
//          ftm_pwm_duty(FTM0, FTM_CH6,0);
//        }
//        return;
//    }
    //����
    if(rightSpeedOut >= 0)
    {   ftm_pwm_duty(ftm0, ftm_ch5,rightSpeedOut);
        ftm_pwm_duty(ftm0, ftm_ch4,0);//6Ϊ������4Ϊ�ҷ�
    }
    else
    {
       ftm_pwm_duty(ftm0, ftm_ch5,0);
       ftm_pwm_duty(ftm0, ftm_ch4,-rightSpeedOut);
    }
   //����
    if(leftSpeedOut >= 0)
    {
       ftm_pwm_duty(ftm0, ftm_ch7,0);
       ftm_pwm_duty(ftm0, ftm_ch6,leftSpeedOut);//����
    }
    else 
    {
       ftm_pwm_duty(ftm0, ftm_ch7,-leftSpeedOut);//��
       ftm_pwm_duty(ftm0, ftm_ch6,0);
    }
}

//=================================================================//
// @brief:    �ٿ�
// @param: 	
//@retirn: 
// @note: 
//=================================================================//

void SpeedControl(void)
{
  if(1==g_drive_flag)
  {
     SpeedGet();
     ExpectSpeedGet();          //��ȡ�����ٶ�
     IncrementalLeftPidCalc();  //����ʽPID
     IncrementalRightPidCalc();
     GiveDriveDuty();           //���PWM��ֵ
     
     if (spdExp > 10)           //�����ס����
     {
       if (lCurSpeed < 2 || rCurSpeed < 2)
       {
         lock_count++;
       }
       else
       {
         lock_count = 0;
       }
       if (lock_count > 500)
         g_drive_flag = 0;
     }
  }
  else if(0==g_drive_flag)
  {
    SpeedGet();
    //g_distance_count += (lCurSpeed + rCurSpeed) / 2;   
    leftDrv.iOut=0;
    rightDrv.iOut=0;
    ftm_pwm_duty(ftm0, ftm_ch6,0);
    ftm_pwm_duty(ftm0, ftm_ch4,0);//��
    ftm_pwm_duty(ftm0, ftm_ch7,0);//����
    ftm_pwm_duty(ftm0, ftm_ch5,0);
    
  }
}