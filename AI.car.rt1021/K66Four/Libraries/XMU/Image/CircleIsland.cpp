
#include "GlobalVar.h"
#include "BasicFind.h"
#include "FindLine.h"
#include "FillSpecialLine.h"
#include "CircleIsland.h"
#include "MainProcess.h"
//#include "FirstLineProcess.h"

#define LEFT_PNT(row, type)	LeftPnt.ErrRow = (row); LeftPnt.ErrCol = LL[LeftPnt.ErrRow]; LeftPnt.Type = (type)
#define RIGHT_PNT(row, type) RightPnt.ErrRow = (row); RightPnt.ErrCol = RL[RightPnt.ErrRow]; RightPnt.Type = (type)
#define CIRFL_TH 6			//CircleIsland Find Line Threshold
#define CIRCROSSUP_TH 7
#define FIVE_SIX_TH 10	//last is 10

#define CIRCLEFINDUP_TH 10
int LeftLost = 0, RightLost = 0;
int ChangeFlag = 0;

Point PointA, PointB, PointC, PointD;

//环岛5变6判断
int Circle5_6Judge()
{
    int count = 0;
    if(CircleFlag == CR)
    {
        for(int i = LeftPnt.ErrRow - 2; i > MAX(LeftPnt.ErrRow - 12,UP_EAGE); --i)
        {
            if(LL[i] != LEFT_EAGE && LL[i] < LeftPnt.ErrCol)
              count++;
            if(count >= 5)
            {
                return 1;
            }
        }
    }
    else if(CircleFlag == CL)
    {
        for(int i = RightPnt.ErrRow - 2; i > MAX(RightPnt.ErrRow - 12,UP_EAGE); --i)
        {
            if(RL[i] != RIGHT_EAGE && RL[i] > RightPnt.ErrCol)
              count++;
            if(count >= 5)
            {
                return 1;
            }
        }
    }
    else
      return 0;
    return 0;
}
//================================================================//
//  @brief  :		环岛斜率
//  @param  :		void
//  @note   :		void
//================================================================//
void Img_CircleSlope()
{
	//str.Format("\r\n cLeftPnt = %d,%d,%d \r\n", LeftPnt.Type, LeftPnt.ErrRow, LeftPnt.ErrCol); PrintDebug(str);
	//str.Format("\r\n cRightPnt = %d,%d,%d \r\n", RightPnt.Type, RightPnt.ErrRow, RightPnt.ErrCol); PrintDebug(str);
	if (LeftPnt.ErrRow <= UP_EAGE + 5)
	{
		L_CircleEntrance1 = g_slope(LL, LeftPnt.ErrRow, LeftPnt.ErrRow + 10);
		L_CircleEntrance2 = g_slope(LL, DOWN_EAGE - 10, DOWN_EAGE);
                if(L_CircleEntrance1 != 100 && L_CircleEntrance2 != 100)
                  L_CircleDelta = abs(L_CircleEntrance1 - L_CircleEntrance2);
		//str.Format("\r\n lll = %f,%f,%f \r\n", L_CircleEntrance1, L_CircleEntrance2, L_CircleDelta); PrintDebug(str);
	}
	else
		;
	if (RightPnt.ErrRow <= UP_EAGE + 5)
	{
		R_CircleEntrance1 = g_slope(RL, RightPnt.ErrRow, RightPnt.ErrRow + 10);
		R_CircleEntrance2 = g_slope(RL, DOWN_EAGE - 10, DOWN_EAGE);
                if(R_CircleEntrance1 != 100 && R_CircleEntrance2 != 100)
                  R_CircleDelta = abs(R_CircleEntrance1 - R_CircleEntrance2);
		//str.Format("\r\n RRR = %f,%f,%f \r\n", R_CircleEntrance1, R_CircleEntrance2, R_CircleDelta); PrintDebug(str);
	}
	else
		;

}
//================================================================//
//  @brief  :		环岛独立判断
//  @param  :		void
//  @return :		CN不是 CL左环岛 CR右环岛
//  @note   :		void
//================================================================//
int Img_JudgeCircleIsland(int type)
{
    if(g_steer_open == 1 && Img_RampFlag == 0)
    {
	
        if (Img_CircleOpen && !Img_SpecialElemFlag
                && /*LeftPnt.Type == 2 && RightPnt.Type == 2 &&*/ abs(LeftPnt.ErrRow - RightPnt.ErrRow) >= 40 && CircleFlag == CN)
        {
                if (CircleFlagSet == 1 && RightPnt.ErrRow <= UP_EAGE + 5 && RightPnt.ErrCol >= MIDDLE && LeftPnt.ErrRow >= DOWN_EAGE - 10)
                {
                        //CircleState = 1;
                        InCircleState = 2;
                        return CL;
                }
                else if (CircleFlagSet == 2 && LeftPnt.ErrRow <= UP_EAGE + 5 && LeftPnt.ErrCol <= MIDDLE && RightPnt.ErrRow >= DOWN_EAGE - 10)
                {
                        //CircleState = 1;
                        InCircleState = 2;
                        return CR;
                }
        }
        if (Img_CircleOpen && !Img_SpecialElemFlag
                && /*LeftPnt.Type == 2 && RightPnt.Type == 2 &&*/ abs(LeftPnt.ErrRow - RightPnt.ErrRow) >= 40 && CircleState == 0)
        {
                if (CircleFlagSet == 1 && R_CircleEntrance1 < 0 && R_CircleEntrance2 < 0 && R_CircleDelta < 0.6 
                    && RightPnt.ErrRow <= UP_EAGE + 5 && RightPnt.ErrCol >= MIDDLE + 7 && (LeftPnt.ErrRow == DOWN_EAGE || LL[DOWN_EAGE] <= LEFT_EAGE + 5))
                {
                        CircleState = 2;
                        InCircleState = 2;
                        return CL;
                }
                else if (CircleFlagSet == 2 && L_CircleEntrance1 > 0 && L_CircleEntrance2 > 0 && L_CircleDelta < 0.6 
                         && LeftPnt.ErrRow <= UP_EAGE + 5 && LeftPnt.ErrCol <= MIDDLE - 7 && (RightPnt.ErrRow == DOWN_EAGE || RL[DOWN_EAGE] >= RIGHT_EAGE - 5))
                {
                        CircleState = 2;
                        InCircleState = 2;
                        return CR;
                }
        }
		
		
    }
    return CircleFlag;
}

