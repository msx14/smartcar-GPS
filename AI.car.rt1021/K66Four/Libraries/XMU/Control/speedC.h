#ifndef SPEEDC_H
#define SPEEDC_H

#define RIGHT_GO ftm_ch4
#define RIGHT_BACK ftm_ch5
#define LEFT_GO ftm_ch6
#define LEFT_BACK ftm_ch7

void GiveDriveDuty(void);
void SpeedGet(void);
void ExpectSpeedGet();
void LeftPiCalc();
void RightPiCalc();
void SpeedControl();
void CleanTmp(void);
//—”æ‡…≤≥µ
void DelayDistantStop(void);

#endif