/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2019,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：一群：179029047(已满)  二群：244861897
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		isr
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		查看doc内version文件 版本说明
 * @Software 		IAR 8.3 or MDK 5.26
 * @Target core		NXP RT1021DAG5A
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2019-02-18
 ********************************************************************************************************************/

#include "headfile.h"
#include "isr.h"
#include "GlobalVar.h"
#include "Bluetooth.h"

void PIT_IRQHandler(void)
{
		if(PIT_FLAG_GET(PIT_CH0))
		{
			train_ad_collection();
			type_change();
			SpeedControl();//速控（包括闭环和差速）
			
		if(gpio_get(D15)==1)
		{			
//			if(stop_tiktok%200>150)
//			{
//				if(smotor_angle>80||smotor_angle<-80)
//					smotor_angle=-smotor_angle;
//				else if(smotor_angle<80&&smotor_angle>=0)
//					smotor_angle=180;
//				else if(smotor_angle<0&&smotor_angle>-80)
//					smotor_angle=-180;
//				pwm_duty(PWM1_MODULE0_CHB_C27,smotor_angle+SMOTOR_CENTER);
//			}
//			else if(stop_tiktok%200<=150)
//			{
//			pwm_duty(PWM1_MODULE0_CHB_C27,smotor_angle+SMOTOR_CENTER);
			/*	UserData();*/data_send();
//			}
				
		}
		if(stop_judge==3)	global_judge=1;
	//	if(stop_tiktok>=1000&&stop_judge==0)	global_judge=1;
			
		
		PIT_FLAG_CLEAR(PIT_CH0);
  }
    if(PIT_FLAG_GET(PIT_CH1))
    {
			if(gpio_get(D15)==1)
				stop_tiktok++;
			
        PIT_FLAG_CLEAR(PIT_CH1);
    }
    
    if(PIT_FLAG_GET(PIT_CH2))
    {
        PIT_FLAG_CLEAR(PIT_CH2);
    }
    
    if(PIT_FLAG_GET(PIT_CH3))
    {
        PIT_FLAG_CLEAR(PIT_CH3);
    }

    __DSB();
}


void GPIO1_Combined_16_31_IRQHandler(void)
{
    if(GET_GPIO_FLAG(MT9V032_VSYNC_PIN))
    {
        //不用清除标志位，标志位在mt9v032_vsync函数内部会清除
        if(1 == flexio_camera_type)mt9v032_vsync();
    }
    if(GET_GPIO_FLAG(SCC8660_VSYNC_PIN))
    {
        //不用清除标志位，标志位在scc8660_vsync函数内部会清除
        if(2 == flexio_camera_type)scc8660_vsync();
    }
}


uint32 gpio_int_test;
void GPIO2_Combined_0_15_IRQHandler(void)
{
    if(GET_GPIO_FLAG(C15))
    {
        CLEAR_GPIO_FLAG(C15);//清除中断标志位
        gpio_int_test++;
    }
}



/*
中断函数名称，用于设置对应功能的中断函数
Sample usage:当前启用了周期定时器中断
void PIT_IRQHandler(void)
{
    //务必清除标志位
    __DSB();
}
记得进入中断后清除标志位
CTI0_ERROR_IRQHandler
CTI1_ERROR_IRQHandler
CORE_IRQHandler
FLEXRAM_IRQHandler
KPP_IRQHandler
Reserved56_IRQHandler
GPR_IRQ_IRQHandler
Reserved58_IRQHandler
Reserved59_IRQHandler
Reserved60_IRQHandler
WDOG2_IRQHandler
SNVS_HP_WRAPPER_IRQHandler
SNVS_HP_WRAPPER_TZ_IRQHandler
SNVS_LP_WRAPPER_IRQHandler
CSU_IRQHandler
DCP_IRQHandler
DCP_VMI_IRQHandler
Reserved68_IRQHandler
TRNG_IRQHandler
Reserved70_IRQHandler
BEE_IRQHandler
PMU_IRQHandler
Reserved78_IRQHandler
TEMP_LOW_HIGH_IRQHandler
TEMP_PANIC_IRQHandler
USB_PHY_IRQHandler
Reserved82_IRQHandler
ADC1_IRQHandler
ADC2_IRQHandler
DCDC_IRQHandler
Reserved86_IRQHandler
Reserved87_IRQHandler
GPIO1_INT0_IRQHandler
GPIO1_INT1_IRQHandler
GPIO1_INT2_IRQHandler
GPIO1_INT3_IRQHandler
GPIO1_INT4_IRQHandler
GPIO1_INT5_IRQHandler
GPIO1_INT6_IRQHandler
GPIO1_INT7_IRQHandler
GPIO1_Combined_0_15_IRQHandler
GPIO1_Combined_16_31_IRQHandler
GPIO2_Combined_0_15_IRQHandler
GPIO2_Combined_16_31_IRQHandler
GPIO3_Combined_0_15_IRQHandler
GPIO3_Combined_16_31_IRQHandler
Reserved102_IRQHandler
Reserved103_IRQHandler
GPIO5_Combined_0_15_IRQHandler
GPIO5_Combined_16_31_IRQHandler
Reserved107_IRQHandler
WDOG1_IRQHandler
RTWDOG_IRQHandler
EWM_IRQHandler
CCM_1_IRQHandler
CCM_2_IRQHandler
GPC_IRQHandler
SRC_IRQHandler
Reserved115_IRQHandler
GPT1_IRQHandler
GPT2_IRQHandler
PWM1_0_IRQHandler
PWM1_1_IRQHandler
PWM1_2_IRQHandler
PWM1_3_IRQHandler
PWM1_FAULT_IRQHandler
Reserved123_IRQHandler
SEMC_IRQHandler
Reserved128_IRQHandler
USB_OTG1_IRQHandler
XBAR1_IRQ_0_1_IRQHandler
XBAR1_IRQ_2_3_IRQHandler
ADC_ETC_IRQ0_IRQHandler
ADC_ETC_IRQ1_IRQHandler
ADC_ETC_IRQ2_IRQHandler
ADC_ETC_ERROR_IRQ_IRQHandler
PIT_IRQHandler
ACMP1_IRQHandler
ACMP2_IRQHandler
ACMP3_IRQHandler
ACMP4_IRQHandler
Reserved143_IRQHandler
Reserved144_IRQHandler
ENC1_IRQHandler
ENC2_IRQHandler
Reserved147_IRQHandler
Reserved148_IRQHandler
TMR1_IRQHandler
TMR2_IRQHandler
Reserved151_IRQHandler
Reserved152_IRQHandler
PWM2_0_IRQHandler
PWM2_1_IRQHandler
PWM2_2_IRQHandler
PWM2_3_IRQHandler
PWM2_FAULT_IRQHandler*/



