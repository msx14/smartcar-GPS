
#include "GlobalVar.h"
#include "BasicFind.h"
#include "FindLine.h"
#include "FillSpecialLine.h"
#include "MainProcess.h"
#include "canny.h"
#include "SpecialElem.h"
#include "CircleIsland.h"
//#include "queue.h"
//#include "FirstLineProcess.h"

#define MAXNUM 30
#define IN_SET 5	//向内偏移量
#define OUT_SET 3	//转弯后另一边偏移量


//================================================================//
//  @brief  :		期望速度控制
//  @param  :		middle 车辆中值
//  @return :		void
//  @note   :		void
//================================================================//
int GetSpeedRow(int middle, int left_row, int right_row)
{
	Point P[3] = {
		{DOWN_EAGE, middle - 5},
	{DOWN_EAGE, middle},
	{DOWN_EAGE, middle + 5} };
	int min_row = MIN(left_row, right_row);
	for (int i = DOWN_EAGE; i > UP_EAGE; i--)
	{
		if ((LL[i] - P[0].Col) * (LL[i - 1] - P[0].Col) <= 0
			|| (RL[i] - P[0].Col) * (RL[i - 1] - P[0].Col) <= 0
			|| UP_EAGE + 1 == i)
		{
			P[0].Row = MAX(i, min_row);
			break;
		}
	}
	for (int i = DOWN_EAGE; i > UP_EAGE; i--)
	{
		if ((LL[i] - P[1].Col) * (LL[i - 1] - P[1].Col) <= 0
			|| (RL[i] - P[1].Col) * (RL[i - 1] - P[1].Col) <= 0
			|| UP_EAGE + 1 == i)
		{
			P[1].Row = MAX(i, min_row);
			break;
		}
	}
	for (int i = DOWN_EAGE; i > UP_EAGE; i--)
	{
		if ((LL[i] - P[2].Col) * (LL[i - 1] - P[2].Col) <= 0
			|| (RL[i] - P[2].Col) * (RL[i - 1] - P[2].Col) <= 0
			|| UP_EAGE + 1 == i)
		{
			P[2].Row = MAX(i, min_row);
			break;
		}
	}
	return (P[1].Row + P[0].Row + P[2].Row) / 3;
}
//================================================================//
//  @brief  :		识别停车线
//  @param  :		void
//  @return :		1停车线  0非停车线
//  @note   :		void
//================================================================//
int ImgIsStopLine(int line, int left, int right)
{
	int count = 0;
	for (int i = left + 1; i < right; )
	{
		i = SearchRightEage(line, i);
		i = SearchRightNoEage(line, i);
		count++;
		if (count > 6)//&& RegionAveGray(DOWN_EAGE - 2, LL[DOWN_EAGE - 2], RL[DOWN_EAGE - 2]) 
			//- RegionAveGray(line, left, right) > BrightThreshold) 6
			return 1;
	}
	return 0;
}
//================================================================//
//  @brief  :		识别停车线以及距离
//  @param  :		void
//  @return :		1停车线  0非停车线
//  @note   :		void
//================================================================//
int DistStopLine(int line)
{
	int a = ImgIsStopLine(line, LL[line], RL[line]);
	line += 2;
	int b = ImgIsStopLine(line, LL[line], RL[line]);
	line += 2;
	int c = ImgIsStopLine(line, LL[line], RL[line]);
	if (a || b || c)return 1;
	else return 0;
}
//================================================================//
//  @brief  :		识别停车
//  @param  :		void 
//  @return :		void
//  @note   :		void
//================================================================//
void ImgJudgeStopLine(void)
{
#if STOPLINE
	if (Img_StopOpen && !Img_SpecialElemFlag
		&& LeftIntLine < UP_EAGE + 15 && RightIntLine < UP_EAGE + 15
		&& LeftPnt.ErrRow <= UP_EAGE + 40 && RightPnt.ErrRow <= UP_EAGE + 40	//15
		&& !Img_StopLineFlag && DistStopLine(StopRow) && !Img_GarageFlag)
	{
		Img_StopLineFlag = 1;
		Img_SpecialElemFlag = 1;
		if(CircleFlagSet == 2)
                  Img_GarageFlag = 1;
                else if(CircleFlagSet == 1)
                  Img_GarageFlag = 2;
	}
#endif
}
////================================================================//
////  @brief  :		停车补图
////  @param  :		void 
////  @return :		void
////  @note   :		void
////================================================================//
//void ImgStopLine(void)
//{
//	if (Img_GarageFlag == 1)
//	{
//		//右边补线
//		RL[DOWN_EAGE] = ConstRightEage;
//		RL[DOWN_EAGE - 45] = ConstRightEage - 80;
//		FillLinePoint(RL, DOWN_EAGE, DOWN_EAGE - 45);
//		RightPnt.ErrRow = DOWN_EAGE - 45;
//		RightPnt.ErrCol = ConstRightEage - 80;
//		RightPnt.Type = 0;
//		for (int i = DOWN_EAGE - 46; i >= UP_EAGE; --i)
//			RL[i] = RIGHT_EAGE;
//		//左边补线
//		LL[DOWN_EAGE] = ConstLeftEage;
//		LL[DOWN_EAGE - 45] = ConstLeftEage - 80;
//		FillLinePoint(LL, DOWN_EAGE, DOWN_EAGE - 45);
//		LeftPnt.ErrRow = DOWN_EAGE - 45;
//		LeftPnt.ErrCol = ConstLeftEage - 80;
//		LeftPnt.Type = 0;
//		for (int i = DOWN_EAGE - 46; i >= UP_EAGE; --i)
//			LL[i] = LEFT_EAGE;
//	}
//	if (Img_GarageFlag == 2)
//	{
//		//左边补线
//		LL[DOWN_EAGE] = ConstLeftEage;
//		LL[DOWN_EAGE - 45] = ConstLeftEage + 80;
//		FillLinePoint(LL, DOWN_EAGE, DOWN_EAGE - 45);
//		LeftPnt.ErrRow = DOWN_EAGE - 45;
//		LeftPnt.ErrCol = ConstLeftEage + 80;
//		LeftPnt.Type = 0;
//		for (int i = DOWN_EAGE - 46; i >= UP_EAGE; --i)
//			LL[i] = LEFT_EAGE;
//		//右边补线
//		RL[DOWN_EAGE] = ConstRightEage;
//		RL[DOWN_EAGE - 45] = ConstRightEage + 80;
//		FillLinePoint(RL, DOWN_EAGE, DOWN_EAGE - 45);
//		RightPnt.ErrRow = DOWN_EAGE - 45;
//		RightPnt.ErrCol = ConstRightEage + 80;
//		RightPnt.Type = 0;
//		for (int i = DOWN_EAGE - 46; i >= UP_EAGE; --i)
//			RL[i] = RIGHT_EAGE;
//	}
//}
//================================================================//
//  @brief  :		内跳线判断封闭曲线
//  @param  :		左线行数 右线行数 type 0为直道断路 1位弯道断路
//  @return :		1 确认有
//  @note   :		全局变量LL RL
//================================================================//
int ImgJudgeSpecialLine(int left_row, int left_col, int right_row, int right_col, int type)
{
	const int StartLine = 45;
	if (!type &&
		(left_row < StartLine && right_row < StartLine
			|| left_row - right_row > 8 || right_row - left_row > 8
			|| left_col > MIDDLE || right_col < MIDDLE))
		return 0;
	if (type)
	{
		if (left_col > right_col)
		{
			int tmp = left_col;
			left_col = right_col; right_col = tmp;
			tmp = left_row;
			left_row = right_row; right_row = tmp;
		}
	}
	const int diff = 2;
	int NewRow = left_row;
	int NewRow2 = right_row;
	int OldRow = NewRow;
	int OldRow2 = NewRow2;
	int Middle = (left_col + right_col) >> 1;
	for (int i = left_col + 1; i <= Middle; i++)
	{
		NewRow = SearchUpEage(OldRow + 2, i);
		if (NewRow - OldRow > diff || OldRow - NewRow > diff)
			return 0;
		OldRow = NewRow;
	}
	for (int i = right_col - 1; i >= Middle; i--)
	{
		NewRow2 = SearchUpEage(OldRow2 + 2, i);
		if (NewRow2 - OldRow2 > diff || OldRow2 - NewRow2 > diff)
			return 0;
		OldRow2 = NewRow2;
	}
	if (NewRow == NewRow2)return 1;
	else return 0;
}
////================================================================//
////  @brief  :		识别停车结束
////  @param  :		void 
////  @return :		void
////  @note   :		void
////================================================================//
//void ImgJudgeGarage(void)
//{
//#if STOPEND
//	if (Img_StopLineFlag && Img_GarageFlag)
//	{
//		if (ImgJudgeSpecialLine(LeftPnt.ErrRow, LeftPnt.ErrCol, RightPnt.ErrRow, RightPnt.ErrCol, 1))
//		{
//			Img_GarageFlag = 0;
//			Img_StopLineFlag = 0;
//                        Img_StopFlag = 1;                        
//		}
//	}
//#endif
//}
////================================================================//
////  @brief  :		车库内补图
////  @param  :		void 
////  @return :		void
////  @note   :		void
////================================================================//
//void ImgGarage(void)
//{
//	if (Img_StopFlag)
//	{
//                static int motorsave = 0;
//                motorsave += curSpeed;
//		int ltype = -1,rtype = -1;
//		ltype = JudgeCurveEage(DOWN_EAGE, LeftPnt.ErrRow, 1);
//		rtype = JudgeCurveEage(DOWN_EAGE, RightPnt.ErrRow, 2);
//		//str.Format("\r\n type = %d,%d \r\n", ltype, rtype); PrintDebug(str);
//		if (ltype && !rtype)
//		{
//			int row = DOWN_EAGE;
//			for (int i = row; i >= LeftPnt.ErrRow; i = i - 5)
//			{
//				ltype = JudgeCurveEage(DOWN_EAGE, i, 1);
//				if (1 == ltype)
//				{
//					row = i + 5;
//					break;
//				}
//			}
//			for (int i = row - 1; i >= LeftPnt.ErrRow; --i)
//				LL[i] = LEFT_EAGE;
//			LeftPnt.ErrRow = row;
//			LeftPnt.ErrCol = LL[row];
//			LeftPnt.Type = 0;
//			RightPnt.Type = 0;
////			if (LeftPnt.ErrRow >= 50 && RightPnt.ErrRow >= 30)
////			{
////				Img_StopFlag = 0;
////                                
////			}
//                        if(motorsave >= StopDis)
//                        {
//                            Img_StopFlag = 0;
//                            speed_type = 0;
//                            motorsave = 0;
//                            Img_SpecialElemFlag = 0;
//                        }
//		}
//		else if (rtype && !ltype)
//		{
//			int row = DOWN_EAGE;
//			for (int i = row; i >= RightPnt.ErrRow; i = i - 5)
//			{
//				rtype = JudgeCurveEage(DOWN_EAGE, i, 2);
//				if (1 == rtype)
//				{
//					row = i + 5;
//					break;
//				}
//			}
//			for (int i = row - 1; i >= RightPnt.ErrRow; --i)
//				RL[i] = RIGHT_EAGE;
//			RightPnt.ErrRow = row;
//			RightPnt.ErrCol = RL[row];
//			RightPnt.Type = 0;
//			LeftPnt.Type = 0;
////			if (RightPnt.ErrRow >= 50 && LeftPnt.ErrRow >= 30)
////			{
////				Img_StopFlag = 0;
////			}
//                        if(motorsave >= StopDis)
//                        {
//                            Img_StopFlag = 0;
//                            speed_type = 0;
//                            motorsave = 0;
//                            Img_SpecialElemFlag = 0;
//                        }
//		}
//	}
//}

