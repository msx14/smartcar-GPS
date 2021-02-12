#include "GlobalVar.h"
#include "BasicFind.h"
#include "canny.h"

////�����޶�:0~IMG_COLS - 1
//int valuelimit(int m)
//{
//	if (m < LEFT_EAGE)m = LEFT_EAGE + 1;
//	else if (m > RIGHT_EAGE)m = RIGHT_EAGE;
//	return m;
//}
//================================================================//
//  @brief  :		�ж��Ƿ�Ϊ��Ե
//  @param  :		void
//  @return :		1�� 0����
//  @note   :		void
//================================================================//
int IsEage(int row, int col)
{
	//�޷�
	if (row > DOWN_EAGE) row = DOWN_EAGE;
	if (row < UP_EAGE) row = UP_EAGE;
	if (col <= LEFT_EAGE) col = LEFT_EAGE + 1;
	if (col > RIGHT_EAGE) col = RIGHT_EAGE;
	if (FindLineType)
	{
		unsigned char* p = image[0] + IMG_COL * (row - 1) + col - 1;
		unsigned char ack = 0;
		ack += *p++ < LightThreshold;
		ack += *p++ < LightThreshold;
		p += (IMG_COL - 2);
		ack += *p++ < LightThreshold;
		ack += *p++ < LightThreshold;
		if (!ack) return 0;
	}
	if (HIGH_TH == ImageEage[row][col])
		return 1;
	else return 0;
}
//================================================================//
//  @brief  :		��������һ���߽��
//  @param  :		void
//  @return :		�߽��������
//  @note   :		void
//================================================================//
int SearchLeftEage(int row, int col)
{
	for (; col > LEFT_EAGE; --col)
	{
		if (IsEage(row, col))
			return col;
	}
	return LEFT_EAGE;
}

//================================================================//
//  @brief  :		��������һ���߽��
//  @param  :		void
//  @return :		�߽��������
//  @note   :		void
//================================================================//
int SearchRightEage(int row, int col)
{
	for (; col < RIGHT_EAGE; ++col)
	{
		if (IsEage(row, col))
			return col;
	}
	return RIGHT_EAGE;
}

//================================================================//
//  @brief  :		��������һ���߽��
//  @param  :		void
//  @return :		�߽��������
//  @note   :		void
//================================================================//
int SearchUpEage(int row, int col)
{
	for (; row > UP_EAGE; --row)
	{
		if (IsEage(row, col))
			return row;
	}
	return UP_EAGE;
}

//================================================================//
//  @brief  :		��������һ���߽��
//  @param  :		void
//  @return :		�߽��������
//  @note   :		void
//================================================================//
int SearchDownEage(int row, int col)
{
	for (; row < DOWN_EAGE; ++row)
	{
		if (IsEage(row, col))
			return row;
	}
	return DOWN_EAGE;
}
//================================================================//
//  @brief  :		��������һ���Ǳ߽��
//  @param  :		void
//  @return :		�߽��������
//  @note   :		void
//================================================================//
int SearchLeftNoEage(int row, int col)
{
	for (; col > LEFT_EAGE; --col)
	{
		if (!IsEage(row, col))
			return col;
	}
	return LEFT_EAGE;
}

//================================================================//
//  @brief  :		��������һ���Ǳ߽��
//  @param  :		void
//  @return :		�߽��������
//  @note   :		void
//================================================================//
int SearchRightNoEage(int row, int col)
{
	for (; col < RIGHT_EAGE; ++col)
	{
		if (!IsEage(row, col))
			return col;
	}
	return RIGHT_EAGE;
}


//================================================================//
//  @brief  :		����������һ���߽��
//  @param  :		void
//  @return :		�߽��������
//  @note   :		void
//================================================================//
Point SearchLeftUpEage(int row, int col)
{
	int i = row, j = col;
	unsigned char k = 0;
	Point Up45;
	while (i > UP_EAGE && j > LEFT_EAGE)
	{
		if (IsEage(i, j))
		{
			Up45.Row = i;
			Up45.Col = j;
			return Up45;
		}
		if (0 == k)
		{
			k = 1;
			--i;
		}
		else
			k = 0;
		--j;
	}
	Up45.Row = i;
	Up45.Col = j;
	return Up45;
}

