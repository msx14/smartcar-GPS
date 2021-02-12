#include  "headfile.h"
#include  "Init.h"

void AD_Init()//��вɼ���ʼ��
{

	//�����ڳ���Χ���߸����
    adc_init(ADC_1,ADC1_CH3_B17 ,ADC_12BIT);
    adc_init(ADC_1,ADC1_CH4_B19 ,ADC_12BIT);
    adc_init(ADC_2,ADC2_CH4_B20 ,ADC_12BIT);
    adc_init(ADC_1,ADC1_CH6_B22 ,ADC_12BIT);
	  adc_init(ADC_1,ADC1_CH5_B21 ,ADC_12BIT);
    adc_init(ADC_2,ADC2_CH3_B18 ,ADC_12BIT);
    adc_init(ADC_1,ADC1_CH7_B23 ,ADC_12BIT);
}
void encoder_Init(void)//�������ɼ���ʼ��
{								
	   //��ʼ�� QTIMER_1 A��ʹ��QTIMER1_TIMER0_D0 B��ʹ��QTIMER1_TIMER1_D1
    qtimer_quad_init(QTIMER_1,QTIMER1_TIMER0_D0,QTIMER1_TIMER1_D1);
    //��ʼ�� QTIMER_1 A��ʹ��QTIMER1_TIMER2_D2 B��ʹ��QTIMER1_TIMER3_D3
    qtimer_quad_init(QTIMER_1,QTIMER1_TIMER2_D2,QTIMER1_TIMER3_D3);
}
void DriveInit()//�����ʼ��
{
	pwm_init(PWM2_MODULE1_CHA_D4, 16000, 0);
	pwm_init(PWM2_MODULE1_CHB_D5, 16000, 0);
	pwm_init(PWM2_MODULE0_CHA_D6, 16000, 0);
	pwm_init(PWM2_MODULE0_CHB_D7, 16000, 0);
}
void iokey_init()//���뿪�ؼ��ɻɹܶ˿ڳ�ʼ��
{
	  gpio_init(D13,GPI,0,GPIO_PIN_CONFIG);
    gpio_init(D14,GPI,0,GPIO_PIN_CONFIG);
    gpio_init(D15,GPI,0,GPIO_PIN_CONFIG);
    gpio_init(D17,GPI,0,GPIO_PIN_CONFIG);	
		gpio_init(B14,GPI,0,GPIO_PIN_CONFIG);
}
void numchange_init()//���ֵ�λ����ʼ��
{
	MCP4452_all_init();
MCP4452_val_ALL_init(initR, W_RO, W_belly_L, W_RI,W_M, W_LO, W_LI, W_belly_R);
}
void system_init(void)
{
	    
 AD_Init();
pwm_init(PWM1_MODULE0_CHB_C27, 50, SMOTOR_CENTER);   //�����ʼ�� 
encoder_Init();
iokey_init();
numchange_init();
 pit_init();
 pit_interrupt_ms(PIT_CH0,2);//�жγ�ʼ�� 2ms��һ���ж� zf_pit.h�п���ѡ��
 lcd_init();
 DriveInit();
}


