
#ifndef SPEEDC_H
#define SPEEDC_H

#define L_FORWARD PWM2_MODULE1_CHA_D4//PWM2_MODULE0_CHA_D6	//左轮前转
#define L_BACKWARD PWM2_MODULE1_CHB_D5//PWM2_MODULE0_CHB_D7	//左轮后转
#define R_FORWARD PWM2_MODULE0_CHB_D7//PWM2_MODULE1_CHB_D5	//右轮前转
#define R_BACKWARD PWM2_MODULE0_CHA_D6//PWM2_MODULE1_CHA_D4	//右轮后转


void GiveDriveDuty(void);
void SpeedGet(void);
void ExpectSpeedGet(void);
void LeftPiCalc(void);
void RightPiCalc(void);
void SpeedControl(void);
void CleanTmp(void);
void DelayDistantStop(void);

#endif