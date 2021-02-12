#include "XMU_IMU.h"

_imu_st imu_data =  {1,0,0,0,
                      {0,0,0},
                      {0,0,0},
                      {0,0,0},
                      {0,0,0},
                      {0,0,0},
                      {0,0,0},
                       0,0,0,
                       0,0,0,
                       0,0,0,
                       0};

void IMU_update(float dT,_xyz_f_st *gyr, _xyz_f_st *acc,_imu_st *imu)
{
  static _lf_t err_lf_x;
  static _lf_t err_lf_y;
  static _lf_t err_lf_z;
  static _xyz_f_st vec_err_i;
  
  float kp = 0.6,ki = 0;
  
  float q0q1,q0q2,q1q1,q1q3,q2q2,q2q3,q3q3,q1q2,q0q3;//q0q0,
  float w_q,x_q,y_q,z_q;
  float acc_length,q_length;
  _xyz_f_st acc_norm;
  _xyz_f_st vec_err;
  _xyz_f_st d_angle;
	  
  w_q = imu->w;
  x_q = imu->x;
  y_q = imu->y;
  z_q = imu->z;
						
  q0q1 = w_q * x_q;
  q0q2 = w_q * y_q;
  q1q1 = x_q * x_q;
  q1q3 = x_q * z_q;
  q2q2 = y_q * y_q;
  q2q3 = y_q * z_q;
  q3q3 = z_q * z_q;
  q1q2 = x_q * y_q;
  q0q3 = w_q * z_q;
		
  // ���ٶȼƵĶ�������λ����
  acc_length = my_sqrt(my_pow(acc->x) + my_pow(acc->y) + my_pow(acc->z));
  acc_norm.x = acc->x / acc_length;
  acc_norm.y = acc->y / acc_length;
  acc_norm.z = acc->z / acc_length;
              
              // ���������µ�x������������λ����
  imu->x_vec.x = 1 - (2*q2q2 + 2*q3q3);
  imu->x_vec.y = 2*q1q2 - 2*q0q3;
  imu->x_vec.z = 2*q1q3 + 2*q0q2;
              
              // ���������µ�y������������λ����
  imu->y_vec.x = 2*q1q2 + 2*q0q3;
  imu->y_vec.y = 1 - (2*q1q1 + 2*q3q3);
  imu->y_vec.z = 2*q2q3 - 2*q0q1;
              
  // ���������µ�z������������Ч�����������������ٶ�����������λ����
  imu->z_vec.x = 2*q1q3 - 2*q0q2;
  imu->z_vec.y = 2*q2q3 + 2*q0q1;
  imu->z_vec.z = 1 - (2*q1q1 + 2*q2q2);
		
  // �������������µ��˶����ٶȡ�(����̬�����޹�)
//  imu->a_acc.x = acc->x - 9800 *imu->z_vec.x;
//  imu->a_acc.y = acc->y - 9800 *imu->z_vec.y;
//  imu->a_acc.z = acc->z - 9800 *imu->z_vec.z;
  
  // �������������µ��˶����ٶȡ�(����̬�����޹�)
//  imu->w_acc.z = imu->z_vec.x *imu->a_acc.x + imu->z_vec.y *imu->a_acc.y + imu->z_vec.z *imu->a_acc.z;
	
  // ����ֵ���Ч���������Ĳ��������������
  vec_err.x =  (acc_norm.y * imu->z_vec.z - imu->z_vec.y * acc_norm.z);
  vec_err.y = -(acc_norm.x * imu->z_vec.z - imu->z_vec.x * acc_norm.z);
  vec_err.z = 0;// -(acc_norm.y * imu->z_vec.x - imu->z_vec.y * acc_norm.x);
		
  //��ֹƵ��1hz�ĵ�ͨ�޷��˲�
  limit_filter(dT,0.2f,&err_lf_x,vec_err.x);
  limit_filter(dT,0.2f,&err_lf_y,vec_err.y);
  limit_filter(dT,0.2f,&err_lf_z,vec_err.z);
  
  //������
  vec_err_i.x += err_lf_x.out *dT *ki;
  vec_err_i.y += err_lf_y.out *dT *ki;
  vec_err_i.z += err_lf_z.out *dT *ki;
		
  // ����������ת�����ںϾ�������
  d_angle.x = (gyr->x *RAD_PER_DEG + (err_lf_x.out + vec_err_i.x) * kp) * dT / 2 ;
  d_angle.y = (gyr->y *RAD_PER_DEG + (err_lf_y.out + vec_err_i.y) * kp) * dT / 2 ;
  d_angle.z = (gyr->z *RAD_PER_DEG + (err_lf_z.out + vec_err_i.z) * kp) * dT / 2 ;
    
  // ������̬��
  imu->w = w_q           - x_q*d_angle.x - y_q*d_angle.y - z_q*d_angle.z;
  imu->x = w_q*d_angle.x + x_q           + y_q*d_angle.z - z_q*d_angle.y;
  imu->y = w_q*d_angle.y - x_q*d_angle.z + y_q           + z_q*d_angle.x;
  imu->z = w_q*d_angle.z + x_q*d_angle.y - y_q*d_angle.x + z_q;
		
  q_length = my_sqrt(imu->w*imu->w + imu->x*imu->x + imu->y*imu->y + imu->z*imu->z);
  imu->w /= q_length;
  imu->x /= q_length;
  imu->y /= q_length;
  imu->z /= q_length;
	
  imu->pit = asin(2*q1q3 - 2*q0q2)*57.30f;
  imu->rol = fast_atan2(2*q2q3 + 2*q0q1, -2*q1q1-2*q2q2 + 1)*57.30f; 
  imu->yaw = -fast_atan2(2*q1q2 + 2*q0q3, -2*q2q2-2*q3q3 + 1)*57.30f; 
}


Butter_BufferData Butter_Buffer_W_acc;

void My_IMU_update(float dT)
{
  IMU_update(dT,&(sensor.Gyro_deg), &(sensor.Acc_mmss),&imu_data);
}

