#include "MK60_ftm.h"
#include "encoder.h"

int Encoder_get(void)
{
  int data = 0;
  data = ftm_quad_get(Encoder_FTM);          //��ȡFTM �������� ��������(������ʾ������)
  ftm_quad_clean(Encoder_FTM);                   //�� FTM �������� ��������
  return (data);
}