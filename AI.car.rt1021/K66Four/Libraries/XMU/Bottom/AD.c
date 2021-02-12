#include "GlobalVar.h"
#include "headfile.h"
#include "AD.h"

int protect_flag = 0;
void ind_acq(void)                         //电感采集
{
        if(g_ad_flag == 1)
          distance = collect(ADC1_SE17);
  	//采集电感
	ind_left = collect(ADC_LEFT);
	ind_right = collect(ADC_RIGHT);
	ind_mid = collect(ADC_MIDDLE);
	//ind_leftcol = ad_ave(ADC0_SE18, ADC_12bit, 10);
	//ind_rightcol = ad_ave(ADC0_SE12, ADC_12bit, 10);
        
	//电感值限幅
	ind_left = MIN(ind_left, MAXIND);
	ind_left = MAX(ind_left, MININD);
        
	ind_right = MIN(ind_right, MAXIND);
	ind_right = MAX(ind_right, MININD);
        
	ind_mid = MIN(ind_mid, MAXIND);
	ind_mid = MAX(ind_mid, MININD);
//	ind_leftcol = MIN(ind_leftcol, MAXIND);
//	ind_leftcol = MAX(ind_leftcol, MININD);
//	ind_rightcol = MIN(ind_rightcol, MAXIND);
//	ind_rightcol = MAX(ind_rightcol, MININD);
}

void ind_norm_maxmin(void)                //左右电感最大最小
{
	ind_leftmax = MAX(ind_leftmax, ind_left);
	ind_leftmin = MIN(ind_leftmin, ind_left);
        
	ind_rightmax = MAX(ind_rightmax, ind_right);
	ind_rightmin = MIN(ind_rightmin, ind_right);
        
	ind_midmax = MAX(ind_midmax, ind_mid);
	ind_midmin = MIN(ind_midmin, ind_mid);
//	ind_leftcolmax = MAX(ind_leftcolmax, ind_leftcol);
//	ind_leftcolmin = MIN(ind_leftcolmin, ind_leftcol);
//	ind_rightcolmax = MAX(ind_rightcolmax, ind_rightcol);
//	ind_rightcolmin = MIN(ind_rightcolmin, ind_rightcol);
}

void ind_norm(void)                           //得出归一值；
{
	left_norm = (float)((ind_left - ind_leftmin)) / (float)((ind_leftmax - ind_leftmin));
	right_norm = (float)((ind_right - ind_rightmin)) / (float)((ind_rightmax - ind_rightmin));
	mid_norm = (float)((ind_mid - ind_midmin)) / (float)((ind_midmax - ind_midmin));
//	leftcol_norm = (float)(ind_leftcol - ind_leftcolmin) / (float)(ind_leftcolmax - ind_leftcolmin);
//	rightcol_norm = (float)(ind_rightcol - ind_rightcolmin) / (float)(ind_rightcolmax - ind_rightcolmin);
}

void get_ind_error(void)  //电感获取Error值 note:放在中断 如果电感开 则一直采集电感值 计算error；
{
	if (g_ad_flag == 1)
	{
		ind_acq();
		ind_norm();
		ad_error_1 = (left_norm - right_norm) / (left_norm + right_norm);// * pow((mid_norm + 0.6),4);
		ind_protect();
	}
	else if (0 == g_ad_flag)
	{
		ind_acq();
		ind_norm_maxmin();
		ind_norm();
		//ind_protect();

	}
}

