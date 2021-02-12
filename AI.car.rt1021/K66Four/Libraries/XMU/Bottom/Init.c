#include "common.h"
#include "headfile.h"
#include "isr.h"
#include "Init.h"
#include "TFCard.h"
#include "crc.h"
#include "BMP.h"
#include "AD.h"

//*    PIT_Init(void)
//*	@brief:		PIT��ʼ��
//*	@param:		void
//*	@return:	void 
//* @note:      void
//*
void PIT_Init(void)
{
	pit_init_ms(pit0, 2);                                //��ʼ��PIT0,��ʱ2ms  
	enable_irq(PIT0_IRQn);                              // ʹ��PIT�ж�   
}


//*    communication_Init(void)
//*	@brief:		������ʼ��
//*	@param:		void
//*	@return:	void 
//* @note:      void
//*
void communication_Init(void)
{
	uart_init(uart4, 115200);
	uart_rx_irq_en(uart4);                                  //�����ڽ����ж�
}

//*    Encoder_Init(void)
//*	@brief:		��������ʼ��
//*	@param:		void
//*	@return:	void 
//* @note:      void
//*
void encoder_Init(void)
{								//ʹ��
	//  ��������  FTM1  A8��A9
	ftm_quad_init(ftm1);
	ftm_quad_init(ftm2);
}

//=================================================================//
//  @brief:	���PWM��ʼ��
//  @param: 	
//  @return: 
//  @note: 
//=================================================================//
void DriveInit()

{
	ftm_pwm_init(ftm0, ftm_ch4, 16000, 0);//��ǰ
	ftm_pwm_init(ftm0, ftm_ch5, 16000, 0);
	ftm_pwm_init(ftm0, ftm_ch6, 16000, 0);//�Һ�
	ftm_pwm_init(ftm0, ftm_ch7, 16000, 0);
}

//=================================================================//
//  @brief:	�����ʼ��
//  @param: 	
//  @return: 
//  @note: 
//=================================================================//
void SteerInit(void)
{
  SteerDuty = InitSteer;
	ftm_pwm_init(ftm3, ftm_ch5, 75, InitSteer);   //�����ʼ��
}

//=================================================================//
//  @brief:	���뿪�عܽų�ʼ��
//  @param: 	
//  @return: 
//  @note: 
//=================================================================//
void DialSwitchInit()
{
	//�ܽų�ʼ��
	gpio_init(DIALSWITCH_PIN1, GPI, 1);
	gpio_init(DIALSWITCH_PIN2, GPI, 1);
	gpio_init(DIALSWITCH_PIN3, GPI, 1);
	gpio_init(DIALSWITCH_PIN4, GPI, 1);
	port_init_NoAlt(DIALSWITCH_PIN1, PULLUP);
	port_init_NoAlt(DIALSWITCH_PIN2, PULLUP);
	port_init_NoAlt(DIALSWITCH_PIN3, PULLUP);
	port_init_NoAlt(DIALSWITCH_PIN4, PULLUP);


}

//=================================================================//
//  @brief:	��г�ʼ��
//  @param: 	
//  @return: 
//  @note: 
//=================================================================//
void IndInit(void)
{
	adc_init(ADC_LEFT);
	adc_init(ADC_MIDDLE);
	adc_init(ADC_RIGHT);
}

//*    System_Init(void)
//*	@brief:		��ʼ��
//*	@param:		void
//*	@return:	void 
//* @note:      void
//*
uint8 Mpu_Error = 1;
void system_Init(void)
{
#if i2c
	IIC_init();
	dat = simiic_read_reg(ICM20602_DEV_ADDR, ICM20602_WHO_AM_I, IIC);
	icm20602_init();

#else
	Mpu_Error = icm20602_Init();
#endif 
	//communication_Init();
	//	OLED_Init();
	DriveInit();
	encoder_Init();
        SteerInit();
	lcd_init();
	//ips_init();
	camera_init();
	IndInit();
	adc_init(ADC1_SE17);               //�����ʼ��
	//FLASH_Init();
	//     sd_init();
	SD_BMP_Init();
	//        LogInit();
	DialSwitchInit();
	INTR_Keyboard_Init();		//���̳�ʼ��
        gpio_init(A7,GPO,0);
	//crcInit();
	PIT_Init();
	/**********�����ж����ȼ�**********/
	NVIC_SetPriorityGrouping(3);
	NVIC_SetPriority(PORTC_IRQn, 0);            //���ж�
        NVIC_SetPriority(DMA0_IRQn, 1);            //DMA0
	NVIC_SetPriority(PIT0_IRQn, 2);            //PIT
	NVIC_SetPriority(PORTA_IRQn, 3);            //�����ж�
}