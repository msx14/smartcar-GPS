#include "GlobalVar.h"
#include "headfile.h"
#include "speedC.h"
#include "AD.h"

//����ת��
void CircleSpeedGet()
{
    static float exitmotorsave = 0;           //����
    static float entrymotorsave = 0;          //���
    static float motorsave56 = 0;             //����5��6
    static float motorsave35 = 0;             //����3��5
    //�Ӿ��뻷��
    if(CircleState == 2 || InCircleState == 2)
    {
        entrymotorsave += curSpeed;
        if(entrymotorsave >= 4000 && AD_CircleFlag == 0)//7000
        {
            CircleState = 0;
            CircleFlag = CN;
            InCircleState = 0;
        }
    }
    else
    {
        entrymotorsave = 0;
    }
      
    
    //�Ӿ��廷��
    if(CircleState == 7)
    {
        exitmotorsave += curSpeed;
        if(exitmotorsave >= 8000)//10000
        {
            Dist_ClearSevenFlag = 1;
        }
    }
    else
    {
        Dist_ClearSevenFlag = 0;
        exitmotorsave = 0;
    }
    
    //5����û�������͵�6
    if(CircleState >= 3 && CircleState <= 5)
    {
        motorsave56 += curSpeed;
        if(motorsave56 >= 8000)
        {
            Dist_Circle56 = 1;
        }
    }
    else if(CircleState == 6)
    {
        motorsave56 = 0;
    }
    else ;
    
    //3����̫�ò���4��5
    if(CircleState == 3)
    {
        motorsave35 += curSpeed;
        if(motorsave35 >= 7000)
        {
            Dist_Circle35 = 1;
        }
    }
    else
    {
        Dist_Circle35 = 0;            
        motorsave35 = 0;
    }
}
//����������
void SpeedGet(void)
{
	//�����ȡ
	rCurSpeed = ftm_quad_get(ftm1);
	lCurSpeed = -ftm_quad_get(ftm2);
	curSpeed = (lCurSpeed + rCurSpeed) >> 1;
        //motor += curSpeed;
	ftm_quad_clean(ftm1);
	ftm_quad_clean(ftm2);
	//�������ȡ
	g_steer_error = SteerDuty - InitSteer;
}

