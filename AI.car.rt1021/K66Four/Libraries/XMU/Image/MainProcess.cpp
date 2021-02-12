#include "GlobalVar.h"
#include "BasicFind.h"
#include "FindLine.h"
#include "FillSpecialLine.h"
#include "MainProcess.h"
#include "canny.h"
#include "SpecialElem.h"
#include "CircleIsland.h"
//#include "FirstLineProcess.h"

//�˲�
float smoothing(int i)
{
	float image_sum = 0;
	float image_ave = 0;	
	for (int jcir = 33; jcir <= 153; jcir++)
	{
		image_sum = image[i][jcir] + image_sum;
	}
	image_ave = image_sum / 120;
	return image_ave;
}
//�������߲��ú���
void SelectFirstLine(void)
{
	FirstLineV4();
}
//================================================================//
//  @brief  :		��ͨ��ͼ������
//  @param  :		void
//  @return :		void
//  @note   :		void
//================================================================//
void MainFill(void)
{
	//VarInit();			//������ʼ��
	//SelectFirstLine();
	CircleIslandImageInit();	//������ʼ��
	//����
	CircleFirstLine();
	g_RoadType = FirstRowProcess();	//�������ͳ����ж�

	if (0 == g_RoadType)
	{
		FindLineNormal(1);

                garage_io();            //�ж�ͣ���ߺͳ���
//                ImgJudgeStopLine();
//                ImgJudgeGarage();		//ʶ�𳵿�
//                ImgStopLine();		//ͣ���߲�ͼ
//                ImgGarage();			//ͣ���ⲹͼ
                
                Img_CircleSlope();      //����б��

		if (0 == CircleState)
			CircleFlag = Img_JudgeCircleIsland(0);
                
//                �ػ���
//                CircleFlag = CN;
//                CircleState = 0;
                if (CircleFlag != 0)
		{
			CircleFill();
		}
		else
		{
			//ImgJudgeGarage();		//ʶ�𳵿�
			//ImgJudgeStopLine();		//ʶ��ͣ��
                       
                        //Navigation();                   //���Ե���
			//ImgStopLine();		//ͣ���߲�ͼ
			//ImgGarage();			//ͣ���ⲹͼ

			//ImgJudgeObstacle();     //ʶ���µ�·��ֱ����·					

			if (LeftPnt.Type == 2 && RightPnt.Type == 2)		//ʮ�ֲ�ͼ
			{
				if (LeftPnt.ErrRow - RightPnt.ErrRow > 10 || RightPnt.ErrRow - LeftPnt.ErrRow > 10)//10
					FillBevelCross();
				else
					FillLevelCross();
				FindLineNormal(0);

			}
			//ErrorML();
			FillMiddleLine();
		}
		
	}
	else if (1 == g_RoadType)
	{
		FindLineLost();

                garage_io();            //�ж�ͣ���ߺͳ���
//                ImgJudgeStopLine();
//                ImgJudgeGarage();		//ʶ�𳵿�
//                ImgStopLine();		//ͣ���߲�ͼ
//                ImgGarage();			//ͣ���ⲹͼ
                
                Img_CircleSlope();      //����б��

		if (0 == CircleState)
			CircleFlag = Img_JudgeCircleIsland(1);
                
//                 �ػ���
//                CircleFlag = CN;
//                CircleState = 0;
                if (CircleFlag != 0)
		{
			CircleFill();
		}
		else
		{
//                         Navigation();                   //���Ե���
			//ImgStopLine();		//ͣ���߲�ͼ

			if (1 == g_RoadType && 2 == LeftPnt.Type && 2 == RightPnt.Type)
			{
				FillBevelCross();
				FindLineNormal(0);
			}
			//ErrorML();
			FillMiddleLine();
		}
	
	}
	else
	{
//               �ػ���
//                CircleFlag = CN;
//                CircleState = 0;
//                ImgStopLine();		//ͣ���߲�ͼ
//                ImgGarage();			//ͣ���ⲹͼ
                
                if (CircleFlag != 0)
                {
                      CircleFill();
                }
                else
                {
                      //Navigation();               //���Ե���
                      //ImgStopLine();		//ͣ���߲�ͼ
                      FillFourCross();
                      FindLineNormal(0);
                      //ErrorML();
                      FillMiddleLine();
                }
                  
	}
	//ErrorML();
	//FillMiddleLine();
}
//================================================================//
//  @brief  :		������ͼ
//  @param  :		void
//  @return :		void
//  @note   :		void
//================================================================//
void ErrorML()
{
  if(!Img_StopLineFlag)
  {	int num = 0;
	for (int i = DOWN_EAGE; i >= UP_EAGE; --i)
	{
		if (LL[i] >= RL[i])
		{
			num++;
		}
		if (num >= 5)
		{
			//str.Format("\r\n error = %d,%d,%d \r\n", i, LL[i], RL[i]); PrintDebug(//str);
			for (int i = DOWN_EAGE; i >= UP_EAGE; --i)
			{
				LL[i] = LEFT_EAGE;
				RL[i] = RIGHT_EAGE;
			}
			SelectFirstLine();
			g_RoadType = FirstRowProcess();	//�������ͳ����ж�
			if (0 == g_RoadType)
			{
				FindLineNormal(1);
			}
			if (1 == g_RoadType)
			{
				FindLineLost();
			}
			if (2 == g_RoadType)
			{
				FillFourCross();
				FindLineNormal(0);
			}
			break;
		}
	}
  }
}
//================================================================//
//  @brief  :		��ͼ������
//  @param  :		void
//  @return :		void
//  @note   :		void
//================================================================//
void PhotoShow()
{
        //����
        if(smoothing(DOWN_EAGE) < 80  && g_drive_flag == 1)
        {
          //g_fSpeed_set = 0;
          g_drive_flag = 0;
        }
        else
        {
          ;
        }
        if(Navagition_Dir == 0)
        {
            CannyEage();
            MainFill();
            //����У��
            if (RL[DOWN_EAGE] - LL[DOWN_EAGE] <= 40 || ML_Count > DOWN_EAGE - 20		//�±߽��С����Ч��������
                    || RightPnt.ErrCol - LeftPnt.ErrCol > 100)									//�ϱ߽粻����
            {
                    ErrorFlag = 4;
            }
            if (!ErrorFlag)
                    SpeedRow = GetSpeedRow(ControlMid, LeftPnt.ErrRow, RightPnt.ErrRow);		//�ٿ�������Զ��
        }
	
}