//================================================================//
//  @brief  :		环岛判断
//  @param  :		void
//  @return :		CN不是 CL左环岛 CR右环岛
//  @note   :		void
//================================================================//
int IsCircleIsland(int type)
{
#define CIRCLEDIFF_TH 2		//环岛边缘差分阈值
#if CIRCLE == 2
	int MaxRow = MIN(10, DOWN_EAGE - LeftPnt.ErrRow);
	int MaxRowR = MIN(10, DOWN_EAGE - RightPnt.ErrRow);
	if (CL == type && 1 == TrendArray(&LL[DOWN_EAGE], MaxRow)
		&& 1 == TrendArray(&LL[LeftPnt.ErrRow + MaxRow], MaxRow))
		return CL;
	else if (CR == type && -1 == TrendArray(&RL[DOWN_EAGE], MaxRow)
		&& -1 == TrendArray(&RL[RightPnt.ErrRow + MaxRow], MaxRow))
		return CR;
	else return CN;
#endif
}
//================================================================//
//  @brief  :		环岛识别
//  @param  :		void
//  @return :		void
//  @note   :		void
//================================================================//
void CircleFind(void)
{
	CircleIslandImageInit();
	//首行
	CircleFirstLine();
	//赛道类型初次判断
	g_RoadType = FirstRowProcess();
	////str.Format("\r\n RoadType = %d \r\n", g_RoadType); PrintDebug(//str);
	if (0 == g_RoadType)
	{
		FindLineNormal(1);
		if (0 == CircleState || 1 == CircleState || 2 == CircleState)
			CircleFlag = Img_JudgeCircleIsland(0);
	}
	if (1 == g_RoadType)
	{
		FindLineLost();
		if (0 == CircleState || 1 == CircleState || 2 == CircleState)
			CircleFlag = Img_JudgeCircleIsland(1);
	}
	if (2 == g_RoadType)
	{
		//FillFourCross();
		FindLineNormal(0);
	}
}