////================================================================//
////  @brief  :		电磁判断入环岛
////  @param  :		void
////  @return :		void
////  @note   :		放在中断
////================================================================//
void AD_Img_Circle()
{
  float l3_slope = 0;
  float r3_slope = 0;
  int max_ll = LEFT_EAGE;
  int max_ll_row = DOWN_EAGE;
  int min_rl = RIGHT_EAGE;
  int min_rl_row = DOWN_EAGE;
    if(/*CircleFlag && */(CircleState == 2 || CircleState == 0) && Img_RampFlag == 0 && Img_CircleOpen)
    {
        if(mid_norm > MidAD && ((left_norm - right_norm) > 0.8 || (left_norm - right_norm) < -0.8))
        {
            CircleCount++;
        }
        if(CircleCount >= 15)
        {
            AD_CircleFlag = 1;
            InCircleState = 3;
            CircleState = 3;
            CircleFlag = CircleFlagSet;
        }
    }
    
    if(CircleFlag == CN && CircleState == 3)
    {
        max_ll = LEFT_EAGE;
        max_ll_row = DOWN_EAGE;
        min_rl = RIGHT_EAGE;
        min_rl_row = DOWN_EAGE;
        for(int i = DOWN_EAGE; i > UP_EAGE + 3; --i)
        {
            if(RL[i] - LL[i] > 0 && RL[i] < RIGHT_EAGE && LL[i] > LEFT_EAGE)
            {
                if(RL[i] < min_rl)
                {
                    min_rl = RL[i];
                    min_rl_row = i;
                }
                if(LL[i] > max_ll)
                {
                    max_ll = LL[i];
                    max_ll_row = i;
                }
            }
            else if(RL[i] >= RIGHT_EAGE && LL[i] > LEFT_EAGE)
            {
                CircleFlag = CR;
                break;
            }
            else if(LL[i] <= LEFT_EAGE && RL[i] < RIGHT_EAGE)
            {
                CircleFlag = CL;
                break;
            }
            else
            {
                break;
            }
        }
        if(min_rl > max_ll)
        {
            if(min_rl_row > max_ll_row)
            {
                CircleFlag = CR;
            }
            else if(min_rl_row < max_ll_row)
            {
                CircleFlag = CL;
            }
        }
//                    if(CircleFlag == CN)
//                    {
//                        l3_slope = g_slope(LL, max_width_row, min_width_row, 0);
//                        r3_slope = g_slope(RL, max_width_row, min_width_row, 1);
//                        if(r3_slope < 0 && r3_slope != -1 && l3_slope < 0)
//                          CircleFlag = CL;
//                        else if((r3_slope == -1 || r3_slope > 0) && l3_slope > 0)
//                          CircleFlag = CR;
//                    }
//                else
//                {
//                  
//                    for (int j = DOWN_EAGE; j > UP_EAGE; j--)
//                    {
//                            for (int i = MIDDLE; i < RIGHT_EAGE; i++)
//                            {
//                              if(image[j][i] > 100)
//                                    CircleFlag++;
//                            }
//                            for (int i = MIDDLE; i > LEFT_EAGE; i--)
//                            {
//                              if(image[j][i] > 100)
//                                    CircleFlag--;
//                            }
//                    }
//                    if (CircleFlag > 0)
//                    {
//                      CircleFlag = CR;
//                    }
//                    else if (CircleFlag < 0)
//                    {
//                      CircleFlag = CL;
//                    }
//                }
    }
       
    
}

//================================================================//
//  @brief  :		电感识别出环岛
//  @param  :		void
//  @return :		1是环岛 0非环岛
//  @note   :		传入参数为0条件弱 传入参数为1条件强
//================================================================//
unsigned char IndJudgeCircle()
{
#if CI_IND
  if(mid_norm > 1.3)
	return 1;
  else return 0;
#else 
  return 1;
#endif
}
//unsigned char IndJudgeCircle(unsigned char type)
//{
//#if CI_IND
//	if (type)
//	{
//
//	}
//	else
//	{
//		if (mid_norm > 1.6f || leftcol_norm > 0.6f || rightcol_norm > 0.6f) return 1;
//		else return 0;
//	}
//#else
//	return 1;
//#endif
//}
//================================================================//
//  @brief  :		电感识别入环岛
//  @param  :		void
//  @return :		1是环岛 0非环岛
//  @note   :		传入参数为0条件弱 传入参数为1条件强
//================================================================//
unsigned char IndJudgeIntoCircle(unsigned char type)
{
#if CI_IND
	if (type)
	{

	}
	else
	{
		if (mid_norm > 1.3f) return 1;
		else return 0;
	}
#else
	if (mid_norm > Ind_CI_TH && (leftcol_norm > 0.15 || rightcol_norm > 0.15)) return 1;
	else return 0;
#endif
}

void ind_protect(void)
{
	static int count = 0;
	if (ind_left < 40 && ind_right < 40 && ind_mid < 40 && !Img_StopLineFlag)
	{
		speed_type = 0;
		protect_flag = 1;
	}
	if (protect_flag)
	{
		g_drive_flag = 0;
		count++;
	}
	if (count >= 500)
	{
		count = 0;
		protect_flag = 0;

	}
}