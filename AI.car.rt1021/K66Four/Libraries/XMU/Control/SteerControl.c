#include "GlobalVar.h"
#include "headfile.h"
#include "SteerControl.h"

const float MidK[] = {
	0.6344, 0.6344, 0.6344, 0.6344, 0.6344, 0.6344, 0.6344, 0.6344, 0.6344, 0.6344, 0.6344, 0.6344, 0.6344, 0.6344, 0.6344, 0.6344, 0.6344, 0.6344, 0.6344, 0.6344, 0.6344, 5.3636, 4.9167, 4.5385, 4.2143, 4.2143, 3.9333, 3.6875, 3.4706, 3.1053, 2.9500, 2.8095, 2.6818, 2.5652, 2.4583, 2.3600, 2.2692, 2.1852, 2.1071, 2.0345, 1.9667, 1.9032, 1.8438, 1.7879, 1.7353, 1.6857, 1.6389, 1.5946, 1.5526, 1.5128, 1.4750, 1.4390, 1.4048, 1.3721, 1.3409, 1.3111, 1.2826, 1.2553, 1.2292, 1.2041, 1.1800, 1.1569, 1.1346, 1.1346, 1.1132, 1.0926, 1.0727, 1.0536, 1.0351, 1.0172, 1.0000, 0.6344, 0.6344, 0.6344, 0.6344, 0.6344, 0.6344, 0.6344, 0.6344, 0.6344, 0.6344, 0.6344, 0.6344, 0.6344, 0.6344, 0.6344, 0.6344, 0.6344, 0.6344, 0.6344, 0.6344, 0.6344, 0.6344, 0.6344, 0.6344, 0.6344, 0.6344, 0.6344, 0.6344, 0.6344, 0.6344, 0.6344, 0.6344, 0.6344, 0.6344, 0.6344, 0.6344, 0.6344, 0.6344, 0.6344, 0.6344, 0.6344, 0.6344, 0.6344, 0.6344, 0.6344, 0.6344, 0.6344, 0.6344, 0.6344,
};

const int DistToPro[] = {
	68,59,53,49,45,43,40,38,36,34,32,31,30,29,28,28,27,27,26,26,26,25 };//最低行为10cm 最远行为65cm

void CarControl_Ind(void)
{
	if(1)//!Img_StopLineFlag && Navagition_Dir == 0)
        {
            ChangeSpeedFlag(2);
            if (CircleState == 3 || 4 == CircleState || 7 == CircleState)
                    CameraSteerControl();
            else
                    IndSteerControl();
            SteerControl();
	}
}

void CarControl(void)
{
        if (!g_camera_open && g_ind_open
                )//|| g_camera_open && ML_Count > 50 && !Img_StopLineFlag && Navagition_Dir == 0)
        {
                ChangeSpeedFlag(0);
                IndSteerControl();
        }
        else if (g_camera_open && g_handle_open && !Img_StopLineFlag && Navagition_Dir == 0)
        {
                ChangeSpeedFlag(1);
                CameraSteerControl();
        }
        //else g_drive_flag = 0;
        SteerControl();//舵机控制
	
}
////电磁停车
//void Ind_StopCar(void)
//{
//	static int count = 0;
//	if (1 == g_ind_open)
//	{
//		if (100 >= ind_left && 100 >= ind_right)
//			count++;
//		else count = 0;
//		if (count > 20)
//		{
//			if (dialSwitchFlg1)
//				g_drive_flag = 0;
//			g_MasterOutFlag = 1;
//			count = 0;
//		}
//	}
//}

void ChangeSpeedFlag(unsigned char type)
{
#define BASICLINE 42		//加减速基准行
	if (1 == type)
	{
		speed_type = 1;
		if (Img_RampFlag != 0) spdExp1 = spdBas3;
		else if (SpeedRow <= UP_EAGE + 1 && Navagition_Dir == 0) spdExp1 = spdBas1 + 6;
		else if (SpeedRow > BASICLINE) spdExp1 = spdBas1 + (BASICLINE - SpeedRow) * 0.5f;
		else spdExp1 = spdBas1 + (BASICLINE - SpeedRow) * (BASICLINE - SpeedRow) * 0.012f;  //最大提3线
		if (CircleState >= 2 && spdExp1 > spdBas1) spdExp1 = spdBas1;  //环岛限速
 
	}
	else if (0 == type)
	{
		speed_type = 4;
	}
	else if (2 == type)		//纯电磁速控
	{
		speed_type = 3;
		if (SpeedRow > BASICLINE) spdExp3 = spdBas2;
		else spdExp3 = spdBas3 + (BASICLINE - SpeedRow) * (BASICLINE - SpeedRow) * 0.024f;
	}
	else;
}


