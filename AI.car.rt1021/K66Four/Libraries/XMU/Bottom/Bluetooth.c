#include "Bluetooth.h"
#include "common.h"
#include "MK60_uart.h"

uint8 uSendBuf[UartDataNum * 2] = { 0 };
uint8 XmuDataNum = UartDataNum * 2;
extern UART_Type* uart[];

double UartData[9] = { 0 };
SerialPortType SerialPortRx;


void SendUserData()
{
//	SendFloat(mid_norm);
//	SendFloat(leftcol_norm);
//	SendFloat(rightcol_norm);
  
        SendInt(CircleState);
        SendInt(temp);
        SendInt(AD_CircleFlag);
	SendFloat(YawAngle);
        SendInt(SteerDuty);

        //SendInt(InCircleState);
//	SendInt(SpeedRow);
//	SendInt(spdExp1);
	//SendInt(Error_1);
	//SendInt(LightThreshold);
	//SendFloat(ind_right);
	//SendFloat(ind_left + ind_right);
	//SendFloat(imu_data.yaw);
	//SendInt(Img_BrokenFlag);
	//SendInt(Img_BlockFlag);
	//SendInt(LeftPnt.ErrRow);
	//SendInt(RightPnt.ErrRow);
	//SendInt(g_inf);
	//SendInt(SteerDuty);
	//SendFloat(leftExpect);
	//SendFloat(rightExpect);
	//SendInt(lCurSpeed);
	//SendInt(rCurSpeed);
}

void BluetoothInt()
{
	uart_init(XmuUARTPort, XmuBR);

	//  set_vector_handler(XmuUARTPortVECTORn,XmuUartHander);   // �����жϷ��������ж���������
	uart_rx_irq_en(XmuUARTPort);                                 //�����ڽ����ж�
}
/*
��ĳ��ͨ���������������
chanel��ͨ��
data  ������-32768~32767
*/
void push(uint8 chanel, uint16 data)
{
	uSendBuf[chanel * 2] = data / 256;
	uSendBuf[chanel * 2 + 1] = data % 256;
}


void sendDataToScope(void)
{
	uint8 i, sum = 0;
	//ʹ����ѯ�ķ�ʽ�������ݣ�������δ���ͣ�����ͣ�ڴ˴�ֱ���������
	uart_putchar(XmuUARTPort, 251);
	uart_putchar(XmuUARTPort, 109);
	uart_putchar(XmuUARTPort, 37);
	sum += (251);      //ȫ�����ݼ���У��
	sum += (109);
	sum += (37);
	for (i = 0; i < XmuDataNum; i++)
	{
		uart_putchar(XmuUARTPort, uSendBuf[i]);
		sum += uSendBuf[i];         //ȫ�����ݼ���У��
	}
	uart_putchar(XmuUARTPort, sum);
}

void BluetoothSendData(void)
{
	push(0, -1);
	sendDataToScope();
}


float DataTest, Datatest1;

//  ��ֵ��������Ҫ�����������
void UartDebug(void)
{
	DataTest = (float)UartData[0];
	Datatest1 = (float)UartData[1];
}
/*
������պ���
CmdNum��0~255������
DATA  ��0~255����������Ӧ��������
��ʱ���ù�
*/
void UartCmd(uint8 CmdNum, uint8 Data)
{
	//LedBlueRev;
}

