#ifndef _PID_H
#define _PID_H

#include "headfile.h"
#include <stdbool.h>

#define DEFAULT_PID_INTEGRATION_LIMIT  		5000.0
#define SENSOR9_UPDATE_DT                       0.002
#define PID_ANGLE_PITCH_INTEGRATION_LIMIT       300.0
#define PID_RATE_PITCH_INTEGRATION_LIMIT	200.0

typedef struct 
{
  float kp;
  float ki;
  float kd;
} pidInit_t;

typedef struct
{
  float AngleOut;
  int RateOut;
}_PID_OUT;

typedef struct
{
  float desired;      //< set point
  float error;        //< error
  float prevError;    //< previous error
  float integ;        //< integral
  float deriv;        //< derivative
  float kp;           //< proportional gain
  float ki;           //< integral gain
  float kd;           //< derivative gain
  float outP;         //< proportional output (debugging)
  float outI;         //< integral output (debugging)
  float outD;         //< derivative output (debugging)
  float iLimit;       //< integral limit
  float iLimitLow;    //< integral limit
  float dt;           //< delta-time dt
} PidObject;

/*pid�ṹ���ʼ��*/
void pidInit(PidObject* pid, const float desired, const pidInit_t pidParam, const float dt);
void pidSetIntegralLimit(PidObject* pid, const float limit);/*pid�����޷�����*/
void pidSetDesired(PidObject* pid, const float desired);	/*pid��������ֵ*/
float pidUpdate(PidObject* pid, const float error);			/*pid����*/
float pidGetDesired(PidObject* pid);	/*pid��ȡ����ֵ*/
bool pidIsActive(PidObject* pid);		/*pid״̬*/
void pidReset(PidObject* pid);			/*pid�ṹ�帴λ*/
void pidSetError(PidObject* pid, const float error);/*pidƫ������*/
void pidSetKp(PidObject* pid, const float kp);		/*pid Kp����*/
void pidSetKi(PidObject* pid, const float ki);		/*pid Ki����*/
void pidSetKd(PidObject* pid, const float kd);		/*pid Kd����*/
void pidSetDt(PidObject* pid, const float dt);		/*pid dt����*/


void attitudeControlInit();
int AngleCtrl(float SetAngle);

#endif
