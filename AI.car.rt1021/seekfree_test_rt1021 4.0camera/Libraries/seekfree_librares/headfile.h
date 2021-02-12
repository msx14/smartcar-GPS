/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2019,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ��һȺ��179029047(����)  ��Ⱥ��244861897
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ����������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file       		headfile
 * @company	   		�ɶ���ɿƼ����޹�˾
 * @author     		��ɿƼ�(QQ3184284598)
 * @version    		�鿴doc��version�ļ� �汾˵��
 * @Software 		IAR 8.3 or MDK 5.26
 * @Target core		NXP RT1021DAG5A
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2019-02-18
 ********************************************************************************************************************/
 
#ifndef _headfile_h
#define _headfile_h


#include <stdint.h>
#include "fsl_common.h"

#include "fsl_debug_console.h"
#include "fsl_iomuxc.h"
#include "fsl_pit.h"
#include "fsl_cache.h"
#include "board.h"
#include "pin_mux.h"
#include "clock_config.h"

#include "common.h"

#include "SEEKFREE_PRINTF.h"

//---------XMU-------

#define _USE_IPS 0
#define _USE_LCD 1

#include "ADCollection.h"
#include "GlobalVar.h"
#include "Init.h"
#include "keyboard.h"
#include "SmotorControl.h"
#include "OLED.h"
#include "Screen.h"
#include "Menu.h"
#include "spd.h"
 #include "nncie.h"
 #include "MCP4452.h"
 #include "Bluetooth.h"
//------��ɿƼ���Ƭ����������ͷ�ļ�
#include "zf_gpio.h"
#include "zf_iomuxc.h"
#include "zf_pit.h"
#include "zf_pwm.h"
#include "zf_uart.h"
//#include "zf_flash.h"
#include "zf_spi.h"
#include "zf_systick.h"
#include "zf_qtimer.h"
#include "zf_adc.h"
#include "zf_iic.h"
#include "zf_camera.h"
#include "zf_flash.h"


//------��ɿƼ���Ʒ����ͷ�ļ�
#include "SEEKFREE_FONT.h"
#include "SEEKFREE_18TFT.h"
#include "SEEKFREE_IPS114_SPI.h"
#include "SEEKFREE_IIC.h"
#include "SEEKFREE_VIRSCO.h"
#include "SEEKFREE_FUN.h"
#include "SEEKFREE_MPU6050.h"
#include "SEEKFREE_OLED.h"
#include "SEEKFREE_NRF24L01.h"
#include "SEEKFREE_MMA8451.h"
#include "SEEKFREE_L3G4200D.h"
#include "SEEKFREE_ICM20602.h"
#include "SEEKFREE_MT9V032.h"
#include "SEEKFREE_WIRELESS.h"
#include "SEEKFREE_W25Q64.h"
#include "SEEKFREE_IPS200_PARALLEL8.h"
#include "SEEKFREE_SCC8660.h"


#endif