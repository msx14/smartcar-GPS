
#ifndef SPEEDC_H
#define SPEEDC_H

#define L_FORWARD PWM2_MODULE1_CHA_D4//PWM2_MODULE0_CHA_D6	//����ǰת
#define L_BACKWARD PWM2_MODULE1_CHB_D5//PWM2_MODULE0_CHB_D7	//���ֺ�ת
#define R_FORWARD PWM2_MODULE0_CHB_D7//PWM2_MODULE1_CHB_D5	//����ǰת
#define R_BACKWARD PWM2_MODULE0_CHA_D6//PWM2_MODULE1_CHA_D4	//���ֺ�ת


void GiveDriveDuty(void);
void SpeedGet(void);
void ExpectSpeedGet(void);
void LeftPiCalc(void);
void RightPiCalc(void);
void SpeedControl(void);
void CleanTmp(void);
void DelayDistantStop(void);

#endif