//老师傅的车库
//void garage_io()
//{
//	int i, j, t, n;
//        t = 9;
//        n = 0;
//	int jump[10] = {0};
//        if(Img_RampFlag == 0)// && Img_StopLineFlag == 0)
//        {
//                for (j = Stop_UpRow + 1; j < Stop_UpRow + 11; ++j)
//		{
//			for (i = LEFT_EAGE + 2; i <= RIGHT_EAGE - 2; ++i)
//			{
////                              if(ImageEage[j][i] == 1)
////                              {
////                                    jump[t]++;
////                              }
//				if (abs(image[j][i] - image[j - 1][i + 1]) + abs(image[j][i + 1] - image[j - 1][i]) >= HighThreshold)
//				{
//					if (abs(image[j][i - 1] - image[j - 1][i]) + abs(image[j][i] - image[j - 1][i - 1]) < HighThreshold)
//					{
//						jump[t]++;
//					}
//				}
//			}
//			if (jump[t] > StopLineThreshold)
//			{
//                              n++;
//                              if(j > StopMaxRow)
//                              {
//                                    StopMaxRow = j;
//                              }
//			}
////                        else
////                              break;
//                        t--;
//		}
//        }
//	if (!Img_StopLineFlag && StopMaxRow > StopRow && n > 2)
//	{
//              Img_StopLineFlag = 1;
//              Img_SpecialElemFlag = 1;
//              if(CircleFlagSet == 2)
//                Img_GarageFlag = 1;
//              else if(CircleFlagSet == 1)
//                Img_GarageFlag = 2;
//	}
//}