//================================================================//
//  @brief  :		环岛补图
//  @param  :		void
//  @return :		void
//  @note   :		void
//================================================================//
void CircleFill(void)
{
	//类型转化
	ChangeState(0);
	//搜线
	//CircleFindLine();
	//搜A点
	GetPointA();
	//搜B点
	GetPointB();
	//搜C点
	GetPointC();
	//搜D点
	GetPointD();
	//连接AB CD
	FillLineAB();
	FillLineCD();
	//补齐赛道
	FillAllEage();
	//补中线
	FillMiddleLine();
	//后类型转化
	//ChangeState(1);
	//str.Format("\r\n CircleState = %d,%d \r\n", CircleState, CircleFlag); PrintDebug(//str);
	//str.Format("\r\n pointa = %d,%d \r\n", PointA.Row, PointA.Col); PrintDebug(//str);
	//str.Format("\r\n pointb = %d,%d \r\n", PointB.Row, PointB.Col); PrintDebug(//str);
	//str.Format("\r\n pointc = %d,%d \r\n", PointC.Row, PointC.Col); PrintDebug(//str);
	//str.Format("\r\n pointd = %d,%d \r\n", PointD.Row, PointD.Col); PrintDebug(//str);
        Point1r = PointA.Row;
        Point1c = PointA.Col;
        Point2r = PointB.Row;
        Point2c = PointB.Col;
        Point3r = PointC.Row;
        Point3c = PointC.Col;
        Point4r = PointD.Row;
        Point4c = PointD.Col;


	
}
//================================================================//
//  @brief  :		环岛处理初始化
//  @param  :		void
//  @return :		void
//  @note   :		void
//================================================================//
void CircleIslandImageInit(void)
{
	VarInit();
	L_CircleEntrance1 = 100; R_CircleEntrance1 = 100;
	L_CircleEntrance2 = 100; R_CircleEntrance2 = 100;
	L_CircleDelta = 100; R_CircleDelta = 100;
	LeftLost = 0; RightLost = 0;
	LeftPnt.Type = RightPnt.Type = 0;
	LeftPnt.ErrRow = RightPnt.ErrRow = DOWN_EAGE;
	LeftPnt.ErrCol = LEFT_EAGE;
	RightPnt.ErrCol = RIGHT_EAGE;
}
//================================================================//
//  @brief  :		环岛首行搜线以及边缘校正
//  @param  :		void
//  @return :		void
//  @note   :		小于等于3算丢边
//================================================================//
void CircleFirstLine(void)
{
	SelectFirstLine();//首行搜线
	LeftPnt.ErrRow = RightPnt.ErrRow = DOWN_EAGE;
	LeftPnt.ErrCol = LL[DOWN_EAGE];
	RightPnt.ErrCol = RL[DOWN_EAGE];
        
	if (LL[DOWN_EAGE] <= LEFT_EAGE + 3)//25			//left lost
		LeftLost = 1;
	else LeftLost = 0;
	if (RL[DOWN_EAGE] >= RIGHT_EAGE - 3)//25		//right lost
		RightLost = 1;
	else RightLost = 0;
#define LOST_EAGE_TH 4	//判断为非丢边的阈值
	if (!LeftLost & !RightLost)  //左右均不丢，函数返回
		return;
	switch (CircleState)
	{
	case 1:
	case 2:
	case 3:
	case 5:
	case 7:
		if (LeftLost && CR == CircleFlag)
		{
			for (int i = DOWN_EAGE - 1; i > UP_EAGE; --i)
			{
				LL[i] = GetLL(i, LL[i + 1]);
				if (LL[i] > LEFT_EAGE + LOST_EAGE_TH)		//no lost edge
				{
					LEFT_PNT(i, 0);
					LeftLost = 0;
					break;
				}
			}
		}
		if (RightLost && CL == CircleFlag)
		{
			for (int i = DOWN_EAGE - 1; i > UP_EAGE; --i)
			{
				RL[i] = GetRL(i, RL[i + 1]);
				if (RL[i] < RIGHT_EAGE - LOST_EAGE_TH)
				{
					RIGHT_PNT(i, 0);
					RightLost = 0;
					break;
				}
			}
		}
		break;
	default:
		break;
	}
}
//================================================================//
//  @brief  :		环岛状态变化
//  @param  :		0补图前 1补图后
//  @return :		void
//  @note   :		void
//================================================================//
void ChangeState(int Order)
{
	if (0 == Order)			//补图前
	{
		switch (CircleState)
		{
		//case 1:
//#define LOSTTH 50
//			if (CL == CircleFlag && 1 == LeftLost && RL[DOWN_EAGE] > RIGHT_EAGE - LOSTTH)
//				CircleState = 2;
//			else if (CR == CircleFlag && 1 == RightLost && LL[DOWN_EAGE] < LEFT_EAGE + LOSTTH)
//				CircleState = 2;
//			break;
//		case 2:
//			/*if (CL == CircleFlag && 0 == LeftLost)
//				CircleState = 3;
//			else if (CR == CircleFlag && 0 == RightLost)
//				CircleState = 3;*/
//			if (CL == CircleFlag)
//			{
////				if (RL[LeftPnt.ErrRow] - LeftPnt.ErrCol >= 35 && LeftPnt.ErrRow != DOWN_EAGE)
////					CircleState = 3;
//                                for (int i = DOWN_EAGE; i > UP_EAGE + 3; --i)
//				{
//                                    if(LL[i + 1] != LEFT_EAGE && LL[i] != LEFT_EAGE && LL[i - 1] != LEFT_EAGE && LL[i - 2] != LEFT_EAGE
//                                       && LL[i - 3] != LEFT_EAGE)
//                                    {
//                                        if (LL[i + 1] - LL[i] <= LL[i] - LL[i - 1] && LL[i] - LL[i - 1] <= 2 && 
//						LL[i] - LL[i - 1] > LL[i - 2] - LL[i - 1] && LL[i] - LL[i - 1] > LL[i - 3] - LL[i - 2] 
//						&& LL[i + 1] - LL[i] > -6 && LL[i - 2] - LL[i - 1] > -6 && LL[i - 3] - LL[i - 2] > -6 && i >= 40 && AD_CircleFlag)
//					{
//						CircleState = 3;
//                                                //补图环岛状态
//                                                InCircleState = 3;
//						break;
//					}
//                                    }
//					
//				}
////                                if(LeftPnt.ErrRow < 50 && LeftPnt.ErrCol < RIGHT_EAGE / 2 
////                                   && RightPnt.ErrRow < 30 && RightPnt.ErrCol > RIGHT_EAGE / 2)
////                                {
////						CircleState = 3;
////                                                //补图环岛状态
////                                                InCircleState = 3;
////                                }
//			}
//			else if (CR == CircleFlag)
//			{
////				if (RightPnt.ErrCol - LL[RightPnt.ErrRow] >= 35 && RightPnt.ErrRow != DOWN_EAGE)
////					CircleState = 3;
//                                for (int i = DOWN_EAGE; i > UP_EAGE + 3; --i)
//				{
//                                    if (RL[i + 1] != RIGHT_EAGE && RL[i] != RIGHT_EAGE && RL[i - 1] != RIGHT_EAGE && RL[i - 2] != RIGHT_EAGE 
//                                        && RL[i - 3] != RIGHT_EAGE)
//                                    {
//                                        if (RL[i + 1] - RL[i] >= RL[i] - RL[i - 1] && RL[i] - RL[i - 1] >= -2 && 
//						RL[i] - RL[i - 1] < RL[i - 2] - RL[i - 1] && RL[i] - RL[i - 1] < RL[i - 3] - RL[i - 2] 
//						&& RL[i + 1] - RL[i] < 6 && RL[i - 2] - RL[i - 1] < 6 && RL[i - 3] - RL[i - 2] < 6 && i >= 40 && AD_CircleFlag)
//					{
//						CircleState = 3;
//                                                //补图环岛状态
//                                                InCircleState = 3;
//						break;
//					}
//                                    }
//					
//				}
////                                if(RightPnt.ErrRow < 50 && RightPnt.ErrCol > RIGHT_EAGE / 2 
////                                   && LeftPnt.ErrRow <30 && LeftPnt.ErrCol < RIGHT_EAGE / 2)
////                                {
////						CircleState = 3;
////                                                //补图环岛状态
////                                                InCircleState = 3;
////                                }
//			}
//			/*if ((RightPnt.ErrCol - LeftPnt.ErrCol >= 40) && LeftPnt.ErrRow <= 25 && RightPnt.ErrRow <= 25)
//				CircleState = 3;*/
//			break;
		case 3:
                        {
                            if (CL == CircleFlag && RL[DOWN_EAGE] >= RIGHT_EAGE - 5)
//                            if (CL == CircleFlag && RL[DOWN_EAGE] >= RIGHT_EAGE - 3 && RL[DOWN_EAGE - 1] >= RIGHT_EAGE - 3 && RL[DOWN_EAGE - 2] >= RIGHT_EAGE - 3
//                                 && RL[DOWN_EAGE - 3] >= RIGHT_EAGE - 5 && RL[DOWN_EAGE - 4] >= RIGHT_EAGE - 5)
                            {
                                CircleState = 4;
                                //补图环岛状态
                                InCircleState = 4;
                            }	
                            else if (CR == CircleFlag && LL[DOWN_EAGE] <= LEFT_EAGE + 5)
//                            else if (CR == CircleFlag && LL[DOWN_EAGE] <= LEFT_EAGE + 3 && LL[DOWN_EAGE - 1] <= LEFT_EAGE + 3 && LL[DOWN_EAGE - 2] <= LEFT_EAGE + 3
//                                      && LL[DOWN_EAGE - 3] <= LEFT_EAGE + 5 && LL[DOWN_EAGE - 4] <= LEFT_EAGE + 5)
                            {
                                CircleState = 4;
                                //补图环岛状态
                                InCircleState = 4;
                            }
                            //延距进5
                            if(Dist_Circle35 == 1)
                            {
                                CircleState = 5;
                                //补图环岛状态
                                InCircleState = 5;
                                Dist_Circle35 = 0;
                            }
                        }
			break;
                case 4:
                        if(YawAngle > 60 || YawAngle < - 60)
                        {
                                  CircleState = 5;
                                  //补图环岛状态
                                  InCircleState = 5;
                        }
			else if (CL == CircleFlag && RightPnt.ErrCol < MIDDLE + 7)
			{
                              if(RL[DOWN_EAGE] <= RIGHT_EAGE - 15)
                              {
                                  CircleState = 5;
                                  //补图环岛状态
                                  InCircleState = 5;
                              }
//				int i;
//				for(i = DOWN_EAGE - 1; i > DOWN_EAGE - 11; --i)
//				{
//					if(RL[i] < RIGHT_EAGE && RL[i] >= RL[i - 1])
//					{
//						;
//					}
//					else
//					{
//						break;
//					}
//				}
//				if(i <= DOWN_EAGE - 9)
//				{
//					CircleState = 5;
//					//补图环岛状态
//					InCircleState = 5;
//				}
			}
			else if (CR == CircleFlag && LeftPnt.ErrCol > MIDDLE - 7)
			{
				//int i;
                                if(LL[DOWN_EAGE] >= LEFT_EAGE + 15)
                                {
                                    CircleState = 5;
                                    //补图环岛状态
                                    InCircleState = 5;
                                }
//				for(i = DOWN_EAGE - 1; i > DOWN_EAGE - 11; --i)
//				{
//					if(LL[i] > LEFT_EAGE && LL[i] <= LL[i - 1])
//					{
//						;
//					}
//					else
//					{
//						break;
//					}
//				}
//				if(i <= DOWN_EAGE - 9)
//				{
//					CircleState = 5;
//					//补图环岛状态
//					InCircleState = 5;
//				}
                                
//				if(LL[DOWN_EAGE] > LEFT_EAGE && LL[DOWN_EAGE - 1] > LEFT_EAGE && LL[DOWN_EAGE - 2] > LEFT_EAGE
//						&& LL[DOWN_EAGE - 3] > LEFT_EAGE && LL[DOWN_EAGE - 4] > LEFT_EAGE && LL[DOWN_EAGE - 5] > LEFT_EAGE
//						&& LL[DOWN_EAGE - 5] > LL[DOWN_EAGE - 4] && LL[DOWN_EAGE - 4] > LL[DOWN_EAGE - 3] && LL[DOWN_EAGE - 3] > LL[DOWN_EAGE - 2]
//						&& LL[DOWN_EAGE - 2] > LL[DOWN_EAGE - 1] && LL[DOWN_EAGE - 1] > LL[DOWN_EAGE])
//				{
//							CircleState = 5;
//							//补图环岛状态
//							InCircleState = 5;
//				}
                        }
			break;
//		case 4:
//			if (CL == CircleFlag && RL[DOWN_EAGE] <= RIGHT_EAGE - 30)
//			{
//                            CircleState = 5;
//                            //补图环岛状态
//                            InCircleState = 5;
//                        }
//			else if (CR == CircleFlag && LL[DOWN_EAGE] >= LEFT_EAGE + 30)
//			{
//                            CircleState = 5;
//                            //补图环岛状态
//                            InCircleState = 5;
//                        }
//			break;
		//修正到这里
		case 5:
                        {
                              static int circle5_count = 0;
                              static int circle5_count0 = 0;
                              if(1)//circle5_count == 0)
                              {
                                      circle5_count0++;
                                      MaxSteerDuty5 += SteerDuty;
                              }
                              if(IndJudgeCircle() && Dist_Circle56 == 1)
                              {             
                                  MaxSteerDuty5 = MaxSteerDuty5 / circle5_count0;
                                  CircleState = 6;
                                  InCircleState = 6;
                                  circle5_count = 0;
                                  Dist_Circle56 = 0;
                                  circle5_count0 = 0;
                                  temp = 3;
                              }
                              else if((YawAngle >= 250 || YawAngle <= -250) && Dist_Circle56 == 1)
                              {
                                    MaxSteerDuty5 = MaxSteerDuty5 / circle5_count0;
                                    CircleState = 6;
                                    InCircleState = 6;
                                    circle5_count = 0;
                                    Dist_Circle56 = 0;
                                    circle5_count0 = 0;
                                    temp = 2;
                              }
                              else if(Dist_Circle56 == 100)
                              {
                                  if (CL == CircleFlag)
                                  {
                                          float r_slope5;
                                          r_slope5 = circle_slope(RL, 55, 65, 1);
                                          //bbb = r_slope5;xw
                                          if (r_slope5 > 0 || r_slope5 == -1)
                                          {
                                              if((/*InCircleSize == 0 && */Circle5_6Judge()) || (RightPnt.ErrRow > DOWN_EAGE - FIVE_SIX_TH/* && InCircleSize == 1*/))
                                              {
                                                 
                                                  //拐点确认
                                                  //if (RIGHT_EAGE >= RightPnt.ErrCol)
                                                  //{
                                                      circle5_count++;
                                                      if(circle5_count >= 3)
                                                      {
                                                          CircleState = 6;
                                                          //补图环岛状态
                                                          InCircleState = 6;
                                                          
                                                          MaxSteerDuty5 = MaxSteerDuty5 / circle5_count0;
                                                          circle5_count0 = 0;
                                                          circle5_count = 0;
                                                          Dist_Circle56 = 0;
                                                      }
                                                  //}                                              
//                                                      else if(circle5_count != 0)
//                                                     {
//                                                       circle5_count = 0;
//                                                     }
                                              }                                       
                                              else
                                              {
                                                  circle5_count = 0;
                                              }                                                 
                                          }                                              
//                                          else
//                                          {
//                                              circle5_count = 0;
//                                          }
                                  }
                                  else if (CR == CircleFlag)
                                  {
                                          float l_slope5;
                                          l_slope5 = circle_slope(LL, 55, 65, 0);
                                          //bbb = l_slope5;
                                          if (l_slope5 < 0)
                                          {
                                                 if((/*InCircleSize == 0 && */Circle5_6Judge()) || (LeftPnt.ErrRow > DOWN_EAGE - FIVE_SIX_TH/* && InCircleSize == 1*/))
//                                                 if (Circle5_6Judge() || LeftPnt.ErrRow > DOWN_EAGE - FIVE_SIX_TH)// || DOWN_EAGE == LeftPnt.ErrRow)
                                                 {
                                                        //拐点确认
                                                        //if (LEFT_EAGE <= LeftPnt.ErrCol)
                                                        //{
                                                            circle5_count++;
                                                            if(circle5_count >= 3)
                                                            {
                                                                CircleState = 6;
                                                                //补图环岛状态
                                                                InCircleState = 6;
                                                                MaxSteerDuty5 = MaxSteerDuty5 / circle5_count0;
                                                                circle5_count0 = 0;
                                                                circle5_count = 0;
                                                                Dist_Circle56 = 0;
                                                                temp = 4;
                                                            }
                                                        //}
                                                        /*else if(circle5_count != 0)
                                                        {
                                                              circle5_count = 0;
                                                        }*/
                                                }   
                                                else
                                                {
                                                      circle5_count = 0;
                                                }
                                          }                                      
//                                          else
//                                          {
//                                                circle5_count = 0;
//                                          }
                                  }
                             }
                        
                        }
			break;
		case 6:
                  {
                        static int count6 = 0;
                        if(YawAngle >= 310 || YawAngle <= - 310)//315
                        {
                            CircleState = 7;
                           //补图环岛状态
                            InCircleState = 7;
                            YawAngle = 0;
                            count6 = 0;
                            temp = 1;
                        }
			else if (CircleFlag == 3)//(CL == CircleFlag && 0 == RightLost)
			{
				int NewRow = DOWN_EAGE, OldRow = DOWN_EAGE;
				int TmpCol = RL[DOWN_EAGE];
				while (1)
				{
					NewRow = SearchUpEage(OldRow + 2, TmpCol - 1);
					if (OldRow - NewRow > 12 || OldRow > DOWN_EAGE + 10 || TmpCol < MIDDLE - MIDDLE / 2)
					{
						break;
					}
					else if (OldRow <= DOWN_EAGE - 20)
					{
						//记得要改
						if (/*IndJudgeCircle() || !Circle5_6Judge()*/1)
                                                {
                                                    count6++;
                                                    if(count6 >= 3)//4
                                                    {
                                                        CircleState = 7;
                                                        //补图环岛状态
                                                        InCircleState = 7;
                                                        count6 = 0;
                                                        YawAngle = 0;
                                                        temp = 5;
                                                    }
                                                    
                                                }
						break;
					}
					else
					{
						OldRow = NewRow;
						TmpCol--;
					}
				}
			}
			else if (CircleFlag == 4)//(CR == CircleFlag && 0 == LeftLost)
			{
                                static int count67 = 0;
				int NewRow = DOWN_EAGE, OldRow = DOWN_EAGE;
				int TmpCol = LL[DOWN_EAGE];
				while (1)
				{
					NewRow = SearchUpEage(OldRow + 2, TmpCol + 1);
					if (OldRow - NewRow > 12 || OldRow > DOWN_EAGE + 10 || TmpCol > MIDDLE + MIDDLE / 2)
					{ 
						break;
					}
					else if (OldRow <= DOWN_EAGE - 20)//???????
					{
						//记得要改
						if (/*IndJudgeCircle() || !Circle5_6Judge()*/1)
                                                {
                                                    count67++;
                                                    if(count67 >= 3)//4
                                                    {
                                                        CircleState = 7;
                                                       //补图环岛状态
                                                        InCircleState = 7;
                                                        count67 = 0;
                                                        YawAngle = 0;
                                                        temp = 6;
                                                    }
                                                    
                                                }
						break;
					}
					else
					{
						OldRow = NewRow;
						TmpCol++;
					}
				}
			}
                  }
			break;
		case 7:			//延距清标志
//			if (CL == CircleFlag && !LeftLost && Dist_ClearSevenFlag
//				|| CR == CircleFlag && !RightLost && Dist_ClearSevenFlag)
//				ChangeFlag = 1;
                        if (/*(CL == CircleFlag && !LeftLost && Dist_ClearSevenFlag)f
				|| (CR == CircleFlag && !RightLost && Dist_ClearSevenFlag)*/Dist_ClearSevenFlag)
                        {
                              //InCircleSize = !InCircleSize;
                              CircleState = 0;
                              //补图环岛状态
                              InCircleState = 0;
                              CircleFlag = 0;
                              Dist_ClearSevenFlag = 0;
                              CircleCount = 0;                    //环岛计数由1/2变3
                              AD_CircleFlag = 0;
                              g_garage_open = 1;
                        }

			break;
		default:
			break;
		}
	}
	else			//补图后
	{
//		switch (CircleState)
//		{
//		case 5:
//			if (1 == ChangeFlag)
//			{
//				ChangeFlag = 0;
//				CircleState = 6;
//			}
//			break;
//		case 7:
//			if (1 == ChangeFlag)
//			{
//				ChangeFlag = 0;
//				CircleState = 0;
//				CircleFlag = 0;
//			}
//			break;
//		default:
//			break;
//		}
          ;
	}
}
//================================================================//
//  @brief  :		环岛搜线
//  @param  :		void
//  @return :		void
//  @note   :		void
//================================================================//
void CircleFindLine(void)
{
	FindLineNormal(0);
	switch (CircleState)
	{
	case 5:
	case 6:
		//拐点判断
		if (CL == CircleFlag)
		{
			LeftPnt.Type = 2;
			RightPnt.Type = 1;
			for (int i = DOWN_EAGE - 1; i > RightPnt.ErrRow; --i)
			{
				int TmpRow = SearchUpEage(i, RL[i] - 1);
				if (i - TmpRow > CIRCROSSUP_TH || UP_EAGE == TmpRow)
				{
					RIGHT_PNT(i, 2);
					break;
				}
			}
		}
		else if (CR == CircleFlag)
		{
			RightPnt.Type = 2;
			LeftPnt.Type = 1;
			for (int i = DOWN_EAGE - 1; i > LeftPnt.ErrRow; --i)
			{
				int TmpRow = SearchUpEage(i, LL[i] + 1);
				if (i - TmpRow > CIRCROSSUP_TH || UP_EAGE == TmpRow)
				{
					LEFT_PNT(i, 2);
					break;
				}
			}
		}
		break;
	default:
		break;
	}
}
//================================================================//
//  @brief  :		搜A点
//  @param  :		void
//  @return :		void
//  @note   :		void
//================================================================//
void GetPointA(void)
{
	switch (InCircleState)
	{
	case 1:
		if (CL == CircleFlag)
		{
			PointA.Row = LeftPnt.ErrRow;
			PointA.Col = LeftPnt.ErrCol;
		}
		else if (CR == CircleFlag)
		{
			PointA.Row = RightPnt.ErrRow;
			PointA.Col = RightPnt.ErrCol;
		}
		break;
        case 2:
		//give const PointA
		if (CL == CircleFlag)
                {
                    PointA.Row = DOWN_EAGE;
                    PointA.Col = ConstLeftEage;
//                    for(int i = DOWN_EAGE; i >= DOWN_EAGE - 5; --i)
//                    {
//                        if(RL[i] < RIGHT_EAGE)
//                        {
//                            PointA.Row = i;
//                            PointA.Col = RL[i] - MidOffset[i] * 1.8;// - Offset * 2;
//                            break;
//                        }
//                    }
                }
		else if (CR == CircleFlag)
                {
                    PointA.Row = DOWN_EAGE;
                    PointA.Col = ConstRightEage;
//                    for(int i = DOWN_EAGE; i >= DOWN_EAGE - 5; --i)
//                    {
//                        if(LL[i] > LEFT_EAGE)
//                        {
//                            PointA.Row = i;
//                            PointA.Col = LL[i] + MidOffset[i] * 1.8;// + Offset * 2;
//                            break;
//                        }
//                    }
                }
                break;
	case 4:
		PointA.Row = DOWN_EAGE;
		if (CL == CircleFlag)
			PointA.Col = LL[DOWN_EAGE] + 1;
		else if (CR == CircleFlag)
			PointA.Col = RL[DOWN_EAGE] - 1;
		break;
//        case 6:
//	{
//          if(CL == CircleFlag)
//          {
//		if (/*LL[DOWN_EAGE] == LEFT_EAGE*/1)
//                {
//                        PointA.Row = DOWN_EAGE;
//                        PointA.Col = MIDDLE;            //ConstRightEage
//                }
//          }
//          else if(CR == CircleFlag)
//          {
//                if(/*RL[DOWN_EAGE] == RIGHT_EAGE*/1)
//                {
//                        PointA.Row = DOWN_EAGE;
//                        PointA.Col = ConstRightEage;
//                }
//          }
//	}
//	break;
	default:
		break;
	}
}