//=================================================================//
//  @brief:	���������ٶ�
//  @param: 	
//  @retirn: 
//  @note: 
//=================================================================//
void ExpectSpeedGet()
{
	switch (speed_type)
	{
	case 0:
		spdExp = spdExp0;    //ͣ����
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
		break;
	default:
		spdExp = spdExp0;
		// g_speedUpFlg = 0;
	}
}
//=================================================================//
//  @brief:	����pwm�������
//  @param: 	
//  @retirn: 
//  @note: 
//=================================================================//
void LeftPiCalc()
{
	float kdet = (float)KDet / 10000.0f;
        float in_kdet = In_kdet / 10000.0f;
	if (!protect_flag && !Img_StopLineFlag)
	{
		leftExpect = (1 - kdet * g_steer_error) * spdExp;
	}
        if(Img_StopLineFlag)
        {
            leftExpect = (1 - in_kdet * g_steer_error) * spdExp;
        }
	leftDrv.error_1 = leftExpect - lCurSpeed;

        if(Img_RampFlag == 0)
        {
            leftDrv.p = g_speed_p;
            leftDrv.i = g_speed_i;
        }
        else
        {
            leftDrv.p = ramp_speed_p;
            leftDrv.i = ramp_speed_i;
        }
	leftDrv.d = g_speed_d;

//	if (leftDrv.error_1 > speederror || leftDrv.error_1 < -speederror) 
//          leftDrv.i = 0;		//���ַ���

	leftDrv.d_duty = (int)(0.5 + leftDrv.p * (leftDrv.error_1 - leftDrv.error_2) + leftDrv.i * leftDrv.error_1 + leftDrv.d * (leftDrv.error_1 - 2 * leftDrv.error_2 + leftDrv.error_3));
	leftSpeedOut += leftDrv.d_duty;

//	if (g_StateMaster > WaitingStop && speed_type == 0)			//ͣ����ͣ
//	{
//		if (leftDrv.error_1 < -3) leftSpeedOut = SPEED_OUT_MIN;
//	}



	leftDrv.error_3 = leftDrv.error_2;
	leftDrv.error_2 = leftDrv.error_1;

	if (leftSpeedOut > SPEED_OUT_MAX)
		leftSpeedOut = SPEED_OUT_MAX;
	else if (leftSpeedOut < SPEED_OUT_MIN)
		leftSpeedOut = SPEED_OUT_MIN;
}
//=================================================================//
//  @brief:	����pwm�������
//  @param: 	
//  @retirn: 
//  @note: 
//=================================================================//
void RightPiCalc()
{
	float kdet = (float)KDet / 10000.0f;
        float in_kdet = In_kdet / 10000.0f;
	if (!protect_flag)
	{
		rightExpect = (1 + kdet * g_steer_error) * spdExp;
	}
        if (Img_StopLineFlag)
	{
		rightExpect = (1 + in_kdet * g_steer_error) * spdExp;
	}

	rightDrv.error_1 = rightExpect - rCurSpeed;

        if(Img_RampFlag == 0)
        {
            rightDrv.p = g_speed_p;
            rightDrv.i = g_speed_i;
        }
        else
        {
            rightDrv.p = ramp_speed_p;
            rightDrv.i = ramp_speed_i;
        }
	rightDrv.d = g_speed_d;

//	if (rightDrv.error_1 > speederror || rightDrv.error_1 < -speederror) 
//          rightDrv.i = 0;		//���ַ���

	rightDrv.d_duty = (int)(0.5 + rightDrv.p * (rightDrv.error_1 - rightDrv.error_2) + rightDrv.i * rightDrv.error_1 + rightDrv.d * (rightDrv.error_1 - 2 * rightDrv.error_2 + rightDrv.error_3));
	rightSpeedOut += rightDrv.d_duty;

//	if (g_StateMaster > WaitingStop && speed_type == 0)				//ͣ����ͣ
//	{
//		if (rightDrv.error_1 < -3) rightSpeedOut = SPEED_OUT_MIN;
//	}


	rightDrv.error_3 = rightDrv.error_2;
	rightDrv.error_2 = rightDrv.error_1;

	if (rightSpeedOut > SPEED_OUT_MAX)
		rightSpeedOut = SPEED_OUT_MAX;
	else if (rightSpeedOut < SPEED_OUT_MIN)
		rightSpeedOut = SPEED_OUT_MIN;

}
//=================================================================//
// @brief:    ���pwm���
// @param: 	
//@retirn: 
// @note: 
//=================================================================//
void GiveDriveDuty(void)
{
	//����
	if (rightSpeedOut >= 0)
	{
		ftm_pwm_duty(ftm0, RIGHT_GO, rightSpeedOut); //����
		ftm_pwm_duty(ftm0, RIGHT_BACK, 0);
	}
	else
	{
		ftm_pwm_duty(ftm0, RIGHT_GO, 0);
		ftm_pwm_duty(ftm0, RIGHT_BACK, -rightSpeedOut);
	}
	//����
	if (leftSpeedOut >= 0)
	{
		ftm_pwm_duty(ftm0, LEFT_BACK, 0);
		ftm_pwm_duty(ftm0, LEFT_GO, leftSpeedOut);//����
	}
	else
	{
		ftm_pwm_duty(ftm0, LEFT_BACK, -leftSpeedOut);//��
		ftm_pwm_duty(ftm0, LEFT_GO, 0);
	}
}

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


void SpeedControl(void)
{
	if (1 == g_drive_flag)
	{
		SpeedGet();
		ExpectSpeedGet();
		LeftPiCalc();
		RightPiCalc();
		GiveDriveDuty();
		// last_speed = speed_type;
	}
	else if (0 == g_drive_flag)
	{
		SpeedGet();
		CleanTmp();
		ftm_pwm_duty(ftm0, RIGHT_GO, 0);
		ftm_pwm_duty(ftm0, RIGHT_BACK, 0);//��
		ftm_pwm_duty(ftm0, LEFT_GO, 0);//����
		ftm_pwm_duty(ftm0, LEFT_BACK, 0);
		//    DistantStop += curSpeed;
	}
}

////=================================================================//
////  @brief:	ͣ��������
////  @param: 	
////  @retirn: 
////  @note: 
////=================================================================//
//void go_stop(void)
//{
//	static int nowrount = 0;                          //��ǰȦ��
//	static int ntime = 0;
//	if (g_drive_flag)
//	{
//		if (g_stop_line)              //��ʼͣ��
//		{
//			if (nowrount >= rount)
//			{
//				//        g_handle_open = 0;
//				speed_type = 4;
//				nowrount = 0;
//			}
//		}
//
//		if (g_stop_line)
//			ntime++;
//		else ntime = 0;
//		if (ntime > 1000)
//		{
//			g_stop_line = 0;
//			ntime = 0;
//			++nowrount;
//		}
//	}
//	else
//	{
//		nowrount = 0;
//		ntime = 0;
//		g_stop_line = 0;
//	}
//}

//�Ӿ�ɲ��
void DelayDistantStop(void)
{
	static int GiveDistant = 2500;		//��Ϊ�趨�ӳپ���

	if (g_stop_dis)		//���յ��Ӿ�ɲ����־ ��ʼ�ۼ���ʻ����
		DistantStop += curSpeed;
	else DistantStop = 0;

	if (DistantStop >= GiveDistant)
	{
		g_stop_line = 1;	//ִ��ɲ��
		g_stop_dis = 0;
	}
	else;
}