//void garage_io()
//{
//        if(g_garage_open == 1)
//        {
//                int i, j;
//                int jump[70] = {0};
//                for(j = UP_EAGE + 15; j < UP_EAGE + 25; j++)
//		{
//			for (i = LEFT_EAGE + 2; i <= RIGHT_EAGE - 2; i++)
//			{
//				if (abs(image[j][i] - image[j - 1][i + 1]) + abs(image[j][i + 1] - image[j - 1][i]) >= HighThreshold)
//				{
//					if (abs(image[j][i - 1] - image[j - 1][i]) + abs(image[j][i] - image[j - 1][i - 1]) < HighThreshold)
//					{
//						jump[j]++;
//					}
//				}
//			}
//                        if(StopMaxRow < j)
//                        {
//                                if (jump[j] > StopLineThreshold)
//                                {
//                                            StopMaxRow = j;
//                                }
//                        }
//		}
//        }
//	if (!Img_StopLineFlag && StopMaxRow != 0)
//	{
//              Img_StopLineFlag = 1;
//              if(CircleFlagSet == 2)
//                Img_GarageFlag = 1;
//              else if(CircleFlagSet == 1)
//                Img_GarageFlag = 2;
//	}
//	if(Img_StopLineFlag)
//        {
//                for(j = UP_EAGE + 25; j < DOWN_EAGE - 2; j++)
//		{
//			for (i = LEFT_EAGE + 2; i <= RIGHT_EAGE - 2; i++)
//			{
//				if (abs(image[j][i] - image[j - 1][i + 1]) + abs(image[j][i + 1] - image[j - 1][i]) >= HighThreshold)
//				{
//					if (abs(image[j][i - 1] - image[j - 1][i]) + abs(image[j][i] - image[j - 1][i - 1]) < HighThreshold)
//					{
//						jump[j]++;
//					}
//				}
//			}
//			if (jump[j] > StopLineThreshold)
//			{
//                                if(StopMaxRow < j)
//                                    StopMaxRow = j;
////                                if(StopMinRow > j)
////                                    StopMinRow = j;
//			}
//		}
////                if(StopMinRow >= DOWN_EAGE - 8)
////                        StopMinRow = 0;
//        }
//}