//舵机控制
void SteerControl(void)
{
	if (g_steer_open)
            ftm_pwm_duty(ftm3, ftm_ch5, SteerDuty);
        else
            ftm_pwm_duty(ftm3, ftm_ch5, SteerDutySet);
		
}

//电磁控制
void IndSteerControl(void)
{
	if (Ind_LongRoadFlag)//CircleFlag)
	{
		CameraSteerControl();
	}
	else
	{
		//P
		float P = 0, D = 0;
		float k = p_max_Ind - p_min_Ind;
		if (ad_error_1 > 0)
			Steer_P_Ind = k * ad_error_1 + p_min_Ind;
		else
			Steer_P_Ind = -k * ad_error_1 + p_min_Ind;
		if (Ind_LongRoadFlag)
			P = p_LongRoad_Ind;
		else P = Steer_P_Ind;
		D = Steer_D_Ind;
		//加速限制PD
		if (SpeedRow < UP_EAGE + 15)
		{
			P = 50;
			D = 500;
		}
		SteerDuty = InitSteer + (int)(P * ad_error_1 + D * (ad_error_1 - ad_error_2) + 0.5);
		ad_error_2 = ad_error_1;
		if (100 >= ind_left && 100 <= ind_right)              //右打死
			SteerDuty = InitSteer - SteerCorner;
		else if (100 >= ind_right && 100 <= ind_left)         //左打死
			SteerDuty = InitSteer + SteerCorner;
		else;
		SteerDuty = MAX(SteerDuty, InitSteer - SteerCorner);
		SteerDuty = MIN(SteerDuty, InitSteer + SteerCorner);
	}
}
//摄像头控制
void CameraSteerControl(void)
{
	//获取误差
	if (ProSpect < ML_Count)
	{
              if(Img_RampFlag == 0)
                Error_1 = (ControlMid - ML[ML_Count]);
              else
              {
                if(DOWN_EAGE - 2 < ML_Count)
                  Error_1 = (ControlMid - ML[ML_Count]);
                else
                  Error_1 = (ControlMid - ML[DOWN_EAGE - 2]);
              }
	}
	else
	{
              if(Img_RampFlag == 0)
              {
                //gpio_set(A7, 1);
                Error_1 = (ControlMid - ML[ProSpect]);
              }
              else
              {
                //gpio_set(A7, 0);
                if(DOWN_EAGE - 2 < ML_Count)
                  Error_1 = (ControlMid - ML[ML_Count]);
                else
                  Error_1 = (ControlMid - ML[DOWN_EAGE - 2]);
              }  
                
	}
	//if (Error_1 > 20 || Error_1 < -20)
	//{
	//	//加权平均
	//	int end_line = (91 - 10) / 5;
	//	for (int i = end_line; i > 0; i--)
	//		if (DistToPro[i] > ML_Count)
	//		{
	//			end_line = i;
	//			break;
	//		}
	//	float sum_err = 0, sum_ave = 0;
	//	for (int i = DOWN_EAGE; i > DistToPro[end_line]; i--)
	//	{
	//		sum_err += (ControlMid - ML[i]) * MidK[i] * MidK[i];
	//		sum_ave += MidK[i];
	//	}
	//	Error_1 = (int)(0.5 + sum_err / sum_ave);
	//}
	//校验误差
	if (ErrorFlag && Img_RampFlag == 0)
		Error_1 = Error_2;
	//舵机输出计算
	float P = 0, D = 0;
	//P值改变
	  //动态p
	float k = (p_max - p_min) / 94;
	if (Error_1 > 0)
	{
		Steer_P = p_max - k * Error_1;
	}
	else
	{
		Steer_P = p_max + k * Error_1;
	}
	if (CircleState > 0)
	{
		P = Steer_P_CI;
	}
	else
	{
		P = Steer_P;
	}
        if (Img_RampFlag != 0)
	{
		P = Steer_P_Ramp;
	}
	else
	{
		P = Steer_P;
	}
	//出入弯D
	if (Error_1 > 0 && Error_1 - Error_2 > 0
		|| Error_1 < 0 && Error_1 - Error_2 < 0)  //入弯
		D = Steer_D1;
	else D = Steer_D2;

	SteerDuty = InitSteer + (int)(P * Error_1 + D * (Error_1 - Error_2) + 0.5);
        
        //环岛舵机转角
        if(CircleState == 6)
        {
            SteerDuty = MaxSteerDuty5;
        }
        if(CircleState == 7)
        {
            MaxSteerDuty5 = 0;
        }
        
	Error_2 = Error_1;
	SteerDuty = MAX(SteerDuty, InitSteer - SteerCorner);
	SteerDuty = MIN(SteerDuty, InitSteer + SteerCorner);
}

