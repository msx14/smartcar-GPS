#include  "ADCollection.h"
#include "headfile.h"
#include "GlobalVar.h"

uint8 send_buff[20];        //无线转串口发送数组 

float adc_max_work(float adc_max,float adc_now) //fetch the max of adc
{
      if(adc_max<=adc_now)
       adc_max=adc_now;
    return adc_max;
}
float adc_min_work(float adc_min,float adc_now) //fetch the min of adc
{
     if(adc_min>=adc_now)
       adc_min=adc_now;
     return adc_min;
}
	
int data_limitation(float data_input)
{
	int data_temp;
	if(data_input>=1)
		data_input=1;
	data_temp=(int32)(255.0*data_input-128);
	return data_temp;
}
void train_ad_collection(void)
{
 	/*以下为短前瞻的五个电感*/
  	LO_L = adc_mean_filter(ADC_1,LO_L_com ,10);/*左OUT训练均值滤波*/
    LI_L = adc_mean_filter(ADC_1,LI_L_com ,10);/*左IN训练均值滤波*/
    M_L = adc_mean_filter(ADC_2,M_L_com,10);/*中 - 训练均值滤波*/    
		RI_L = adc_mean_filter(ADC_1,RI_L_com ,10);/*右IN训练均值滤波*/
    RO_L = adc_mean_filter(ADC_1,RO_L_com ,10);/*右OUT训练均值滤波*/
  /*以下为腹部的两个电感*/  
		belly_R_L = adc_mean_filter(ADC_1,belly_R_L_com,10);/*腹部右均值滤波*/
    belly_L_L = adc_mean_filter(ADC_2,belly_L_L_com,10);/*腹部右均值滤波*/   
  /*以下为长前瞻的3个电感*/   
  outL_L=adc_mean_filter(ADC_1, outL_L_com,10); /*左均值滤波*/ 
  outM_L=adc_mean_filter(ADC_1, outM_L_com,10); /*中均值滤波*/
  outR_L=adc_mean_filter(ADC_1, outR_L_com,10); /*右均值滤波*/
  
  if(adc_read%2==1&&gpio_get(D14)==1&&adc_read!=0)  
  { 
    ad1_m=adc_mean_filter(ADC_1, LO_L_com,10);
    ad2_m=adc_mean_filter(ADC_1, LI_L_com,10);
    ad3_m=adc_mean_filter(ADC_2, M_L_com,10);
    ad4_m=adc_mean_filter(ADC_1, RI_L_com,10);
    ad5_m=adc_mean_filter(ADC_1, RO_L_com,10);
    LO_Lmax=adc_max_work(LO_Lmax,ad1_m);                                           LO_Lmin=adc_min_work(LO_Lmin,ad1_m);
    LI_Lmax=adc_max_work(LI_Lmax,ad2_m);                                           LI_Lmin=adc_min_work(LI_Lmin,ad2_m);  
		M_Lmax=adc_max_work(M_Lmax,ad3_m);                                               M_Lmin=adc_min_work(M_Lmin,ad3_m);   
		RI_Lmax=adc_max_work(RI_Lmax,ad4_m);                                           RI_Lmin=adc_min_work(RI_Lmin,ad4_m);
    RO_Lmax=adc_max_work(RO_Lmax,ad5_m);                                           RO_Lmin=adc_min_work(RO_Lmin,ad5_m);
 
    ad6_m=adc_mean_filter(ADC_1, belly_R_L_com,10);
    ad7_m=adc_mean_filter(ADC_2, belly_L_L_com,10);
    belly_R_Lmax=adc_max_work(belly_R_Lmax,ad6_m);                                   belly_R_Lmin=adc_min_work(belly_R_Lmin,ad6_m);
    belly_L_Lmax=adc_max_work(belly_L_Lmax,ad7_m);                                   belly_L_Lmin=adc_min_work(belly_L_Lmin,ad7_m);
   
    ad8_m=adc_mean_filter(ADC_1, outL_L_com,10);
    ad9_m=adc_mean_filter(ADC_1,outR_L_com,10);
    ad10_m=adc_mean_filter(ADC_1, outM_L_com,10);
    outL_Lmax=adc_max_work(outL_Lmax,ad8_m);                                    outL_Lmin=adc_min_work(outL_Lmin,ad8_m);
    outR_Lmax=adc_max_work(outR_Lmax,ad9_m);                                    outR_Lmin=adc_min_work(outR_Lmin,ad9_m);
    outM_Lmax=adc_max_work(outM_Lmax,ad10_m);                                   outM_Lmin=adc_min_work(outM_Lmin,ad10_m);
    }   
  else if(adc_read%2==0&&gpio_get(D14)==1&&adc_read!=0)
  {
    LO_L_r1=(LO_L-LO_Lmin)/(LO_Lmax-LO_Lmin);
    LI_L_r1=(LI_L-LI_Lmin)/(LI_Lmax-LI_Lmin);
    RI_L_r1=(RI_L-RI_Lmin)/(RI_Lmax-RI_Lmin);
    RO_L_r1=(RO_L-RO_Lmin)/(RO_Lmax-RO_Lmin);
    M_L_r1=(M_L-M_Lmin)/(M_Lmax-M_Lmin);
    
    belly_R_L_r1=(belly_R_L-belly_R_Lmin)/(belly_R_Lmax-belly_R_Lmin);
    belly_L_L_r1=(belly_L_L-belly_L_Lmin)/(belly_L_Lmax-belly_L_Lmin);
		
    outL_L_r1=(outL_L-outL_Lmin)/(outL_Lmax-outL_Lmin);
    outR_L_r1=(outR_L-outR_Lmin)/(outR_Lmax-outR_Lmin);
    outM_L_r1=(outM_L-outM_Lmin)/(outM_Lmax-outM_Lmin);

		ad1=data_limitation(LO_L_r1);
		ad2=data_limitation(LI_L_r1); 
		ad3=data_limitation(M_L_r1);   
		ad4=data_limitation(RI_L_r1); 
		ad5=data_limitation(RO_L_r1);
		ad6=data_limitation(belly_R_L_r1);
		ad7=data_limitation(belly_L_L_r1);
	}
	}
    //以上的数据采集以及控制代码建议放入周期中断，保证代码的执行周期是一样的
        //数据发送代码建议放在主循环，使用if查询，如果数据采集成功就发送数据		
void  data_send()
{	
			//前两个字节为时间，如果程序结构里面有时间变量可以将时间变量输出，这样我们接受到数据后
			//可以根据时间来判断包是否是连续的，是否有丢包
            send_buff[0] = 0;
            send_buff[1] = 00;
            
            send_buff[2] = ad1;
            send_buff[3] = ad2;
            send_buff[4] = ad3;
            send_buff[5] = ad4;
            send_buff[6] = ad5;
            send_buff[7] = ad6;
            send_buff[8] = ad7;
            
			//将舵机数值转换为-128至+127  因为舵机转角被限制在-400至+400之间，
			//因此舵机转角除以420之后绝对值必定是小于1的，
			//然后在乘以128数据范围也就一定被限制在了-128至+127之间了。
           smotor_num = (int)((float)(smotor_angle)/400.0*127.0);
						send_buff[9]=camera_error;//smotor_num;
			//固定字节，可以用于校验或者方便肉眼可辨每一个包是否正确
            send_buff[10] = 0x5a;
            
            seekfree_wireless_send_buff(send_buff,11);
}