//================================================================//
//  @brief  :		搜B点
//  @param  :		void
//  @return :		void
//  @note   :		void
//================================================================//
void GetPointB(void)
{

	switch (InCircleState)
	{
//	case 1:
//		PointB.Row = UP_EAGE;
//		break;
//	case 2:
//		//if (CL == CircleFlag)		//找最大值
//		//{
//		//	int TmpRow;
//		//	for (int i = LeftPnt.ErrCol; i <= RIGHT_EAGE; ++i)
//		//	{
//		//		TmpRow = SearchUpEage(LeftPnt.ErrRow, i);
//		//		if (i - TmpRow > 4 || TmpRow == UP_EAGE)		//是拐点
//		//		{
//		//			PointB.Row = TmpRow;
//		//			PointB.Col = i;
//		//			break;
//		//		}
//		//	}
//		//}
//		//if (CR == CircleFlag)		//找最大值
//		//{
//		//	int TmpRow;
//		//	for (int i = RightPnt.ErrCol; i >= LEFT_EAGE; --i)
//		//	{
//		//		TmpRow = SearchUpEage(RightPnt.ErrRow, i);
//		//		if (i - TmpRow > 4 || TmpRow == UP_EAGE)		//是拐点
//		//		{
//		//			PointB.Row = TmpRow;
//		//			break;
//		//		}
//		//	}
//		//}
//		////str.Format("\r\n B = %d \r\n", PointB.Row); PrintDebug(//str);
//		PointB.Row = UP_EAGE;
//		break;
	case 3:
		if (CL == CircleFlag)		//找最大值
		{
			int tmp = DOWN_EAGE;
			for (int i = LeftPnt.ErrRow; i < DOWN_EAGE; i++)
			{
				if (LL[i] > LL[tmp])
					tmp = i;
			}
			PointB.Row = tmp;
			PointB.Col = LL[PointB.Row];
		}
		else if (CR == CircleFlag)		//找最小值
		{
			int tmp = DOWN_EAGE;
			for (int i = RightPnt.ErrRow; i < DOWN_EAGE; i++)
			{
				if (RL[i] < RL[tmp])
					tmp = i;
			}
			PointB.Row = tmp;
			PointB.Col = RL[PointB.Row];
		}
		break;
	case 4:
		PointB = PointA;
		break;
//        case 6:
//	{
//		if (CL == CircleFlag)
//		{
//			if (/*LL[DOWN_EAGE] == LEFT_EAGE*/1)
//			{
//				PointB.Row = UP_EAGE + 1;// UP_EAGE + 1
//				PointB.Col = 5;    //94
//			}
//		}
//                if (CR == CircleFlag)
//		{
//			if (/*RL[DOWN_EAGE] == RIGHT_EAGE*/1)
//			{
//				PointB.Row = 50;// UP_EAGE + 1,40
//				PointB.Col = 185;
//			}
//		}
//	}
//	break;
	default:
		break;
	}
}