//惯性导航出
void NavigationOut()
{
    static int motorsave = 0;
    if(Navagition_Dir == 1 && g_drive_flag)
    {
        ChangeSpeedFlag(0);
        YawError_before = YawError;
        YawError = YawAngle_exp - YawAngle;
        motorsave += curSpeed;
        
        SteerDuty = InitSteer + (int)(SteerP_Nav * YawError + SteerD_Nav * (YawError - YawError_before));
        SteerDuty = MAX(SteerDuty, InitSteer - SteerCorner);
	SteerDuty = MIN(SteerDuty, InitSteer + SteerCorner);
        SteerControl();
        
        if(motorsave >= StopDis)
        {
            Navagition_Dir = 0;
            motorsave = 0;
            YawAngle = 0;
        }
        
    }
    else if(Navagition_Dir == 2 && g_drive_flag)
    {
         ChangeSpeedFlag(0);
         YawError_before = YawError;
         YawError = (-1 * YawAngle_exp) - YawAngle;
         motorsave += curSpeed;
         
         SteerDuty = InitSteer + (int)(SteerP_Nav * YawError + SteerD_Nav * (YawError - YawError_before));
         SteerDuty = MAX(SteerDuty, InitSteer - SteerCorner);
	 SteerDuty = MIN(SteerDuty, InitSteer + SteerCorner);
         SteerControl();
          
         if(motorsave >= StopDis)
         {
             Navagition_Dir = 0;
             motorsave = 0;
             YawAngle = 0;
         }
   }
   
    
}
//惯性导航入
//void NavigationIn()
//{
//    static int motorsave = 0;
//    if(Img_StopLineFlag && Navagition_Dir == 0 && Img_RampFlag == 0 && StopMaxRow > StopRow)
//    {   
//        speed_type = 4;
////        if(StopMaxRow >= 55 || motorsave != 0)
//        if(StopMaxRow >= Stop_UpRow || motorsave != 0 || StopMinRow == 0)
//          motorsave += curSpeed;
//        //motor = motorsave;
//        if(Img_GarageFlag == 1)
//        {
//             YawError_before = YawError;
//             YawError = YawAngle_exp - YawAngle;
//        }
//        else if(Img_GarageFlag == 2)
//        {
//             YawError_before = YawError;
//             YawError = (-1 * YawAngle_exp) - YawAngle;
//        }
//        
//        SteerDuty = InitSteer + (int)(SteerP_Nav * YawError + SteerD_Nav * (YawError - YawError_before));
//        SteerDuty = MAX(SteerDuty, InitSteer - SteerCorner);
//	SteerDuty = MIN(SteerDuty, InitSteer + SteerCorner);
////        if(Img_GarageFlag == 1)
////          SteerDuty = InitSteer + SteerCorner;
////        else
////          SteerDuty = InitSteer - SteerCorner;
//        SteerControl();
//        
//        if(motorsave >= StopDis)
//        {
//            speed_type = 0;
////            motorsave = 0;
////            //motor = 0;
////            YawAngle = 0;
//////            Img_StopLineFlag = 0;
//////            Img_GarageFlag = 0;
////            Img_SpecialElemFlag = 0;
////            StopMaxRow = 0;
////            StopMinRow = 0;
//        }
//        
//    }
//    
//}

