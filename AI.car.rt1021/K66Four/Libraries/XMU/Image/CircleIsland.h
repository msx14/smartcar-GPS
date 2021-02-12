#ifndef CIRCLEISLAND_H_
#define CIRCLEISLAND_H_

void CircleIslandImageInit(void);
void CircleFirstLine(void);
void ChangeState(int Order);
void CircleFindLine(void);
void GetPointA(void);
void GetPointB(void);
void GetPointC(void);
void GetPointD(void);
void FillLineAB(void);
void FillLineCD(void);
void FillAllEage(void);
int FillLineGradient(int* line, int row, int col, float Gradient);
void Connect_Point_Curve(int* line_process, int x_position1, int y_position1, int x_position2, int y_position2);
void CircleFill(void);
int Img_JudgeCircleIsland(int type);
int IsCircleIsland(int type);
void CircleFind(void);
void Img_CircleSlope();

//extern Point PointA, PointB, PointC, PointD;
#endif