//================================================================//
//  @brief  :		����������һ���߽��45
//  @param  :		void
//  @return :		�߽��������
//  @note   :		void
//================================================================//
Point SearchLeftUpEage45(int row, int col)
{
	int i = row, j = col;
	unsigned char k = 0;
	Point Up45;
	while (i > UP_EAGE && j > LEFT_EAGE)
	{
		if (IsEage(i, j))
		{
			Up45.Row = i;
			Up45.Col = j;
			return Up45;
		}
		--i;
		--j;
	}
	Up45.Row = i;
	Up45.Col = j;
	return Up45;
}

//================================================================//
//  @brief  :		����������һ���߽��
//  @param  :		void
//  @return :		�߽��������
//  @note   :		void
//================================================================//
Point SearchRightUpEage(int row, int col)
{
	int i = row, j = col;
	unsigned char k = 0;
	Point Up45;
	while (i > UP_EAGE && j < RIGHT_EAGE)
	{
		if (IsEage(i, j))
		{
			Up45.Row = i;
			Up45.Col = j;
			return Up45;
		}
		if (0 == k)
		{
			k = 1;
			--i;
		}
		else k = 0;
		++j;
	}
	Up45.Row = i;
	Up45.Col = j;
	return Up45;
}

//================================================================//
//  @brief  :		����������һ���߽��45
//  @param  :		void
//  @return :		�߽��������
//  @note   :		void
//================================================================//
Point SearchRightUpEage45(int row, int col)
{
	int i = row, j = col;
	unsigned char k = 0;
	Point Up45;
	while (i > UP_EAGE && j < RIGHT_EAGE)
	{
		if (IsEage(i, j))
		{
			Up45.Row = i;
			Up45.Col = j;
			return Up45;
		}
		--i;
		++j;
	}
	Up45.Row = i;
	Up45.Col = j;
	return Up45;
}

//================================================================//
//  @brief  :		����������һ���߽��
//  @param  :		void
//  @return :		�߽��������
//  @note   :		void
//================================================================//
Point SearchLeftDownEage(int row, int col)
{
	int i = row, j = col;
	Point Up45;
	while (i < DOWN_EAGE && j > LEFT_EAGE)
	{
		if (IsEage(i, j))
		{
			Up45.Row = i;
			Up45.Col = j;
			return Up45;
		}
		++i; --j;
	}
	Up45.Row = i;
	Up45.Col = j;
	return Up45;
}

//================================================================//
//  @brief  :		����������һ���߽��
//  @param  :		void
//  @return :		�߽��������
//  @note   :		void
//================================================================//
Point SearchRightDownEage(int row, int col)
{
	int i = row, j = col;
	Point Up45;
	while (i < DOWN_EAGE && j < RIGHT_EAGE)
	{
		if (IsEage(i, j))
		{
			Up45.Row = i;
			Up45.Col = j;
			return Up45;
		}
		++i; ++j;
	}
	Up45.Row = i;
	Up45.Col = j;
	return Up45;
}
//================================================================//
//  @brief  :		�������
//  @param  :		void
//  @return :		�߽��������
//  @note   :		void
//================================================================//
int GetLL(int row, int col)
{
	int TmpCol;
	if (row == DOWN_EAGE - 1)
		col += 8;
	else
		col += IN_OFFSET;
	if (col > RIGHT_EAGE) col = RIGHT_EAGE;
	if (!IsEage(row, col))
		TmpCol = SearchLeftEage(row, col);
	else
		TmpCol = SearchRightNoEage(row, col) - 1;
	return TmpCol;
}

