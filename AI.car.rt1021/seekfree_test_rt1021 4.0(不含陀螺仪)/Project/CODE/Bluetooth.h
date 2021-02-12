/*
 * Bluetooth.h
 *
 *  Created on: 2020��6��26��
 *      Author: lenovo
 */

#ifndef CODE_BOTTOM_BLUETOOTH_H_
#define CODE_BOTTOM_BLUETOOTH_H_


#include "headfile.h"
//#include "XMU_IMU.h"

//FreeCars��λ�� ����������ʾ�� ����ͨ������������λ�����øı�
#define UartDataNum      17
#define XmuUARTPort      UART_0
#define XmuIRQ           IRQ_UART4
#define XmuBR            115200       //������

#define XmuUARTPortVECTORn  UART4_RX_TX_VECTORn
#define XmuUartHander       uart4_handler

//���²�Ҫ�޸�
#define UartRxBufferLen  100
#define UartRxDataLen    41           //FreeCars��λ�����͸�������MCU���գ���Ҫ��
#define UartRxCmdLen     7	      //FreeCars��λ�������������ݳ��ȣ���Ҫ��

#define UartCmdNum  SerialPortRx.Buffer[SerialPortRx.Stack-3]//�����
#define UartCmdData SerialPortRx.Buffer[SerialPortRx.Stack-2]//��������
//�������ݵĳ���ֻҪ�����鳤��Ϊ26=22+3+1������Ϊ���뷢���ַ���ȡ��ͳһ
//ȡ���ݵĳ������ַ����ĳ�����ȣ������ڷ��������ǻ�෢����һЩ
//��Чλ������Ӱ�첻���

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


#endif /* CODE_BOTTOM_BLUETOOTH_H_ */
