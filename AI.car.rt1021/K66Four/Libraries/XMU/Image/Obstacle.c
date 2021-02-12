#include "Obstacle.h"
#include <GlobalVar.h>
#include "headfile.h"
#include "PID.h"

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ������ʶ���µ�
//  @param      RampFlag    //����ͷʶ����·�ϱ�־λ
//  @param      void
//  @return     void 
//  Sample usage:				
//-------------------------------------------------------------------------------------------------------------------
void JudgeRamp(void)
{
	static int state = 1;
	static int angle_init = 0;
	static int acc_speed = 0;
	switch (state)
	{
	case 1:
		if (Img_RampFlag == 1)
		{
			angle_init = imu_data.pit;
			state = 2;
		}
		break;
	case 2:
		if (angle_init - imu_data.pit > 10)
		{
			CircleFlag = 0;
			Img_BrokenFlag = 0;
			Img_BlockFlag = 0;
			state = 3;
		}
		break;
	case 3:
		CircleFlag = 0;
		Img_BrokenFlag = 0;
		Img_BlockFlag = 0;
		if (imu_data.pit - angle_init > 10)
			state = 4;
		break;
	case 4:
		CircleFlag = 0;
		Img_BrokenFlag = 0;
		Img_BlockFlag = 0;
		if (imu_data.pit - angle_init < 5
			&& angle_init - imu_data.pit < 5)
		{
			state = 5;
		}
	case 5:
		acc_speed += curSpeed;
		CircleFlag = 0;
		Img_BrokenFlag = 0;
		Img_BlockFlag = 0;
		if (acc_speed > ONE_METER)
		{
			acc_speed = 0;
			state = 1;
			Img_RampFlag = 0;
			CircleFlag = 0;
			Img_BrokenFlag = 0;
			Img_BlockFlag = 0;
		}
		break;
	default:
		break;
	}
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ����
//  @param      camera_RB_flag    //����ͷʶ����·�ϱ�־λ
//  @param      inf_RB_flag  //�����־λ
//  @return     0 //���ں��·�ϣ�1//�����·�� 
//  Sample usage:				
//-------------------------------------------------------------------------------------------------------------------
void inf(void)
{
	g_inf = collect(ADC1_SE17);
}

#define _ANGLE imu_data.yaw
//-------------------------------------------------------------------------------------------------------------------
//  @brief      ���·��2 ���� ������
//  @param      Img_BlockFlag    //ʶ����·�ϱ�־λ
//  @param      
//  Sample usage:				
//-------------------------------------------------------------------------------------------------------------------
void roadblock3(void)
{
	static pidInit_t SteerInit = { 2,0,0 };
	static PidObject Steer;
	static int state = 0;
	static int yaw_init = 0;
	static int yaw_obj = 0;
	static signed char block_count = 0;
	if (!g_drive_flag) block_count = 0;
	static int angle_1, angle_2;
	switch (state)
	{
	case 0:
		if (Img_BlockFlag)
		{
			if (block_count < BlockCount)
			{

				state = 1;
				speed_type = 5;
				if (1 == BlockDir[block_count])
				{
					angle_1 = -st;
					angle_2 = st_end;
				}
				else if (2 == BlockDir[block_count])
				{
					angle_1 = st;
					angle_2 = -st_end;
				}
				block_count++;
			}
			else
			{
				Img_BlockFlag = 0;
			}
		}
		break;
	case 1:				//�Ӿ�
		sum += curSpeed;
		if (sum > 0)
		{
			state = 2;
			sum = 0;
			pidInit(&Steer, 0, SteerInit, 0.002);
			yaw_init = _ANGLE;
			yaw_obj = yaw_init + angle_1;
			g_handle_open = 0;
		}
		break;
	case 2:
		sum += curSpeed;
		SteerDuty = InitSteer - (int)pidUpdate(&Steer, AngleError(_ANGLE, yaw_obj));
		SteerDuty = MAX(SteerDuty, InitSteer - 120);
		SteerDuty = MIN(SteerDuty, InitSteer + 120);
		ftm_pwm_duty(ftm3, ftm_ch5, SteerDuty);
		if (sum > sum_dist)
		{
			state = 3;
			yaw_obj = yaw_init + angle_2;
			sum = 0;
		}
		break;
	case 3:
		sum += curSpeed;
		SteerDuty = InitSteer - (int)pidUpdate(&Steer, AngleError(_ANGLE, yaw_obj));
		SteerDuty = MAX(SteerDuty, InitSteer - 120);
		SteerDuty = MIN(SteerDuty, InitSteer + 120);
		ftm_pwm_duty(ftm3, ftm_ch5, SteerDuty);
		if (sum > delay_dist			//��֤���ܵ���������
			&& (ind_left > 300 || ind_right > 300))		//�ֲ�������
		{
			state = 0;
			sum = 0;
			speed_type = 1;
			Img_BlockFlag = 0;
			Img_BrokenFlag = 0;
			CircleFlag = 0;
			CircleState = 0;
			if (1 == g_camera_open)
				g_handle_open = 1;
			g_steer_open = 1;
		}
		break;
	default:
		break;
	}
}

#undef _ANGLE  
//-------------------------------------------------------------------------------------------------------------------
//  @brief      �����ǱȽϴ�С(�Ǵ�С) ʵ�ʴ���Ŀ�귵��1
//  @param      real_angle    //ʵ�ʽǶ�
//  @param      obj_angle  //Ŀ��Ƕ�
//  Sample usage:				
//------------------------------------------------------------------------------------------------------------------- 
int JudgeMaxAngle(float real_angle, float obj_angle)
{
	if (obj_angle > 180) obj_angle -= 360;
	else if (obj_angle < -180) obj_angle += 360;
	if (real_angle > 0 && obj_angle >= 0 && real_angle > obj_angle)
		return 1;
	else if (real_angle <= 0 && obj_angle < 0 && real_angle > obj_angle)
		return 1;
	else return 0;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ���������ǲ�ֵ
//  @param      real_angle    //ʵ�ʽǶ�
//  @param      obj_angle  //Ŀ��Ƕ�
//  Sample usage:				
//------------------------------------------------------------------------------------------------------------------- 
float AngleError(float real_angle, float obj_angle)
{
	if (obj_angle > 180) obj_angle -= 360;
	else if (obj_angle < -180) obj_angle += 360;
	if (obj_angle - real_angle > 180)
	{
		return (obj_angle - 360 - real_angle);
	}
	else if (real_angle - obj_angle > 180)
	{
		return (obj_angle + 360 - real_angle);
	}
	else
	{
		return (obj_angle - real_angle);
	}
}