void NavigationIn()
{
    static int motorsave = 0;
    if(Img_StopLineFlag && StopMaxRow >= StopRow && Navagition_Dir == 0 && Img_RampFlag == 0)
    {   
        speed_type = 4;
        if(StopMinRow == 0 || StopMaxRow >= Stop_UpRow || motorsave != 0)
          motorsave += curSpeed;
        //motor = motorsave;
        if(Img_GarageFlag == 1)
        {
             YawError_before = YawError;
             YawError = YawAngle_exp - YawAngle;
        }
        else if(Img_GarageFlag == 2)
        {
             YawError_before = YawError;
             YawError = (-1 * YawAngle_exp) - YawAngle;
        }
        
        SteerDuty = InitSteer + (int)(SteerP_Nav * YawError + SteerD_Nav * (YawError - YawError_before));
        SteerDuty = MAX(SteerDuty, InitSteer - SteerCorner);
	SteerDuty = MIN(SteerDuty, InitSteer + SteerCorner);
//        if(Img_GarageFlag == 1)
//          SteerDuty = InitSteer + SteerCorner;
//        else
//          SteerDuty = InitSteer - SteerCorner;
        SteerControl();
        
        if(motorsave >= StopDis)
        {
            speed_type = 0;
//            motorsave = 0;
//            //motor = 0;
//            YawAngle = 0;
////            Img_StopLineFlag = 0;
////            Img_GarageFlag = 0;
//            Img_SpecialElemFlag = 0;
//            StopMaxRow = 0;
//            StopMinRow = 0;
        }
        
    }
    
}
//坡道判断
void RampJudge()
{
      if(/*imu_data.pit < -5*/ distance > 1500 && Img_RampFlag == 0 && g_ramp_open == 1)
      {
        Img_RampFlag = 1;
        UP_EAGE = 67;
      }
      else ;
      if((/*Img_RampFlag == 0 || */Img_RampFlag == 1) && (/*distance <= 1000 || */imu_data.pit < -15))
        Img_RampFlag = 2;
      else ;
      if(Img_RampFlag == 2 && (/*distance >= 2000 || */imu_data.pit > 10))
        Img_RampFlag = 3;
      else ;
      if(Img_RampFlag == 3 && (distance <= 1000 && imu_data.pit < 2))
      {
        Img_RampFlag = 0;
        g_ramp_open = 0;
        g_garage_open = 1;
        UP_EAGE = 25;
      }
      else ;    
//      if(/*imu_data.pit < -5*/ distance > 1500 && Img_RampFlag == 0 && g_ramp_open == 1)
//      {
//        Img_RampFlag = 1;
//        UP_EAGE = 50;
//      }
//      else ;
//      if((/*Img_RampFlag == 0 || */Img_RampFlag == 1) && (/*distance <= 1000 || */imu_data.pit > -4))
//        Img_RampFlag = 2;
//      else ;
//      if(Img_RampFlag == 2 && (/*distance >= 2000 || */imu_data.pit < -5))
//        Img_RampFlag = 3;
//      else ;
//      if(Img_RampFlag == 3 && (distance <= 1000 && imu_data.pit > -5))
//      {
//        Img_RampFlag = 0;
//        g_ramp_open = 0;
//        g_garage_open = 1;
//        UP_EAGE = 25;
//      }
//      else ;    

//      static int motorsave = 0;
//      static int rampcount = 0; 
//      if(distance > 2000 && Img_RampFlag == 0 && rampcount == 0)
//        Img_RampFlag = 1;
//      else ;
//      if(Img_RampFlag == 1)
//        motorsave += curSpeed;
//      else ;
//      if(Img_RampFlag == 1 && motorsave >= 80)
//      {
//        Img_RampFlag = 0;
//        rampcount = 1;
//        motorsave = 0;
//      } 
//      else ;
              
        
//    static int motorsave = 0;
//    if(imu_data.pit > 2 && Img_RampFlag == 0)
//        Img_RampFlag = 1;
//    else ;
//    if(Img_RampFlag == 1 && motorsave <= 100)
//    {
//        motorsave += curSpeed;
//    }
//    else if(Img_RampFlag == 1 && motorsave > 100)
//    {
//        Img_RampFlag = 0;
//        motorsave = 0;
//    }
//    motor = motorsave;
  
//        Img_RampFlag = 2;
//    if(Img_RampFlag == 1 && imu_data.pit < 0)
//        Img_RampFlag = 2;
//    else ;
//    if(Img_RampFlag == 2 && imu_data.pit > -7)
//        Img_RampFlag = 0;
//    else ;
	
}