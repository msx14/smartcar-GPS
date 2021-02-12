#include "headfile.h"
#include "Meeting.h"
#include "Obstacle.h"
#include "GlobalVar.h"

//#define MEETING_SPEED 10
//#define _ANGLE imu_data.yaw
//
//int StartDistance = 0;
//int turn_angle = 80;
//
////================================================================//
////  @brief  :		��ͼ������ᳵ��������
////  @param  :		void
////  @return :		void
////  @note   :		���ڲ�ͼ����	
////================================================================//
//void MeetingToImage(void)
//{
//	if (!g_single_open)			//�ǵ���ģʽ
//	{
//		if (0 == g_GetMeetingState && !g_GetMeetingFlag			//δ��ʼ�ᳵ
//			&& 2 == Img_BrokenFlag && CarGo == g_StateMaster)
//			g_GetMeetingFlag = 1;
//		else if (g_GetMeetingState && !g_GetMeetingFlag			//�Ѿ���ɻᳵ������ʶ���·
//			&& Img_BrokenFlag)
//			Img_BrokenFlag = 0;
//
//		if (g_GetMeetingState && 1 == Img_StopLineFlag && WaitingStop <= g_StateMaster)		//�Ѿ���ɻᳵ����ʼʶ��ͣ����
//			;
//		else Img_StopLineFlag = 0;
//	}
//}
//
////================================================================//
////  @brief  :		���ֳ��ᳵ����
////  @param  :		void
////  @return :		void
////  @note   :		�����ж�	
////================================================================//
//void MeetingFour(void)
//{
//	static int acc_speed = 0;
//	static int sum_speed = 0.5 * ONE_METER;
//	static float yaw_init = 0;
//	static float yaw_init_1 = 0;
//	static float yaw_init_2 = 0;
//	static int get_flag = 0;
//	static int count = 0;
//	if (1 == g_MeetingMode)				//����ͷ
//	{
//
//		switch (g_StateMaster)
//		{
//		case Ready:
//			if (g_car_lanuch) g_StateMaster = WaitingBegin;
//			break;
//		case WaitingBegin:
//			if (g_StateSlave > Ready)
//			{
//				g_StateMaster = CarGo;
//				g_drive_flag = 1;
//				g_GetMeetingState = 0;
//				g_MasterOutFlag = 0;
//				CircleFlag = 0;
//				CircleState = 0;
//				Img_BrokenFlag = 0;
//				Img_BlockFlag = 0;
//				Img_RampFlag = 0;
//				speed_type = 1;
//				if (1 == g_camera_open)
//					g_handle_open = 1;
//				g_steer_open = 1;
//				g_ad_flag = 1;
//			}
//			break;
//		case CarGo:				//�ȴ�����ᳵ��
//			if (g_GetMeetingFlag) 			 //����ᳵ�� 
//			{
//				acc_speed += curSpeed;
//				if (acc_speed > StartDistance)
//				{
//					g_GetMeetingState = 1;
//					Img_BlockFlag = 0;
//					g_handle_open = 0;
//					acc_speed = 0;
//					//�ı�״̬ ������һ״̬��־
//					g_StateMaster = StateOne;
//					speed_type = 2; //�ᳵ�ٶ�
//					spdExp2 = spdBas2;
//					yaw_init = _ANGLE;
//					if (2 == g_MeetingDir)		//��ת
//					{
//						yaw_init_1 = yaw_init + turn_angle;
//						if (yaw_init_1 > 180) yaw_init_1 -= 360;
//					}
//					else
//					{
//						yaw_init_1 = yaw_init - turn_angle;
//						if (yaw_init_1 < -180) yaw_init_1 += 360;
//					}
//				}
//			}
//			else acc_speed = 0;
//			break;
//		case StateOne:		//�ᳵ�������Լ�״̬
//			if (2 == g_MeetingDir)
//			{
//				ftm_pwm_duty(ftm3, ftm_ch5, InitSteer - 120);
//				if (_ANGLE > 0 && yaw_init_1 >= 0)
//				{
//					if (_ANGLE > yaw_init_1)
//					{
//						ftm_pwm_duty(ftm3, ftm_ch5, InitSteer);
//						//�ı�״̬ ������һ״̬��־
//						g_StateMaster = StateTwo;
//						spdExp2 = 0;
//						acc_speed += curSpeed;
//					}
//				}
//				else if (_ANGLE <= 0 && yaw_init_1 < 0)
//				{
//					if (_ANGLE > yaw_init_1)
//					{
//						ftm_pwm_duty(ftm3, ftm_ch5, InitSteer);
//						//�ı�״̬ ������һ״̬��־
//						g_StateMaster = StateTwo;
//						spdExp2 = 0;
//						acc_speed += curSpeed;
//					}
//				}
//			}
//			else
//			{
//				ftm_pwm_duty(ftm3, ftm_ch5, InitSteer + 120);
//				if (_ANGLE >= 0 && yaw_init_1 > 0)
//				{
//					if (_ANGLE < yaw_init_1)
//					{
//						ftm_pwm_duty(ftm3, ftm_ch5, InitSteer);
//						//�ı�״̬ ������һ״̬��־
//						g_StateMaster = StateTwo;
//						spdExp2 = 0;
//						acc_speed += curSpeed;
//					}
//				}
//				else if (_ANGLE < 0 && yaw_init_1 <= 0)
//				{
//					if (_ANGLE < yaw_init_1)
//					{
//						ftm_pwm_duty(ftm3, ftm_ch5, InitSteer);
//						//�ı�״̬ ������һ״̬��־
//						g_StateMaster = StateTwo;
//						spdExp2 = 0;
//						acc_speed += curSpeed;
//					}
//				}
//			}
//			break;
//		case StateTwo:
//			//�ȴ������ź�
//			if (g_StateSlave >= WaitingStop || g_SlaveOutFlag)		//�ӳ��ѹ���·
//			{
//				//�ı�״̬ ������һ״̬��־
//				g_StateMaster = StateThree;
//				speed_type = 2;
//				spdExp2 = 0 - spdBas2;
//				yaw_init = _ANGLE;
//				if (2 == g_MeetingDir)
//				{
//					yaw_init_1 = yaw_init - turn_angle;
//					if (yaw_init_1 < -180)yaw_init_1 += 360;
//				}
//				else
//				{
//					yaw_init_1 = yaw_init + turn_angle;
//					if (yaw_init_1 > 180)yaw_init_1 -= 360;
//				}
//			}
//			break;
//		case StateThree:
//			//����
//			acc_speed += curSpeed;
//			if (acc_speed > 0)
//				ftm_pwm_duty(ftm3, ftm_ch5, InitSteer);
//			else if (2 == g_MeetingDir)
//				ftm_pwm_duty(ftm3, ftm_ch5, InitSteer - 120);
//			else ftm_pwm_duty(ftm3, ftm_ch5, InitSteer + 120);
//			if (2 == g_MeetingDir)
//			{
//				if (_ANGLE >= 0 && yaw_init_1 > 0)
//				{
//					if (_ANGLE < yaw_init_1)
//					{
//						ftm_pwm_duty(ftm3, ftm_ch5, InitSteer);
//						//�ı�״̬ ������һ״̬��־
//						g_StateMaster = StateFour;
//						spdExp2 = spdBas2;
//					}
//				}
//				else if (_ANGLE < 0 && yaw_init_1 <= 0)
//				{
//					if (_ANGLE < yaw_init_1)
//					{
//						ftm_pwm_duty(ftm3, ftm_ch5, InitSteer);
//						//�ı�״̬ ������һ״̬��־
//						g_StateMaster = StateFour;
//						spdExp2 = spdBas2;
//					}
//				}
//			}
//			else
//			{
//				if (_ANGLE > 0 && yaw_init_1 >= 0)
//				{
//					if (_ANGLE > yaw_init_1)
//					{
//						ftm_pwm_duty(ftm3, ftm_ch5, InitSteer);
//						//�ı�״̬ ������һ״̬��־
//						g_StateMaster = StateFour;
//						spdExp2 = spdBas2;
//					}
//				}
//				else if (_ANGLE <= 0 && yaw_init_1 < 0)
//				{
//					if (_ANGLE > yaw_init_1)
//					{
//						ftm_pwm_duty(ftm3, ftm_ch5, InitSteer);
//						//�ı�״̬ ������һ״̬��־
//						g_StateMaster = StateFour;
//						spdExp2 = spdBas2;
//					}
//				}
//			}
//			break;
//		case StateFour:
//			//�ı�״̬ ������һ״̬��־
//			g_StateMaster = StateFive;
//			Img_BrokenFlag = 2;
//			g_handle_open = 1;
//			acc_speed = 0;
//			//������
//			IndSteerControl();
//			SteerControl();//�������
//			break;
//		case StateFive:
//			acc_speed += curSpeed;
//			//������
//			IndSteerControl();
//			SteerControl();//�������
//			if (!Img_BrokenFlag || acc_speed > 2 * ONE_METER)			//����· ������һ״̬
//			{
//				g_GetMeetingFlag = 0;
//				acc_speed = 0;
//				g_StateMaster = WaitingStop;
//				speed_type = 1;
//			}
//			break;
//		case WaitingStop:		//�ȴ�ʶ��ͣ����
//			if (1 == MeetingStopMode)				//��ͣ��ģʽ
//			{
//				if (Img_StopLineFlag)		//ʶ��ͣ���� �жϴӳ�״̬
//				{
//					g_StateMaster = StateGo;
//				}
//			}
//			else
//			{
//				if (Img_StopLineFlag && !g_SlaveOutFlag)		//ʶ��ͣ���� �жϴӳ�״̬
//				{
//					if (g_StateSlave == StateStop) //�ӳ��ѵ� ������һ�ξ���ͣ��
//						g_StateMaster = StateGo;
//					else
//					{
//						g_StateMaster = StateStop; //ͣ���ȴ�
//						speed_type = 0;
//					}
//				}
//				else if (Img_StopLineFlag && g_SlaveOutFlag)
//					g_StateMaster = StateGo;
//			}
//			break;
//		case StateGo:
//			if (1 == MeetingStopMode)
//			{
//				acc_speed += curSpeed;
//				if (acc_speed > 3.5 * sum_speed)
//				{
//					acc_speed = 0;
//					g_StateMaster = CarFinish;
//				}
//			}
//			else
//			{
//				acc_speed += curSpeed;
//				if (acc_speed > sum_speed)
//				{
//					acc_speed = 0;
//					g_StateMaster = CarFinish;
//				}
//			}
//			break;
//		case StateStop:
//			if (g_StateSlave >= StateGo || g_SlaveOutFlag)		//�ӳ����� ���ߴӳ�����
//			{
//				speed_type = 1;
//				acc_speed += curSpeed;
//				if (acc_speed > sum_speed)
//				{
//					g_StateMaster = CarFinish;
//					acc_speed = 0;
//				}
//
//			}
//			break;
//		case CarFinish:
//			speed_type = 0;
//			break;
//		default:
//			break;
//		}
//	}
//	else if (2 == g_MeetingMode)		//��ͷ
//	{
//		switch (g_StateMaster)
//		{
//		case Ready:
//			if (g_car_lanuch) g_StateMaster = WaitingBegin;
//			break;
//		case WaitingBegin:
//			if (g_StateSlave > Ready)
//			{
//				g_StateMaster = CarGo;
//				g_drive_flag = 1;
//				g_GetMeetingState = 0;
//				g_MasterOutFlag = 0;
//				CircleFlag = 0;
//				CircleState = 0;
//				Img_BrokenFlag = 0;
//				Img_BlockFlag = 0;
//				Img_RampFlag = 0;
//				speed_type = 1;
//				if (1 == g_camera_open)
//					g_handle_open = 1;
//				g_steer_open = 1;
//				g_ad_flag = 1;
//			}
//			break;
//		case CarGo:				//�ȴ�����ᳵ��
//			if (g_GetMeetingFlag) 			 //����ᳵ�� 
//			{
//				acc_speed += curSpeed;
//				if (acc_speed > StartDistance)
//				{
//					g_GetMeetingState = 1;
//					Img_BlockFlag = 0;
//					g_handle_open = 0;
//					acc_speed = 0;
//					//�ı�״̬ ������һ״̬��־
//					g_StateMaster = StateOne;
//					speed_type = 2; //�ᳵ�ٶ�
//					spdExp2 = spdBas2;
//					yaw_init = _ANGLE;
//					if (2 == g_MeetingDir)		//��ת
//					{
//						yaw_init_1 = yaw_init + turn_angle;
//						if (yaw_init_1 > 180) yaw_init_1 -= 360;
//					}
//					else
//					{
//						yaw_init_1 = yaw_init - turn_angle;
//						if (yaw_init_1 < -180) yaw_init_1 += 360;
//					}
//				}
//			}
//			else acc_speed = 0;
//			break;
//		case StateOne:
//			if (2 == g_MeetingDir)
//			{
//				ftm_pwm_duty(ftm3, ftm_ch5, InitSteer - 120);
//				if (_ANGLE > 0 && yaw_init_1 >= 0
//					|| _ANGLE <= 0 && yaw_init_1 < 0)
//				{
//					if (_ANGLE > yaw_init_1)
//					{
//						ftm_pwm_duty(ftm3, ftm_ch5, InitSteer);
//						//�ı�״̬ ������һ״̬��־
//						g_StateMaster = StateTwo;
//						spdExp2 = 0;
//						acc_speed += curSpeed;
//					}
//				}
//			}
//			else
//			{
//				ftm_pwm_duty(ftm3, ftm_ch5, InitSteer + 120);
//				if (_ANGLE >= 0 && yaw_init_1 > 0
//					|| _ANGLE < 0 && yaw_init_1 <= 0)
//				{
//					if (_ANGLE < yaw_init_1)
//					{
//						ftm_pwm_duty(ftm3, ftm_ch5, InitSteer);
//						//�ı�״̬ ������һ״̬��־
//						g_StateMaster = StateTwo;
//						spdExp2 = 0;
//						acc_speed += curSpeed;
//					}
//				}
//			}
//			break;
//		case StateTwo:	//��ʱһ��ʱ�� �ȴ�����ͣ��
//			count++;
//			if (count > 100 && (g_StateSlave > StateOne || g_SlaveOutFlag))		//	�ȴ��Է���ͷ����
//			{
//				count = 0;
//				//�ı�״̬ ������һ״̬��־
//				g_StateMaster = StateThree;
//				spdExp2 = -spdBas2;
//				acc_speed += curSpeed;
//				yaw_init = _ANGLE;
//				if (2 == g_MeetingDir)
//				{
//					yaw_init_1 = yaw_init + turn_angle;
//					if (yaw_init_1 > 180) yaw_init_1 -= 360;
//				}
//				else
//				{
//					yaw_init_1 = yaw_init - turn_angle;
//					if (yaw_init_1 < -180) yaw_init_1 += 360;
//				}
//			}
//			break;
//		case StateThree:
//			//����
//			acc_speed += curSpeed;
//			if (acc_speed > 0)
//				ftm_pwm_duty(ftm3, ftm_ch5, InitSteer);
//			else if (2 == g_MeetingDir)
//				ftm_pwm_duty(ftm3, ftm_ch5, InitSteer + 120);
//			else
//				ftm_pwm_duty(ftm3, ftm_ch5, InitSteer - 120);
//			if (2 == g_MeetingDir)
//			{
//				if (_ANGLE > 0 && yaw_init_1 >= 0 && _ANGLE > yaw_init_1
//					|| _ANGLE <= 0 && yaw_init_1 < 0 && _ANGLE > yaw_init_1)
//				{
//					ftm_pwm_duty(ftm3, ftm_ch5, InitSteer);
//					acc_speed = 0;
//					//�ı�״̬ ������һ״̬��־
//					g_StateMaster = StateFour;
//					spdExp2 = spdBas2;
//					g_handle_open = 1;
//					Img_BrokenFlag = 2;
//					Img_BlockFlag = 0;
//					Img_SpecialElemFlag = 1;
//					CircleFlag = 0;
//					CircleState = 0;
//				}
//			}
//			else
//			{
//				if (_ANGLE >= 0 && yaw_init_1 > 0 && _ANGLE < yaw_init_1
//					|| _ANGLE < 0 && yaw_init_1 <= 0 && _ANGLE < yaw_init_1)
//				{
//					ftm_pwm_duty(ftm3, ftm_ch5, InitSteer);
//					acc_speed = 0;
//					//�ı�״̬ ������һ״̬��־
//					g_StateMaster = StateFour;
//					spdExp2 = spdBas2;
//					g_handle_open = 1;
//					Img_BrokenFlag = 2;
//					Img_BlockFlag = 0;
//					Img_SpecialElemFlag = 1;
//					CircleFlag = 0;
//					CircleState = 0;
//				}
//			}
//			break;
//		case StateFour:
//			acc_speed += curSpeed;
//			ftm_pwm_duty(ftm3, ftm_ch5, InitSteer);
//			if (acc_speed > 0.2 * ONE_METER)
//			{
//				acc_speed = 0;
//				g_StateMaster = StateFive;
//				speed_type = 0;
//			}
//			break;
//		case StateFive:
//			if (g_StateSlave > CarGo || g_SlaveOutFlag)		//�ӳ�����
//			{
//				g_StateMaster = StateSix;
//				speed_type = 2;
//			}
//			break;
//		case StateSix:
//			acc_speed += curSpeed;
//			IndSteerControl();
//			SteerControl();//�������
//			if (!Img_BrokenFlag || acc_speed > 0.2 * ONE_METER)			//����· ������һ״̬
//			{
//				g_StateMaster = WaitingStop;
//				g_GetMeetingFlag = 0;
//				speed_type = 1;
//				Img_BrokenFlag = 0;
//				Img_BlockFlag = 0;
//				Img_SpecialElemFlag = 0;
//				CircleFlag = 0;
//				CircleState = 0;
//			}
//			break;
//		case WaitingStop:		//�ȴ�ʶ��ͣ����
//			if (1 == MeetingStopMode)				//��ͣ��ģʽ
//			{
//				if (Img_StopLineFlag)		//ʶ��ͣ���� �жϴӳ�״̬
//				{
//					g_StateMaster = StateGo;
//				}
//			}
//			else
//			{
//				if (Img_StopLineFlag && !g_SlaveOutFlag)		//ʶ��ͣ���� �жϴӳ�״̬
//				{
//					if (g_StateSlave == StateStop) //�ӳ��ѵ� ������һ�ξ���ͣ��
//						g_StateMaster = StateGo;
//					else
//					{
//						g_StateMaster = StateStop; //ͣ���ȴ�
//						speed_type = 0;
//					}
//				}
//				else if (Img_StopLineFlag && g_SlaveOutFlag)
//					g_StateMaster = StateGo;
//			}
//			break;
//		case StateGo:
//			if(1 == MeetingStopMode)
//			{
//				acc_speed += curSpeed;
//				if (acc_speed > 3.5 * sum_speed)
//				{
//					acc_speed = 0;
//					g_StateMaster = CarFinish;
//				}
//			}
//			else
//			{
//				acc_speed += curSpeed;
//				if (acc_speed > sum_speed)
//				{
//					acc_speed = 0;
//					g_StateMaster = CarFinish;
//				}
//			}
//			break;
//		case StateStop:
//			if (g_StateSlave >= StateGo || g_SlaveOutFlag)		//�ӳ����� ���ߴӳ�����
//			{
//				speed_type = 1;
//				acc_speed += curSpeed;
//				if (acc_speed > sum_speed)
//				{
//					g_StateMaster = CarFinish;
//					acc_speed = 0;
//				}
//			}
//			break;
//		case CarFinish:
//			speed_type = 0;
//			break;
//		default:
//			break;
//		}
//	}
//}
//
////================================================================//
////  @brief  :		���ֳ��ᳵ����
////  @param  :		void
////  @return :		void
////  @note   :		void	
////================================================================//
//void MeetingTwo(void)
//{
//	static int acc_speed = 0;
//	static int sum_speed = 0.5 * ONE_METER;
//	static float yaw_init = 0;
//	static float yaw_init_1 = 0;
//	static float yaw_init_2 = 0;
//	static int get_flag = 0;
//	static int count = 0;
//	switch (g_StateMaster)
//	{
//	case Ready:
//		if (g_car_lanuch) g_StateMaster = WaitingBegin;
//		break;
//	case WaitingBegin:
//		if (g_StateSlave > Ready)
//		{
//			g_StateMaster = CarGo;
//			g_drive_flag = 1;
//		}
//		break;
//	case CarGo:
//		if (g_GetMeetingFlag) 			 //����ᳵ�� 
//		{
//			acc_speed += curSpeed;
//			if (acc_speed > StartDistance)
//			{
//				g_StateMaster = StateOne;
//				Img_BlockFlag = 0;
//				g_handle_open = 0;
//				acc_speed = 0;
//				//�ı�״̬ ������һ״̬��־
//				speed_type = 3; //�ᳵ�ٶ�
//				spdExp3 = MEETING_SPEED;
//				yaw_init = _ANGLE;
//				yaw_init_1 = yaw_init + turn_angle;
//				if (yaw_init_1 > 180) yaw_init_1 -= 360;
//			}
//		}
//		else acc_speed = 0;
//		break;
//	case StateOne:		//�ᳵ�������Լ�״̬
//		break;
//
//	case WaitingStop:		//�ȴ�ʶ��ͣ����
//		if (Img_StopLineFlag && !g_SlaveOutFlag)		//ʶ��ͣ���� �жϴӳ�״̬
//		{
//			if (g_StateSlave == StateStop) //�ӳ��ѵ� ������һ�ξ���ͣ��
//				g_StateMaster = StateGo;
//			else
//			{
//				g_StateMaster = StateStop; //ͣ���ȴ�
//				speed_type = 0;
//			}
//		}
//		else if (Img_StopLineFlag && g_SlaveOutFlag)
//			g_StateMaster = StateGo;
//		break;
//	case StateGo:
//		acc_speed += curSpeed;
//		if (acc_speed > sum_speed * 1.5)
//		{
//			acc_speed = 0;
//			g_StateMaster = CarFinish;
//		}
//		break;
//	case StateStop:
//		if (g_StateSlave >= StateGo || g_SlaveOutFlag)		//�ӳ����� ���ߴӳ�����
//		{
//			speed_type = 1;
//			acc_speed += curSpeed;
//			if (acc_speed > sum_speed * 1.5)
//			{
//				g_StateMaster = CarFinish;
//				acc_speed = 0;
//			}
//		}
//		break;
//	case CarFinish:
//		speed_type = 0;
//		break;
//	default:
//		break;
//	}
//}
////#define MEETING_MODE 2
////#define MEETING_SPEED 10
////#define _ANGLE imu_data.yaw
////#define WaitingMeet 1
////enum MeetingFlag {
////	CarWait = 30,
////	CarGo,
////	WaitingStop = 15,
////	IsStopLine,
////	StateGo,
////	StateStop,
////	CarFinish
////};
////int StartDistance = 0; //ʶ���·���Ӿ����
////int StartSum = 0;               //���������
//
//////================================================================//
//////  @brief  :		���ֳ��ᳵ����
//////  @param  :		void
//////  @return :		void
//////  @note   :		void	
//////================================================================//
////void MeetingFour(void)
////{
////	static int acc_speed = 0;
////	static int sum_speed = 0.5 * ONE_METER;
////	static float yaw_init = 0;
////	static float yaw_init_1 = 0;
////	static float yaw_init_2 = 0;
////	static int get_flag = 0;
////	static int count = 0;
////	if (1 == g_MeetingMode)	//��ͷ
////	{
////		switch (g_StateMaster)
////		{
////		case 0:
////			if (BrokenFlag == 2 && !RampFlag && !g_GetMeetingMaster)             //�����·�� 
////			{
////				acc_speed += curSpeed;
////				if (acc_speed > StartDistance)
////				{
////					g_GetMeetingMaster = 1;
////					g_handle_open = 0;
////					BrokenFlag = 0;
////					BlockFlag = 0;
////					acc_speed = 0;
////					//�ı�״̬ ������һ״̬��־
////					g_StateMaster = 1;
////					speed_type = 3; //�ᳵ�ٶ�
////					spdExp3 = MEETING_SPEED;
////					yaw_init = _ANGLE;
////					yaw_init_1 = yaw_init + 90;
////					if (yaw_init_1 > 180) yaw_init_1 -= 360;
////				}
////			}
////			else acc_speed = 0;
////			break;
////		case 1:
////			ftm_pwm_duty(ftm3, ftm_ch5, InitSteer - 120);
////			if (_ANGLE > 0 && yaw_init_1 >= 0)
////			{
////				if (_ANGLE > yaw_init_1)
////				{
////					ftm_pwm_duty(ftm3, ftm_ch5, InitSteer);
////					//�ı�״̬ ������һ״̬��־
////					g_StateMaster = 3;
////					spdExp3 = 0;
////					acc_speed += curSpeed;
////				}
////			}
////			else if (_ANGLE <= 0 && yaw_init_1 < 0)
////			{
////				if (_ANGLE > yaw_init_1)
////				{
////					ftm_pwm_duty(ftm3, ftm_ch5, InitSteer);
////					//�ı�״̬ ������һ״̬��־
////					g_StateMaster = 3;
////					spdExp3 = 0;
////					acc_speed += curSpeed;
////				}
////			}
////			break;
////		case 3:	//��ʱһ��ʱ�� �ȴ�����ͣ��
////			count++;
////			if (count > 100)
////			{
////				count = 0;
////				//�ı�״̬ ������һ״̬��־
////				g_StateMaster = 4;
////				spdExp3 = -MEETING_SPEED;
////				acc_speed += curSpeed;
////				yaw_init = _ANGLE;
////				yaw_init_1 = yaw_init + 90;
////				if (yaw_init_1 > 180) yaw_init_1 -= 360;
////			}
////			break;
////		case 4:
////			acc_speed += curSpeed;
////			if (acc_speed > 0)
////				ftm_pwm_duty(ftm3, ftm_ch5, InitSteer);
////			else
////				ftm_pwm_duty(ftm3, ftm_ch5, InitSteer + 120);
////
////			if (_ANGLE > 0 && yaw_init_1 >= 0 && _ANGLE > yaw_init_1
////				|| _ANGLE <= 0 && yaw_init_1 < 0 && _ANGLE > yaw_init_1)
////			{
////				ftm_pwm_duty(ftm3, ftm_ch5, InitSteer);
////				acc_speed = 0;
////				//�ı�״̬ ������һ״̬��־
////				g_StateMaster = 5;
////				spdExp3 = 0;
////			}
////			break;
////		case 5:		//�ȴ���һ����
////			if (g_StateSlave > 0)	//�ӳ�����
////			{
////				//�ı�״̬ ������һ״̬��־
////				g_StateMaster = 6;
////				spdExp3 = MEETING_SPEED;
////				g_handle_open = 1;
////				BrokenFlag = 2;
////				BlockFlag = 0;
////			}
////			break;
////		case 6:
////			if (!BrokenFlag)			//����· ������һ״̬
////			{
////				g_StateMaster = WaitingStop;
////				speed_type = 1;
////			}
////			break;
////		case WaitingStop:		//�ȴ�ʶ��ͣ����
////			if (StopLineFlag)		//ʶ��ͣ���� �жϴӳ�״̬
////			{
////				if (g_StateSlave == StateStop) //�ӳ��ѵ� ������һ�ξ���ͣ��
////					g_StateMaster = StateGo;
////				else
////				{
////					g_StateMaster = StateStop; //ͣ���ȴ�
////					speed_type = 0;
////				}
////			}
////			break;
////		case StateGo:
////			acc_speed += curSpeed;
////			if (acc_speed > sum_speed)
////			{
////				acc_speed = 0;
////				g_StateMaster = CarFinish;
////			}
////			break;
////		case StateStop:
////			if (g_StateSlave == StateGo || g_StateSlave == CarFinish)		//�ӳ�����
////			{
////				speed_type = 1;
////				spdExp1 = 15;
////				acc_speed += curSpeed;
////				if (acc_speed > sum_speed)
////				{
////					g_StateMaster = CarFinish;
////					acc_speed = 0;
////				}
////			}
////			break;
////		case CarFinish:
////			speed_type = 0;
////			break;
////		default:
////			break;
////		}
////	}
////	else if (2 == g_MeetingMode)		//����ͷ
////	{
////		switch (g_StateMaster)
////		{
////		case 0:
////			if (BrokenFlag == 2 && !RampFlag && !g_GetMeetingMaster)             //�����·�� 
////			{
////				acc_speed += curSpeed;
////				if (acc_speed > StartDistance)
////				{
////					g_GetMeetingMaster = 1;
////					BlockFlag = 0;
////					g_handle_open = 0;
////					acc_speed = 0;
////					//�ı�״̬ ������һ״̬��־
////					g_StateMaster = 1;
////					speed_type = 3; //�ᳵ�ٶ�
////					spdExp3 = MEETING_SPEED;
////					yaw_init = _ANGLE;
////					yaw_init_1 = yaw_init + 90;
////					if (yaw_init_1 > 180) yaw_init_1 -= 360;
////				}
////			}
////			else acc_speed = 0;
////			break;
////		case 1:
////			ftm_pwm_duty(ftm3, ftm_ch5, InitSteer - 120);
////			if (_ANGLE > 0 && yaw_init_1 >= 0)
////			{
////				if (_ANGLE > yaw_init_1)
////				{
////					ftm_pwm_duty(ftm3, ftm_ch5, InitSteer);
////					//�ı�״̬ ������һ״̬��־
////					g_StateMaster = 3;
////					spdExp3 = 0;
////					acc_speed += curSpeed;
////				}
////			}
////			else if (_ANGLE <= 0 && yaw_init_1 < 0)
////			{
////				if (_ANGLE > yaw_init_1)
////				{
////					ftm_pwm_duty(ftm3, ftm_ch5, InitSteer);
////					//�ı�״̬ ������һ״̬��־
////					g_StateMaster = 3;
////					spdExp3 = 0;
////					acc_speed += curSpeed;
////				}
////			}
////			break;
////		case 3:
////			//�ȴ������ź�
////			if (g_StateSlave > 1 || g_SlaveOutFlag)		//�ӳ��ѹ���·
////			{
////				//�ı�״̬ ������һ״̬��־
////				g_StateMaster = 4;
////				spdExp3 = 0 - MEETING_SPEED;
////				yaw_init = _ANGLE;
////				yaw_init_1 = yaw_init - 90;
////				if (yaw_init_1 < -180)yaw_init_1 += 360;
////			}
////			break;
////		case 4:
////			//����
////			acc_speed += curSpeed;
////			if (acc_speed > 0)
////				ftm_pwm_duty(ftm3, ftm_ch5, InitSteer);
////			else
////				ftm_pwm_duty(ftm3, ftm_ch5, InitSteer - 120);
////			if (_ANGLE >= 0 && yaw_init_1 > 0)
////			{
////				if (_ANGLE < yaw_init_1)
////				{
////					ftm_pwm_duty(ftm3, ftm_ch5, InitSteer);
////					//�ı�״̬ ������һ״̬��־
////					g_StateMaster = 5;
////					spdExp3 = MEETING_SPEED;
////				}
////			}
////			else if (_ANGLE < 0 && yaw_init_1 <= 0)
////			{
////				if (_ANGLE < yaw_init_1)
////				{
////					ftm_pwm_duty(ftm3, ftm_ch5, InitSteer);
////					//�ı�״̬ ������һ״̬��־
////					g_StateMaster = 5;
////					spdExp3 = MEETING_SPEED;
////				}
////			}
////			break;
////		case 5:
////			//�ı�״̬ ������һ״̬��־
////			g_StateMaster = 6;
////			BrokenFlag = 2;
////			g_handle_open = 1;
////
////			//������
////			g_camera_ctrl_flag = 0;
////			g_ind_ctrl_flag = 1;
////			GetSteerOut();//���������
////			SteerControl();//�������
////			break;
////		case 6:
////			//������
////			g_camera_ctrl_flag = 0;
////			g_ind_ctrl_flag = 1;
////			GetSteerOut();//���������
////			SteerControl();//�������
////			if (!BrokenFlag)			//����· ������һ״̬
////			{
////				g_GetMeetingMaster = 0;
////				acc_speed = 0;
////				g_StateMaster = WaitingStop;
////				speed_type = 1;
////			}
////			break;
////		case WaitingStop:		//�ȴ�ʶ��ͣ����
////			if (StopLineFlag && !g_SlaveOutFlag)		//ʶ��ͣ���� �жϴӳ�״̬
////			{
////				if (g_StateSlave == StateStop) //�ӳ��ѵ� ������һ�ξ���ͣ��
////					g_StateMaster = StateGo;
////				else
////				{
////					g_StateMaster = StateStop; //ͣ���ȴ�
////					speed_type = 0;
////					//spdExp1 = 0;
////				}
////			}
////			else if (StopLineFlag && g_SlaveOutFlag)
////				g_StateMaster = StateGo;
////			break;
////			//case IsStopLine:
////			//	if (g_StateSlave == StateStop) //�ӳ��ѵ� ������һ�ξ���ͣ��
////			//		g_StateMaster = StateGo;
////			//	else
////			//	{
////			//		g_StateMaster = StateStop; //ͣ���ȴ�
////			//		speed_type = 1;
////			//		spdExp1 = 0;
////			//	}
////			//	break;
////		case StateGo:
////			acc_speed += curSpeed;
////			if (acc_speed > sum_speed * 1.5)
////			{
////				acc_speed = 0;
////				g_StateMaster = CarFinish;
////			}
////			break;
////		case StateStop:
////			if (g_StateSlave >= StateGo || g_SlaveOutFlag)		//�ӳ����� ���ߴӳ�����
////			{
////				speed_type = 1;
////				acc_speed += curSpeed;
////				if (acc_speed > sum_speed * 1.5)
////				{
////					g_StateMaster = CarFinish;
////					acc_speed = 0;
////				}
////			}
////			break;
////		case CarFinish:
////			speed_type = 0;
////			break;
////		default:
////			break;
////		}
////	}
////}
////
//////================================================================//
//////  @brief  :		���ֳ��ᳵ����
//////  @param  :		void
//////  @return :		void
//////  @note   :		void	
//////================================================================//
////void MeetingTwo(void)
////{
////	static int acc_speed = 0;
////	static int sum_speed = 2500;
////	static float yaw_init = 0;
////	static float yaw_init_1 = 0;
////	static float yaw_init_2 = 0;
////	static int get_flag = 0;
////	static int count = 0;
////	if (1 == g_MeetingMode)
////	{
////		switch (g_StateMaster)
////		{
////		case 0:
////			if (BrokenFlag == 2 && !RampFlag && !g_GetMeetingMaster)             //�����·�� 
////			{
////				BlockFlag = 0;//clear block 
////				acc_speed += curSpeed;
////				if (acc_speed > StartDistance)
////				{
////					g_GetMeetingMaster = 1;
////					//�ı�״̬ ������һ״̬��־
////					g_StateMaster = 1;
////					g_drive_flag = 0;//ͣ��
////					BrokenFlag = 0;
////
////				}
////			}
////			break;
////		case 1://�ȴ��ӳ������־
////			if (g_StateSlave > 0)
////			{
////				g_StartMaster = 2;
////			}
////			break;
////		case 2:
////			//ת��
////			//�˴����ת�亯�� ��ֱ������ Ȼ������ת��
////
////			//������־λ�仯
////			g_StateMaster = 3;
////			BrokenFlag = 2;
////
////			break;
////		case 3:
////			//����
////			if (0 == BrokenFlag)
////			{
////				//����·�����ᳵ״̬���ͱ�־λ
////				g_StateMaster = WaitingStop;		//�����ᳵ
////				g_GetMeetingMaster = 0;
////			}
////			break;
////		case WaitingStop:		//����· �ȴ�ʶ��ͣ����
////			if (StopLineFlag)	//ʶ��ͣ����
////			{
////				if (g_StateSlave == IsStopLine) //�ӳ��ѵ� ������һ�ξ���ͣ��
////					g_StateMaster = StateGo;
////				else
////				{
////					g_StateMaster = StateStop; //ͣ���ȴ�
////					g_drive_flag = 0;
////				}
////			}
////			break;
////		case StateGo:
////			acc_speed += curSpeed;
////			if (acc_speed > sum_speed)
////			{
////				acc_speed = 0;
////				g_StateMaster = CarFinish;
////			}
////			break;
////		case StateStop:
////			if (g_StateSlave == StateGo || g_StateSlave == CarFinish)		//�ӳ�����
////			{
////				g_drive_flag = 1;
////				acc_speed += curSpeed;
////				if (acc_speed > sum_speed)
////				{
////					g_StateMaster = CarFinish;
////					acc_speed = 0;
////				}
////			}
////			break;
////		case CarFinish:
////			g_drive_flag = 0;
////		default:
////			break;
////		}
////	}
////	else if (2 == g_MeetingMode)	//����ͷ
////	{
////		switch (g_StateMaster)
////		{
////		case 0:
////			if (BrokenFlag == 2 && !RampFlag && !g_GetMeetingMaster)             //�����·�� 
////			{
////				BlockFlag = 0;//clear block 
////				if (acc_speed > StartDistance)
////				{
////					g_GetMeetingMaster = 1;
////					//�ı�״̬ ������һ״̬��־
////					g_StateMaster = 1;
////				}
////			}
////			break;
////		case 1:		//����ܶ�·
////			if (0 == BrokenFlag)
////			{
////				//����·�����ᳵ״̬���ͱ�־λ
////				g_StateMaster = WaitingStop;		//�����ᳵ
////				g_GetMeetingMaster = 0;
////			}
////			break;
////		case WaitingStop:		//����· �ȴ�ʶ��ͣ����
////			if (StopLineFlag)	//ʶ��ͣ����
////			{
////				if (g_StateSlave == IsStopLine) //�ӳ��ѵ� ������һ�ξ���ͣ��
////					g_StateMaster = StateGo;
////				else
////				{
////					g_StateMaster = StateStop; //ͣ���ȴ�
////					g_drive_flag = 0;
////				}
////			}
////			break;
////			//case IsStopLine:
////			//	if (g_StateSlave == IsStopLine) //�ӳ��ѵ� ������һ�ξ���ͣ��
////			//		g_StateMaster = StateGo;
////			//	else
////			//		g_StateMaster = StateStop; //ͣ���ȴ�
////			//	break;
////		case StateGo:
////			acc_speed += curSpeed;
////			if (acc_speed > sum_speed)
////			{
////				acc_speed = 0;
////				g_StateMaster = CarFinish;
////			}
////			break;
////		case StateStop:
////			if (g_StateSlave == StateGo || g_StateSlave == CarFinish)		//�ӳ�����
////			{
////				g_drive_flag = 1;
////				acc_speed += curSpeed;
////				if (acc_speed > sum_speed)
////				{
////					g_StateMaster = CarFinish;
////					acc_speed = 0;
////				}
////			}
////			break;
////		case CarFinish:
////			g_drive_flag = 0;
////		default:
////			break;
////		}
////	}
////}
//
////================================================================//
////  @brief  :		״̬ת��ƽ�����
////  @param  :		dst Ŀ����� srcԴ��� dutyĿ�����ռ�ձ�
////  @return :		�����
////  @note   :		Դ�����Ŀ���������
////================================================================//
//float LinearOut(float dst, float src, float duty)
//{
//	return (dst * duty + src * (1 - duty));
//}
//
//
//#undef _ANGLE 
//
////================================================================//
////  @brief  :		���ֳ�����ģʽ
////  @param  :		void
////  @return :		void
////  @note   :		void	
////================================================================//
//void SingleFour(void)
//{
//	static int sum_speed = ONE_METER;
//	static int acc_speed = 0;
//	static unsigned char state = 0;
//	switch (state)
//	{
//	case 0:
//		if (Img_StopLineFlag)
//		{
//			state = 1;
//		}
//		break;
//	case 1:
//		acc_speed += curSpeed;
//		if (acc_speed > sum_speed)
//		{
//			state = 0;
//			acc_speed = 0;
//			speed_type = 0;
//			Img_StopLineFlag = 0;
//		}
//		break;
//	default:
//		break;
//	}
//
//}