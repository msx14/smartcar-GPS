#ifndef _SPECIALELEM_H_
#define _SPECIALELEM_H_

int GetSpeedRow(int middle, int left_row, int right_row);
int ImgIsStopLine(int line, int left, int right);
int DistStopLine(int line);
void ImgJudgeStopLine(void);
//void ImgStopLine(void);
//void ImgJudgeGarage(void);
int ImgJudgeSpecialLine(int left_row, int left_col, int right_row, int right_col, int type);
//void ImgGarage(void);

//老师傅的车库
void garage_io();


#endif