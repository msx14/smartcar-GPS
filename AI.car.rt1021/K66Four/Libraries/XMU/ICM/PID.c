#include "PID.h"

void pidInit(PidObject* pid, const float desired, const pidInit_t pidParam, const float dt)
{
	pid->error     = 0;
	pid->prevError = 0;
	pid->integ     = 0;
	pid->deriv     = 0;
	pid->desired = desired;
	pid->kp = pidParam.kp;
	pid->ki = pidParam.ki;
	pid->kd = pidParam.kd;
	pid->iLimit    = DEFAULT_PID_INTEGRATION_LIMIT;
	pid->iLimitLow = -DEFAULT_PID_INTEGRATION_LIMIT;
	pid->dt        = dt;
}

float pidUpdate(PidObject* pid, const float error)
{
	float output;

	pid->error = error;   

	pid->integ += pid->error * pid->dt;
	if (pid->integ > pid->iLimit)
	{
		pid->integ = pid->iLimit;
	}
	else if (pid->integ < pid->iLimitLow)
	{
		pid->integ = pid->iLimitLow;
	}

	pid->deriv = (pid->error - pid->prevError) / pid->dt;

	pid->outP = pid->kp * pid->error;
	pid->outI = pid->ki * pid->integ;
	pid->outD = pid->kd * pid->deriv;

	output = pid->outP + pid->outI + pid->outD;

	pid->prevError = pid->error;

	return output;
}

void pidSetIntegralLimit(PidObject* pid, const float limit) 
{
    pid->iLimit = limit;
}

void pidSetIntegralLimitLow(PidObject* pid, const float limitLow) 
{
    pid->iLimitLow = limitLow;
}

void pidReset(PidObject* pid)
{
	pid->error     = 0;
	pid->prevError = 0;
	pid->integ     = 0;
	pid->deriv     = 0;
}

void pidSetError(PidObject* pid, const float error)
{
	pid->error = error;
}

void pidSetDesired(PidObject* pid, const float desired)
{
	pid->desired = desired;
}

float pidGetDesired(PidObject* pid)
{
	return pid->desired;
}

bool pidIsActive(PidObject* pid)
{
	bool isActive = true;

	if (pid->kp < 0.0001f && pid->ki < 0.0001f && pid->kd < 0.0001f)
	{
		isActive = false;
	}

	return isActive;
}

void pidSetKp(PidObject* pid, const float kp)
{
	pid->kp = kp;
}

void pidSetKi(PidObject* pid, const float ki)
{
	pid->ki = ki;
}

void pidSetKd(PidObject* pid, const float kd)
{
	pid->kd = kd;
}

void pidSetDt(PidObject* pid, const float dt) 
{
    pid->dt = dt;
}

#define Limit_MAX   1000
static int16 pidOutLimit(float in)
{
  if (in > Limit_MAX)
  {
    return Limit_MAX;
  }
  else if (in < -Limit_MAX)
  {
    return -Limit_MAX;
  }
  else
  {
    return (int16_t)in;
  }
}

//
//����Ϊ����PID�Ĳ��԰汾���õ���Pitch�Ƕȣ�PID����������Ҫ���Բ�֪��
//



PidObject pidAnglePitch;
PidObject pidRatePitch;
pidInit_t AnglePitch = {1,0,0};   //�ǶȻ���ֵ
pidInit_t RatePitch = {1,0,0.01}; //���ٶȻ���ֵ


int attitudeRatePID(float actualRate,float DesiredRate)	/* ���ٶȻ�PID */
{
  return pidOutLimit(pidUpdate(&pidRatePitch, DesiredRate - actualRate));
}

float attitudeAnglePID(float DesiredAngle,float ActualAngle)	/* �ǶȻ�PID */
{
  return pidUpdate(&pidAnglePitch, DesiredAngle - ActualAngle);
}

PidObject pidAnglePitch;

void attitudeControlInit()
{
  pidInit(&pidAnglePitch, 0, AnglePitch, SENSOR9_UPDATE_DT);	                /*pitch �Ƕ�PID��ʼ��*/
  pidSetIntegralLimit(&pidAnglePitch, PID_ANGLE_PITCH_INTEGRATION_LIMIT);	/*pitch �ǶȻ����޷�����*/ 
  
  pidInit(&pidRatePitch, 0, RatePitch, SENSOR9_UPDATE_DT);	                /*pitch ���ٶ�PID��ʼ��*/
  pidSetIntegralLimit(&pidRatePitch, PID_RATE_PITCH_INTEGRATION_LIMIT);	        /*pitch ���ٶȻ����޷�����*/
}

_PID_OUT Pitch;

int AngleCtrl(float SetAngle)
{
  Pitch.AngleOut = attitudeAnglePID(SetAngle,imu_data.pit);
  Pitch.RateOut = attitudeRatePID(sensor.Gyro_deg.y,Pitch.AngleOut);        
  return Pitch.RateOut;
}


