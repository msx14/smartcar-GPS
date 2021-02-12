#include "GlobalVar.h"
#include "BasicFind.h"
#include "FindLine.h"
#include "FillSpecialLine.h"
#include "MainProcess.h"
#include "canny.h"
#include "SpecialElem.h"
#include "CircleIsland.h"
//#include "FirstLineProcess.h"

//滤波
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
//首行搜线采用函数
void SelectFirstLine(void)
{
	FirstLineV4();
}
//================================================================//
//  @brief  :		普通补图主程序
//  @param  :		void
//  @return :		void
//  @note   :		void
//================================================================//
void MainFill(void)
{
	//VarInit();			//变量初始化
	//SelectFirstLine();
	CircleIslandImageInit();	//变量初始化
	//首行
	CircleFirstLine();
	g_RoadType = FirstRowProcess();	//赛道类型初次判断

	if (0 == g_RoadType)
	{
		FindLineNormal(1);

                garage_io();            //判断停车线和车库
//                ImgJudgeStopLine();
//                ImgJudgeGarage();		//识别车库
//                ImgStopLine();		//停车线补图
//                ImgGarage();			//停车库补图
                
                Img_CircleSlope();      //环岛斜率

		if (0 == CircleState)
			CircleFlag = Img_JudgeCircleIsland(0);
                
//                关环岛
//                CircleFlag = CN;
//                CircleState = 0;
                if (CircleFlag != 0)
		{
			CircleFill();
		}
		else
		{
			//ImgJudgeGarage();		//识别车库
			//ImgJudgeStopLine();		//识别停车
                       
                        //Navigation();                   //惯性导航
			//ImgStopLine();		//停车线补图
			//ImgGarage();			//停车库补图

			//ImgJudgeObstacle();     //识别坡道路障直道断路					

			if (LeftPnt.Type == 2 && RightPnt.Type == 2)		//十字补图
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

                garage_io();            //判断停车线和车库
//                ImgJudgeStopLine();
//                ImgJudgeGarage();		//识别车库
//                ImgStopLine();		//停车线补图
//                ImgGarage();			//停车库补图
                
                Img_CircleSlope();      //环岛斜率

		if (0 == CircleState)
			CircleFlag = Img_JudgeCircleIsland(1);
                
//                 关环岛
//                CircleFlag = CN;
//                CircleState = 0;
                if (CircleFlag != 0)
		{
			CircleFill();
		}
		else
		{
//                         Navigation();                   //惯性导航
			//ImgStopLine();		//停车线补图

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
//               关环岛
//                CircleFlag = CN;
//                CircleState = 0;
//                ImgStopLine();		//停车线补图
//                ImgGarage();			//停车库补图
                
                if (CircleFlag != 0)
                {
                      CircleFill();
                }
                else
                {
                      //Navigation();               //惯性导航
                      //ImgStopLine();		//停车线补图
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
//  @brief  :		修正错图
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
			g_RoadType = FirstRowProcess();	//赛道类型初次判断
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
//  @brief  :		补图主程序
//  @param  :		void
//  @return :		void
//  @note   :		void
//================================================================//
void PhotoShow()
{
        //保护
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
            //中线校验
            if (RL[DOWN_EAGE] - LL[DOWN_EAGE] <= 40 || ML_Count > DOWN_EAGE - 20		//下边界过小，有效行数过低
                    || RightPnt.ErrCol - LeftPnt.ErrCol > 100)									//上边界不收敛
            {
                    ErrorFlag = 4;
            }
            if (!ErrorFlag)
                    SpeedRow = GetSpeedRow(ControlMid, LeftPnt.ErrRow, RightPnt.ErrRow);		//速控赛道最远行
        }
	
}