//================================================================//
//  @brief  :		���ұ���
//  @param  :		void
//  @return :		�߽��������
//  @note   :		void
//================================================================//
int GetRL(int row, int col)
{
	int TmpCol;
	if (row == DOWN_EAGE - 1)
		col -= 8;
	else
		col -= IN_OFFSET;
	if (col <= LEFT_EAGE) col = LEFT_EAGE + 1;
	if (!IsEage(row, col))
		TmpCol = SearchRightEage(row, col);
	else
		TmpCol = SearchLeftNoEage(row, col) + 1;
	return TmpCol;
}
//================================================================//
//  @brief  :		��С���˷�
//  @param  :		��ʼ�У�row1�� �����У�row2�� �׵�ַ��array��
//  @return :		kб��
//  @note   :		void
//================================================================//
float LeastSquare(int* array, int row1, int row2)
{
	float sum_x2 = 0.0;
	float sum_y = 0.0;
	float sum_x = 0.0;
	float sum_xy = 0.0;
	float  c;

	for (int i = row1; i >= row2; --i)
	{
		sum_x2 += i * i;
		sum_y += *(array + i);
		sum_x += i;
		sum_xy += i * *(array + i);
	}

	c = (row1 - row2 + 1) * sum_x2 - sum_x * sum_x;
	if (0 == c)
		return 0;
	else
		return ((row1 - row2 + 1) * sum_xy - sum_x * sum_y) / c;
}

//================================================================//
//  @brief  :		�ж���ֱ
//  @param  :		type : 1�ж�LL��2�ж�RL
//  @return :		return : 1Ϊ���ߣ�0Ϊֱ��
//  @note   :		void
//================================================================//
int JudgeCurveEage(int up_row, int down_row, int type)
{
	if (type == 1)
	{
		if ((LL[up_row] + LL[down_row]) / 2 - LL[(up_row + down_row) / 2] < 10
			&& LL[(up_row + down_row) / 2] - (LL[up_row] + LL[down_row]) / 2 < 10)
			return 0;
		else
			return 1;
	}
	else if (type == 2)
		if ((RL[up_row] + RL[down_row]) / 2 - RL[(up_row + down_row) / 2] < 10
			&& RL[(up_row + down_row) / 2] - (RL[up_row] + RL[down_row]) / 2 < 10)
			return 0;
		else
			return 1;
}

//================================================================//
//  @brief  :		����Ҷ�ƽ��ֵ
//  @param  :		�����׵�ַArray n����
//  @return :		��ֵ
//  @note   :		void
//================================================================//
int AveGray(void)
{
	unsigned char* p = image[UP_EAGE];
	long int sum = 0;
	for (int i = 0; i < 188 * 51; i++)
	{
		sum += *p++;
	}
	return sum / 188 / 51;

}

//================================================================//
//  @brief  :		���������ڻҶ�ƽ��ֵ
//  @param  :		�����׵�ַArray n����
//  @return :		��ֵ
//  @note   :		void
//================================================================//
int RegionAveGray(int row, int left_col, int right_col)
{
	long int sum = 0;
	int width = right_col - left_col;
	for (int j = left_col; j < right_col; j++)
	{
		sum += image[row][j];
	}
	return sum / width;
}

//================================================================//
//  @brief  :		��������ֵ
//  @param  :		�����׵�ַArray n����
//  @return :		��ֵ
//  @note   :		void
//================================================================//
int MaxArray(int* line, int n)
{
	int max = 0;
	for (int i = 0; i < n; i++)
	{
		if (*line > max) max = *line;
		line--;
	}
	return max;
}
int MinArray(int* line, int n)
{
	int min = 0;
	for (int i = 0; i < n; i++)
	{
		if (*line < min) min = *line;
		line--;
	}
	return min;
}

//================================================================//
//  @brief  :		����������
//  @param  :		�����׵�ַArray n����
//  @return :		���� -1���� 1���� 0�޳���
//  @note   :		void
//================================================================//
signed int TrendArray(int* line, int n)
{
	int LeftNum = 0, RightNum = 0;
	for (int i = 0; i < n - 1; i++)
	{
		if (*line > * (line - 1))LeftNum++;
		else if (*line < *(line - 1))RightNum++;
		else;
		line--;
	}
	if (LeftNum > RightNum)return -1;
	else if (LeftNum < RightNum)return 1;
	else return 0;
}

//================================================================//
//  @brief  :		��ֵ�˲�
//  @param  :		�����׵�ַArray n����
//  @return :		void
//  @note   :		void
//================================================================//
void AveFilter(int* line, int n)
{
	const int filter_threshold = 7;	//�˲���ֵ
	line--; n -= 2;
	while (n-- > 0)
	{
		if ((*line - *(line + 1) > filter_threshold || *(line + 1) - *line > filter_threshold)
			&& (*line - *(line - 1) > filter_threshold || *(line - 1) - *line > filter_threshold))
			* line = (*(line - 1) + *(line + 1)) >> 1;
		line--;
	}
}