//================================================================//
//  @brief  :		搜C点
//  @param  :		void
//  @return :		void
//  @note   :		void
//================================================================//
void GetPointC(void)
{
	//const int UpTh = 3;
	switch (InCircleState)
	{
	case 1:
		if (CL == CircleFlag)
		{
			PointC.Row = RightPnt.ErrRow + 1;
			PointC.Col = RL[PointC.Row];
		}
		else if (CR == CircleFlag)
		{
			PointC.Row = LeftPnt.ErrRow + 1;
			PointC.Col = LL[PointC.Row];
		}
		break;
	case 2:
		if (CL == CircleFlag)
		{
			PointC.Row = RightPnt.ErrRow + 1;
			PointC.Col = RL[PointC.Row];
		}
		else if (CR == CircleFlag)
		{
			PointC.Row = LeftPnt.ErrRow + 1;
			PointC.Col = LL[PointC.Row];
		}
		break;
	case 3:
		if (CL == CircleFlag)		//Left CircleIsland
		{
			PointC.Row = SearchUpEage(PointB.Row - 1, PointB.Col + 11);
			PointC.Col = PointB.Col + 11;
		}
		else if (CR == CircleFlag)		//Right CircleIsland
		{
			PointC.Row = SearchUpEage(PointB.Row - 1, PointB.Col - 11);
			PointC.Col = PointB.Col - 11;
		}
		break;
	case 4:
		PointC.Row = UP_EAGE;
		PointC.Col = PointB.Col;
		break;
	case 5:
		if (CL == CircleFlag)
		{
			//if (RightPnt.Type == 2 && RightPnt.ErrRow > DOWN_EAGE - FIVE_SIX_TH)// || DOWN_EAGE == RightPnt.ErrRow)
			//{
			//	//拐点确认
			//	if (RIGHT_EAGE >= RightPnt.ErrCol)
			//		ChangeFlag = 1;
			//}
			PointC.Col = (LeftPnt.ErrCol + RightPnt.ErrCol) >> 1;
			PointC.Row = SearchUpEage((LeftPnt.ErrRow + RightPnt.ErrRow) >> 1, PointC.Col);
		}
		else if (CR == CircleFlag)
		{
			//if (LeftPnt.Type == 2 && LeftPnt.ErrRow > DOWN_EAGE - FIVE_SIX_TH)// || DOWN_EAGE == LeftPnt.ErrRow)
			//{
			//	//拐点确认
			//	if (LEFT_EAGE <= LeftPnt.ErrCol)
			//		ChangeFlag = 1;
			//}
			PointC.Col = (LeftPnt.ErrCol + RightPnt.ErrCol) >> 1;
			PointC.Row = SearchUpEage((RightPnt.ErrRow + LeftPnt.ErrRow) >> 1, PointC.Col);
		}
		else return;
		break;
//	case 6:
//		if (CL == CircleFlag)
//		{
//                        if (/*LL[DOWN_EAGE] == LEFT_EAGE*/1)
//			{
//				PointC.Row = UP_EAGE + 1;
//				PointC.Col = 5;
//			}
//			else
//			{
//				int Eage = MIN(ConstRightEage, RightPnt.ErrCol);
//				PointC.Col = (LeftPnt.ErrCol + Eage) >> 1;
//				//PointC.Col = LeftPnt.ErrCol;
//				PointC.Row = SearchUpEage(LeftPnt.ErrRow - 1, PointC.Col);
//			}
//		
//		}
//		else if (CR == CircleFlag)
//		{
//                        if (/*RL[DOWN_EAGE] == RIGHT_EAGE*/1)
//			{
//				PointC.Row = UP_EAGE + 1;
//				PointC.Col = 157;//94
//			}
//			else
//			{
//				int Eage = MAX(ConstLeftEage, LeftPnt.ErrCol);
//                                PointC.Col = (Eage + RightPnt.ErrCol) >> 1;
//                                //PointC.Col = RightPnt.ErrCol;
//                                PointC.Row = SearchUpEage(RightPnt.ErrRow - 1, PointC.Col);
//			}
//		}
//		//PointC.Row = SearchUpEage((LeftPnt.ErrRow + RightPnt.ErrRow) >> 1, PointC.Col);
//		break;
	case 7:
		if (CL == CircleFlag)
		{
			PointC.Row = RightPnt.ErrRow;
			PointC.Col = RightPnt.ErrCol;
		}
		else if (CR == CircleFlag)
		{
			PointC.Row = LeftPnt.ErrRow;
			PointC.Col = LeftPnt.ErrCol;
		}
		break;
	default:
		break;
	}
}

