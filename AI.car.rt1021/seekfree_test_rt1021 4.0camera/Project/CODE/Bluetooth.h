/*
 * Bluetooth.h
 *
 *  Created on: 2020年6月26日
 *      Author: lenovo
 */

#ifndef CODE_BOTTOM_BLUETOOTH_H_
#define CODE_BOTTOM_BLUETOOTH_H_


#include "headfile.h"
//#include "XMU_IMU.h"
#include "common.h"
#include "zf_uart.h"

//FreeCars上位机 串口数据显示框 接收通道数，按照上位机设置改变
#define UartDataNum      17
#define XmuUARTPort      UART_0
#define XmuIRQ           IRQ_UART4
#define XmuBR            115200       //波特率

#define XmuUARTPortVECTORn  UART4_RX_TX_VECTORn
#define XmuUartHander       uart4_handler

//以下不要修改
#define UartRxBufferLen  100
#define UartRxDataLen    41           //FreeCars上位机发送浮点数据MCU接收，不要改
#define UartRxCmdLen     7	      //FreeCars上位机接收命令数据长度，不要改

#define UartCmdNum  SerialPortRx.Buffer[SerialPortRx.Stack-3]//命令号
#define UartCmdData SerialPortRx.Buffer[SerialPortRx.Stack-2]//命令数据
//尽管数据的长度只要求数组长度为26=22+3+1；但是为了与发送字符串取得统一
//取数据的长度与字符串的长度相等，这样在发送数据是会多发送了一些
//无效位，但是影响不大的

typedef struct
{
	int Stack;
	uint8 Data;
	uint8 PreData;
	uint8 Buffer[UartRxBufferLen];
	uint8 Enable;
	uint8 Check;
}SerialPortType;

//extern unsigned char uSendBuf[UartDataNum*2];

void BluetoothInt();
void push(unsigned char chanel, unsigned short int data);
void sendDataToScope(void);
void BluetoothSendData(void);
void UartDebug(void);
void uart4_handler(void);
void SendAngle(void);
void sendCamImgToCamViewer(void);
void UserData(void);
void SendFloat(float Data);
void SendInt(int Data);


#define COM_COF_UART	USART_1
#define COM_COF_UART_TX   UART1_TX_B6
#define COM_COF_UART_RX  	UART1_RX_B7

//void com_init(void);
extern int get_times;


#endif /* CODE_BOTTOM_BLUETOOTH_H_ */