void garage_io()
{
        if(g_garage_open == 1)
        {
                int i, j;
                int jump[70] = {0};
                for (j = UP_EAGE + 1; j < DOWN_EAGE - 5; j++)
		{
			for (i = LEFT_EAGE + 2; i <= RIGHT_EAGE - 2; i++)
			{
				if (abs(image[j][i] - image[j - 1][i + 1]) + abs(image[j][i + 1] - image[j - 1][i]) >= HighThreshold)
				{
					if (abs(image[j][i - 1] - image[j - 1][i]) + abs(image[j][i] - image[j - 1][i - 1]) < HighThreshold)
					{
						jump[j]++;
					}
				}
			}
			//str.Format("jump[%d]:%d\n\r", j, jump[j]); PrintDebug(//str);
		}
		for (j = UP_EAGE + 1; j < DOWN_EAGE - 5; j++)
		{
                    if (jump[j] > StopLineThreshold)
                    {
                            StopMinRow = j;
                            break;
                    }
		}
                if(j >= DOWN_EAGE - 8)
                {
                    StopMinRow = 0;
                }
		for (j = UP_EAGE + 1; j < DOWN_EAGE - 5; j++)
		{
			if (jump[j] > StopLineThreshold)
			{
                                if(StopMaxRow < j)
                                  StopMaxRow = j;
			}
		}
        }
	if (!Img_StopLineFlag && StopMaxRow >= StopRow)
	{
              Img_StopLineFlag = 1;
              if(CircleFlagSet == 2)
                Img_GarageFlag = 1;
              else if(CircleFlagSet == 1)
                Img_GarageFlag = 2;
        }
}