//�����жϷ�����
void uart4_handler(void)
{
	int i, b, d1;
	uint32 d;
	uint8 ch;

	if (uart[uart4]->RCFIFO != 0)//�ǽ����ж�
	{
		uart_getchar(uart4, &ch);                    //���޵ȴ�����1���ֽ�
		SerialPortRx.Data = ch;

		if (SerialPortRx.Stack < UartRxBufferLen)
		{
			SerialPortRx.Buffer[SerialPortRx.Stack++] = SerialPortRx.Data;

			if (SerialPortRx.Stack >= UartRxDataLen  //UartRxDataLen����Ϊһ֡
				&& SerialPortRx.Buffer[SerialPortRx.Stack - UartRxDataLen] == 0xff //У����ͷ
				&& SerialPortRx.Buffer[SerialPortRx.Stack - UartRxDataLen + 1] == 0x55
				&& SerialPortRx.Buffer[SerialPortRx.Stack - UartRxDataLen + 2] == 0xaa
				&& SerialPortRx.Buffer[SerialPortRx.Stack - UartRxDataLen + 3] == 0x10)
			{   //double data 9��ͨ������У��
				SerialPortRx.Check = 0;
				b = SerialPortRx.Stack - UartRxDataLen; //��ʼλ
				for (i = b; i < SerialPortRx.Stack - 1; i++)  //��У��λ���λ����У��
				{
					SerialPortRx.Check += SerialPortRx.Buffer[i];//У��
				}

				if (SerialPortRx.Check == SerialPortRx.Buffer[SerialPortRx.Stack - 1])
				{   //У��ɹ����������ݽ���
					for (i = 0; i < 9; i++)
					{
						d = SerialPortRx.Buffer[b + i * 4 + 4] * 0x1000000L + SerialPortRx.Buffer[b + i * 4 + 5] * 0x10000L + SerialPortRx.Buffer[b + i * 4 + 6] * 0x100L + SerialPortRx.Buffer[b + i * 4 + 7];
						if (d > 0x7FFFFFFF)
						{
							d1 = 0x7FFFFFFF - d;
						}
						else
						{
							d1 = d;
						}
						UartData[i] = d1;
						UartData[i] /= 65536.0;
					}
					UartDebug();  //תȥ�������ܵ������ݸ�������
				}
				SerialPortRx.Stack = 0;
			}
			else if (SerialPortRx.Stack >= UartRxCmdLen //UartRxDataLen����Ϊһ֡
				&& SerialPortRx.Buffer[SerialPortRx.Stack - UartRxCmdLen] == 0xff
				&& SerialPortRx.Buffer[SerialPortRx.Stack - UartRxCmdLen + 1] == 0x55
				&& SerialPortRx.Buffer[SerialPortRx.Stack - UartRxCmdLen + 2] == 0xaa
				&& SerialPortRx.Buffer[SerialPortRx.Stack - UartRxCmdLen + 3] == 0x77)//cmd
			{
				SerialPortRx.Check = 0;
				b = SerialPortRx.Stack - UartRxCmdLen; //��ʼλ
				for (i = b; i < SerialPortRx.Stack - 1; i++)  //��У��λ���λ����У��
				{
					SerialPortRx.Check += SerialPortRx.Buffer[i];//У��
				}
				if (SerialPortRx.Check == SerialPortRx.Buffer[SerialPortRx.Stack - 1])
				{   //У��ɹ�
					UartCmd(UartCmdNum, UartCmdData);//������յ����������MCU�������
				}
				SerialPortRx.Stack = 0;
			}
		}
		else
		{
			SerialPortRx.Stack = 0;
		}
	}
}

//���ڷ�����̬
void SendAngle(void)
{
	uint8 sendbuff[32] = { 0 };
	uint8_t temp = 0;
	int16_t yaww, rolll, pitchh; //??D?????
	int32_t alt;
	alt = 0;//z_est[0]*100;
	yaww = (int16_t)(imu_data.yaw * 100);
	rolll = (int16_t)(imu_data.rol * 100);
	pitchh = (int16_t)(imu_data.pit * 100);

	sendbuff[0] = 0xaa;
	sendbuff[1] = 0xaa;
	sendbuff[2] = 0x01;
	sendbuff[3] = 12;
	sendbuff[4] = rolll >> 8;
	sendbuff[5] = rolll;
	sendbuff[6] = pitchh >> 8;
	sendbuff[7] = pitchh;
	sendbuff[8] = yaww >> 8;
	sendbuff[9] = yaww;

	sendbuff[10] = alt >> 24;
	sendbuff[11] = alt >> 16;
	sendbuff[12] = alt >> 8;
	sendbuff[13] = alt;

	sendbuff[14] = 0;
	sendbuff[15] = 0;
	sendbuff[16] = 0;
	for (temp = 0; temp < 16; temp++)
	{
		sendbuff[16] += sendbuff[temp];
	}
	uart_putbuff(XmuUARTPort, sendbuff, 17);
}