//================================================================//
//  @brief  :		搜D点
//  @param  :		void
//  @return :		void
//  @note   :		void
//================================================================//
void GetPointD(void)
{
	switch (InCircleState)
	{
	case 1:
		if (CL == CircleFlag)		//left CircleIsland
		{
			PointD.Row = DOWN_EAGE;
			PointD.Col = RL[DOWN_EAGE];
		}
		else if (CR == CircleFlag)
		{
			PointD.Row = DOWN_EAGE;
			PointD.Col = LL[DOWN_EAGE];
		}
		else return;
		break;
	case 2:
		if (CL == CircleFlag)		//left CircleIsland
		{
			PointD.Row = DOWN_EAGE;
			PointD.Col = RL[DOWN_EAGE];
		}
		else if (CR == CircleFlag)
		{
			PointD.Row = DOWN_EAGE;
			PointD.Col = LL[DOWN_EAGE];
		}
		else return;
		break;
	case 3:
		if (CL == CircleFlag)
		{
			PointD.Row = DOWN_EAGE;
			PointD.Col = MIN(ConstRightEage, RL[DOWN_EAGE]);
		}
		else if (CR == CircleFlag)
		{
			PointD.Row = DOWN_EAGE;
			PointD.Col = MAX(ConstLeftEage, LL[DOWN_EAGE]);
		}
		else return;
		break;
	case 4:
		PointD.Row = DOWN_EAGE;
		if (CL == CircleFlag)
		{
			if (LL[DOWN_EAGE] + 130 > RIGHT_EAGE)
				PointD.Col = RIGHT_EAGE;
			else PointD.Col = LL[DOWN_EAGE] + 130;
		}
		else if (CR == CircleFlag)
		{
			if (RL[DOWN_EAGE] - 130 < LEFT_EAGE)
				PointD.Col = LEFT_EAGE;
			else
				PointD.Col = RL[DOWN_EAGE] - 130;
		}
		else return;
		break;
	case 5:
		if (CL == CircleFlag)
		{
			PointD.Row = RightPnt.ErrRow;
			PointD.Col = RightPnt.ErrCol;
		}
		else if (CR == CircleFlag)
		{
			PointD.Row = LeftPnt.ErrRow;
			PointD.Col = LeftPnt.ErrCol;
		}
		break;
//	case 6:
//		if (CL == CircleFlag)
//		{
//                        if (/*LL[DOWN_EAGE] == LEFT_EAGE*/1)
//			{
//				PointD.Row = DOWN_EAGE;
//				PointD.Col = ConstLeftEage;
//			}
//			else
//			{
//				PointD.Row = LeftPnt.ErrRow;
//				PointD.Col = MAX(ConstLeftEage, LeftPnt.ErrCol);
////                                PointD.Row = RightPnt.ErrRow;
////                                PointD.Col = MIN(ConstRightEage, RightPnt.ErrCol);
//			}
//			
//		}
//		else if (CR == CircleFlag)
//		{
//                         if (/*RL[DOWN_EAGE] == RIGHT_EAGE*/1)
//			{
//				PointD.Row = DOWN_EAGE;
//				PointD.Col = ConstLeftEage;
//			}
//			else
//			{
//				 PointD.Row = DOWN_EAGE;//LeftPnt.ErrRow;
//                                 PointD.Col = ConstLeftEage;//MAX(ConstLeftEage, LeftPnt.ErrCol);
////			         PointD.Row = LeftPnt.ErrRow;
////			         PointD.Col = MAX(ConstLeftEage, LeftPnt.ErrCol);
//			}
//                       
//		}
//		break;
	case 7:
		if (CL == CircleFlag)
		{
			if (RL[DOWN_EAGE] == RIGHT_EAGE)
			{
				PointD.Col = MIN(RL[DOWN_EAGE], ConstRightEage);
				PointD.Row = DOWN_EAGE;
			}
			else
			{
				PointD.Col = RL[DOWN_EAGE];
				PointD.Row = DOWN_EAGE;
			}
		}
		else if (CR == CircleFlag)
		{
			if (LL[DOWN_EAGE] == LEFT_EAGE)
			{
				PointD.Col = MAX(LL[DOWN_EAGE], ConstLeftEage);
				PointD.Row = DOWN_EAGE;
			}
			else
			{
				PointD.Col = LL[DOWN_EAGE];
				PointD.Row = DOWN_EAGE;
			}
		}
		break;
	default:
		break;
	}
}
//================================================================//
//  @brief  :		连接AB
//  @param  :		void
//  @return :		void
//  @note   :		void
//================================================================//
void FillLineAB(void)
{
	switch (InCircleState)
	{
	case 1:
		if (CL == CircleFlag)
		{
			PointB.Row = PointC.Row;
			PointB.Col = PointC.Col - MidOffset[PointB.Row] * 2;
			LL[PointB.Row] = PointB.Col;
			LL[PointA.Row] = PointA.Col;
			FillLinePoint(LL, PointA.Row, PointB.Row);
			LEFT_PNT(PointB.Row, 0);
		}
		else if (CR == CircleFlag)
		{
			PointB.Row = PointC.Row;
			PointB.Col = PointC.Col + MidOffset[PointB.Row] * 2;
			RL[PointB.Row] = PointB.Col;
			RL[PointA.Row] = PointA.Col;
			FillLinePoint(RL, PointA.Row, PointB.Row);
			RIGHT_PNT(PointB.Row, 0);
		}
		break;
	case 2:
		if (CL == CircleFlag)
		{
			PointB.Row = PointC.Row;
			PointB.Col = PointC.Col - MidOffset[PointB.Row] * 2;
			LL[PointB.Row] = PointB.Col;
			LL[PointA.Row] = PointA.Col;
			FillLinePoint(LL, PointA.Row, PointB.Row);
			LEFT_PNT(PointB.Row, 0);
		}
		else if (CR == CircleFlag)
		{
			PointB.Row = PointC.Row;
			PointB.Col = PointC.Col + MidOffset[PointB.Row] * 2;
			RL[PointB.Row] = PointB.Col;
			RL[PointA.Row] = PointA.Col;
			FillLinePoint(RL, PointA.Row, PointB.Row);
			RIGHT_PNT(PointB.Row, 0);
		}
		break;
//        case 6:
//	{
//          if(CL == CircleFlag)
//          {
//		if (/*LL[DOWN_EAGE] == LEFT_EAGE*/1)
//                {
//                        RL[PointA.Row] = PointA.Col;
//                        RL[PointB.Row] = PointB.Col;
//                        FillLinePoint(RL, PointA.Row, PointB.Row);
//                        RIGHT_PNT(PointB.Row, 0);
//                }
//          }
//          else if(CR == CircleFlag)
//          {
//		if (/*RL[DOWN_EAGE] == RIGHT_EAGE*/1)
//                {
//                        RL[PointA.Row] = PointA.Col;
//                        RL[PointB.Row] = PointB.Col;
//                        FillLinePoint(RL, PointA.Row, PointB.Row);
//                        RIGHT_PNT(PointB.Row, 0);
//                }
//          }
//        }
//	break;
	case 7:
		if (CL == CircleFlag)
		{
			LL[PointD.Row] = LeftPnt.ErrCol = PointD.Col - MidOffset[PointD.Row] * 2;
			LeftPnt.ErrRow = PointD.Row;
			LeftPnt.Type = 2;
		}
		else if (CR == CircleFlag)
		{
			RL[PointD.Row] = RightPnt.ErrCol = PointD.Col + MidOffset[PointD.Row] * 2;
			RightPnt.ErrRow = DOWN_EAGE;
			RightPnt.Type = 2;
		}
		break;
	default:
		break;
	}
}
//================================================================//
//  @brief  :		连接CD
//  @param  :		void
//  @return :		void
//  @note   :		void
//================================================================//
void FillLineCD(void)
{
	switch (InCircleState)
	{
	case 3:
		if (CL == CircleFlag)
		{
			RL[PointC.Row] = PointC.Col;
			RL[PointD.Row] = PointD.Col;
			//FillLinePoint(RL, PointD.Row, PointC.Row);
			Connect_Point_Curve(RL, PointD.Row, PointD.Col, PointC.Row, PointC.Col);
			RIGHT_PNT(PointC.Row, 1);
		}
		else if (CR == CircleFlag)
		{
			LL[PointC.Row] = PointC.Col;
			LL[PointD.Row] = PointD.Col;
			//FillLinePoint(LL, PointD.Row, PointC.Row);
			Connect_Point_Curve(LL, PointD.Row, PointD.Col, PointC.Row, PointC.Col);
			LEFT_PNT(PointC.Row, 1);
		}
		break;
	case 4:
		if (CL == CircleFlag)
		{
			RL[PointC.Row] = PointC.Col;
			RL[PointD.Row] = PointD.Col;
			//FillLinePoint(RL, PointD.Row, PointC.Row);
			Connect_Point_Curve(RL, PointD.Row, PointD.Col, PointC.Row, PointC.Col);
			RIGHT_PNT(PointC.Row, 1);
		}
		else if (CR == CircleFlag)
		{
			LL[PointC.Row] = PointC.Col;
			LL[PointD.Row] = PointD.Col;
			//FillLinePoint(LL, PointD.Row, PointC.Row);
			Connect_Point_Curve(LL, PointD.Row, PointD.Col, PointC.Row, PointC.Col);
			LEFT_PNT(PointC.Row, 1);
		}
		break;
	case 5:
		if (CL == CircleFlag && 2 == RightPnt.Type)
		{
			RL[PointD.Row] = PointD.Col;
			RL[PointC.Row] = PointC.Col;
			FillLinePoint(RL, PointD.Row, PointC.Row);
			RIGHT_PNT(PointC.Row, 1);
		}
		else if (CR == CircleFlag && 2 == LeftPnt.Type)
		{
			LL[PointD.Row] = PointD.Col;
			LL[PointC.Row] = PointC.Col;
			FillLinePoint(LL, PointD.Row, PointC.Row);
			LEFT_PNT(PointC.Row, 1);
		}
		break;
//        case 6:
//                if (CL == CircleFlag)
//                {
//                        LL[PointC.Row] = PointC.Col;
//                        LL[PointD.Row] = PointD.Col;
//                        //FillLinePoint(RL, PointD.Row, PointC.Row);
//                        Connect_Point_Curve(LL, PointD.Row, PointD.Col, PointC.Row, PointC.Col);
//                        LEFT_PNT(PointC.Row, 1);
//                }
//                else if (CR == CircleFlag)
//                {
//                        LL[PointC.Row] = PointC.Col;
//                        LL[PointD.Row] = PointD.Col;
//                        //FillLinePoint(LL, PointD.Row, PointC.Row);
//                        Connect_Point_Curve(LL, PointD.Row, PointD.Col, PointC.Row, PointC.Col);
//                        LEFT_PNT(PointC.Row, 1);
//                }
//                break;	
	case 7:
		if (CL == CircleFlag)
		{
			// 增加了|| (RightPnt.ErrCol == RIGHT_EAGE && RightPnt.ErrRow == DOWN_EAGE)
			if (PointD.Col != RL[DOWN_EAGE] || (RightPnt.ErrCol == RIGHT_EAGE && RightPnt.ErrRow == DOWN_EAGE))
			{
				RL[PointD.Row] = PointD.Col;
				RL[PointC.Row] = PointC.Col;
				FillLinePoint(RL, PointD.Row, PointC.Row);
				RIGHT_PNT(PointC.Row, 1);
			}
		}
		else if (CR == CircleFlag)
		{
			// 增加了|| (LeftPnt.ErrCol == LEFT_EAGE && LeftPnt.ErrRow == DOWN_EAGE)
			if (PointD.Col != LL[DOWN_EAGE] || (LeftPnt.ErrCol == LEFT_EAGE && LeftPnt.ErrRow == DOWN_EAGE))
			{
				LL[PointD.Row] = PointD.Col;
				LL[PointC.Row] = PointC.Col;
				FillLinePoint(LL, PointD.Row, PointC.Row);
				LEFT_PNT(PointC.Row, 1);
			}
		}
                break;
	default:
		break;
	}
}
//================================================================//
//  @brief  :		补齐赛道
//  @param  :		void
//  @return :		void
//  @note   :		void
//================================================================//
void FillAllEage(void)
{
	switch (InCircleState)
	{
	case 1:
	case 2:
	case 3:
	case 7:
		FindLineNormal(0);
		break;
	default:
		break;
	}
}