//================================================================//
//  @brief  :		�Ƿ���ڴ󲨶�
//  @param  :		�����׵�ַArray n����
//  @return :		void
//  @note   :		void
//================================================================//
int IsBigWave(int* line, int n)
{
	AveFilter(line, n);		//�˲�
	//for (int i = 0; i < n; i++)
	//{
	//	string.Format("\r\n LL = %d \r\n", *(line-i)); PrintDebug(string);
	//}
	int* line_init = line;
	while (--n > 0)
	{
		if (*line - *(line - 1) > FINDLINE_TH || *(line - 1) - *line > FINDLINE_TH)
			return line_init - line + 1;
		line--;
	}
	return 0;
}

//================================================================//
//  @brief  :		������б��,0-LL, 1-RL
//  @param  :		�����׵�ַArray n����,row1 < row2
//  @return :		б�� -1û�ѵ��� 
//  @note   :		float
//================================================================//
float g_slope(int* array, int row1, int row2)
{
	float slope = 0;
	int lost_count = 0;
	for (int i = row1; i <= row2; ++i)
	{
		if (*(array + i) == LEFT_EAGE || *(array + i) == RIGHT_EAGE)
		{
			lost_count++;
		}
	}
	//str.Format("\r\n lost_count: %d,row2:%d,row1:%d\r\n", lost_count,row2,row1); PrintDebug(str);
	if (lost_count >= abs(row2 - row1) / 3)
	{
		return 100;
	}
	slope = (*(array + row1) - *(array + row2));
	if (slope == 0)
		slope = 1;
	else
		;
	slope = (row2 - row1) / slope;
	return slope;
}

//================================================================//
//  @brief  :		������б��,0-LL, 1-RL
//  @param  :		�����׵�ַArray n����,row1 < row2
//  @return :		б�� -1û�ѵ��� 
//  @note   :		float
//================================================================//
float circle_slope(int* array, int row1, int row2,int flag)
{
	float slope = 0;
	int point = 3;
	int minrow1 = RIGHT_EAGE;
	int minrow2 = RIGHT_EAGE;
	int maxrow1 = LEFT_EAGE;
	int maxrow2 = LEFT_EAGE;
	int lost_count = 0;
	for (int i = row1; i <= row2; ++i)
	{
		if (*(array + i) <= LEFT_EAGE + 1|| *(array + i) >= RIGHT_EAGE - 1)
		{
			lost_count++;
		}
	}
	//str.Format("\r\n lost_count: %d,row2:%d,row1:%d\r\n", lost_count,row2,row1); PrintDebug(str);
	if (lost_count >= abs(row2 - row1) / 3)
	{
		return -1;
	}
	if ((row2 - row1) < 2 * point - 1)
	{
		point = (row2 - row1 + 1) / 2;
	}
	for (int i = 0; i < point; i++)
	{
		if (*(array + row1 + i) >= maxrow1 && *(array + row1 + i) != RIGHT_EAGE)
			maxrow1 = *(array + row1 + i);
		if (*(array + row1 + i) <= minrow1 && *(array + row1 + i) != LEFT_EAGE)
			minrow1 = *(array + row1 + i);
		if (*(array + row2 - i) >= maxrow2 && *(array + row2 - i) != RIGHT_EAGE)
			maxrow2 = *(array + row2 - i);
		if (*(array + row2 - i) <= minrow2 && *(array + row2 - i) != LEFT_EAGE)
			minrow2 = *(array + row2 - i);
	}
	if (flag == 0)
		if (minrow1 > maxrow2)
			;
		else
		{
			//str.Format("\r\n 2 = %d,%d,%d \r\n", minrow1, maxrow2, flag); PrintDebug(str);
			return -1;
		}
	else
		if (maxrow1 < minrow2)
			;
		else
		{
			//str.Format("\r\n 3 = %d,%d,%d \r\n", maxrow1, minrow2, flag); PrintDebug(str);
			return -1;
		}
	for (int i = 0; i < point; i++)
	{
		slope += (*(array + row1 + i) - *(array + row2 - i));
	}
	if (slope == 0)
		slope = 100;
	else
		slope = (point * (row2 - row1 - point + 1)) / slope;
	return slope;
}