unsigned char testdatatosend[50];	//�������ݻ���
unsigned char _cnt = 0;
unsigned char _count = 0;
//���ݲ�ֺ궨�壬�ڷ��ʹ���1�ֽڵ���������ʱ������int16��float�ȣ���Ҫ�����ݲ�ֳɵ����ֽڽ��з���
#define BYTE0(dwTemp)       ( *( (char *)(&dwTemp)	  ) )
#define BYTE1(dwTemp)       ( *( (char *)(&dwTemp) + 1) )
#define BYTE2(dwTemp)       ( *( (char *)(&dwTemp) + 2) )
#define BYTE3(dwTemp)       ( *( (char *)(&dwTemp) + 3) )

void SendFloat(float Data)
{
	testdatatosend[_cnt++] = BYTE3(Data);//��Ҫ���͵����ݷ������ͻ�����
	testdatatosend[_cnt++] = BYTE2(Data);
	testdatatosend[_cnt++] = BYTE1(Data);
	testdatatosend[_cnt++] = BYTE0(Data);
	_count += 4;
}
void SendInt(int Data)
{
	testdatatosend[_cnt++] = BYTE1(Data);
	testdatatosend[_cnt++] = BYTE0(Data);
	_count += 2;
}


void UserData(void)
{
	_cnt = 0;
	_count = 0;
	static unsigned char Length = 0;
	testdatatosend[_cnt++] = 0xAA;//0xAAΪ֡ͷ
	testdatatosend[_cnt++] = 0xAA;
	testdatatosend[_cnt++] = 0xF1;
	testdatatosend[_cnt++] = 0;//���ֽڱ�ʾ���ݳ��ȣ�������=0����������ٸ�ֵ�������Ͳ����˹����㳤����

	SendUserData();

	Length = _count;

	testdatatosend[3] = Length;
	unsigned char sum = 0;	//����Ϊ����sumУ���ֽڣ���0xAAҲ�������ֽڣ�һֱ��sum�ֽ�ǰһ�ֽ�
	for (unsigned char i = 0; i < _cnt; i++)
	{
		sum += testdatatosend[i];
	}

	testdatatosend[_cnt++] = sum;	//��sumУ�����ݷ������һ�ֽ�	

	uart_putbuff(XmuUARTPort, testdatatosend, _cnt);//���÷������ݺ���
}


/*��λ����ͼ�񣬸���Ȥ�Ŀ�����һ��
#define ImgHeight 200 //????
#define ImgWidth 240 //????
uint8 imgData[ImgHeight*ImgWidth]={0};//?????,??????,??????

void sendCamImgToCamViewer(void)
{
  uint8 i,j;
  uint16 offset;
  uart_putchar(XmuUARTPort,0xFF);//FF,FE,FF,FE ��ʾһ��ͼ�Ŀ�ʼ
  uart_putchar(XmuUARTPort,0xFE);
  uart_putchar(XmuUARTPort,0xFF);
  uart_putchar(XmuUARTPort,0xFE);
  for(i = 0;i < ImgHeight;i++)
  {
	offset = i*ImgWidth; //????????
	for(j = 0;j < ImgWidth;j++)
	{
	  uint8 d = imgData[offset + j];
	  if(d > 0xFD) d = 0xFD;
	  uart_putchar(XmuUARTPort,d);
	}
	uart_putchar(XmuUARTPort,0xFE);//FE,FE ��ʾ����
	uart_putchar(XmuUARTPort,0xFE);
  }
  j=0;
}

*/