//================================================================//
//  @brief  :		给定斜率补线
//  @param  :		void
//  @return :		行数
//  @note   :		void
//================================================================//
int FillLineGradient(int* line, int row, int col, float Gradient)
{
	int* p = line + row - 1;
	for (int i = row - 1; i > UP_EAGE; i--)
	{
		*p = (int)((i - row) * Gradient + col + 0.5);
		if (*p > RIGHT_EAGE || *p < LEFT_EAGE)
		{
			return i + 1;
		}
		p--;
	}
	return UP_EAGE + 1;
}

//================================================================//
//  @brief  :		抛物线连接两点
//  @param  :		两点行坐标(x_position)和列坐标(y_position)
//  @return :		void
//  @note   :		针对Left_border[],Right_border[],Middle_line[];
//					point1为中间点，point2为两侧点
//================================================================//
void Connect_Point_Curve(int* line_process, int x_position1, int y_position1, int x_position2, int y_position2)
{
	float c_K, c_B;
	if (x_position1 == x_position2 || y_position1 == y_position2)
	{
		return;
	}
	line_process += x_position1;
	if (y_position1 > y_position2)
	{
		c_K = (float)(y_position1 - y_position2) * (y_position1 + y_position2) / (x_position1 - x_position2);
		c_B = c_K * x_position1 - y_position1 * y_position1;
	}
	else
	{
		c_K = (float)(y_position2 - y_position1) * (y_position1 + y_position2) / (x_position1 - x_position2);
		c_B = c_K * x_position1 - y_position2 * y_position2;
	}

	if (y_position1 > y_position2)
	{
		for (int c_point = x_position1; c_point >= x_position2; c_point--)
		{
			*line_process = (int)sqrt(c_K * c_point - c_B);
			line_process--;
		}
	}
	else
	{
		for (int c_point = x_position1; c_point >= x_position2; c_point--)
		{
			*line_process = y_position2 + y_position1 - (int)sqrt(c_K * c_point - c_B);
			line_process--;
		}
	}
}