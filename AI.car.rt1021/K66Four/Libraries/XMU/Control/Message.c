#include "headfile.h"
#include "Message.h"
#include "crc.h"
#include "Bluetooth.h"

//#define NumCount 4
//unsigned char sData[NumCount];
//unsigned char rData[NumCount];
//
//void SendData(void)
//{
//	sData[0] = 0x00;
//	sData[0] |= (g_GetMeetingMaster << 0);
//	sData[0] |= (g_MasterOutFlag << 1);
//	sData[0] |= (g_StartMaster << 2);
//	sData[1] = g_StateMaster;
//	width_t check_code = crcCompute(sData, NumCount - 2);
//	sData[NumCount - 2] = (unsigned char)(check_code >> 8);
//	sData[NumCount - 1] = (unsigned char)(check_code);
//	for (unsigned char i = 0; i < NumCount; i++)
//	{
//		uart_putchar(uart4, sData[i]);
//	}
//}
//
//void ReceiveData(void)
//{
//	static int RcNum = 0;
//	uart_getchar(uart4, &rData[RcNum]);
//	RcNum++;
//	if (RcNum >= NumCount)
//	{
//		RcNum = 0;
//		width_t check_code = crcCompute(rData, NumCount - 2);
//		if (rData[NumCount - 2] == (unsigned char)(check_code >> 8)
//		    && rData[NumCount - 1] == (unsigned char)(check_code))
//		{
//			if (g_GetMeetingMaster)
//				g_GetMeetingSlave |= (rData[0] & 0x01);
//			g_SlaveOutFlag = (rData[0] & 0x02) >> 1;
//			g_StartSlave = (rData[0] & 0x04) >> 2;
//			g_StateSlave = rData[1];
//		}
//	}
//}


//unsigned char sData;
//unsigned char rData;
//void SendData(void)
//{
//	sData = 0x80;
//	sData |= (g_MasterOutFlag << 5);
//	sData += g_StateMaster;
//	uart_putchar(uart4, sData);
//}
//
//void ReceiveData(void)
//{
//	uart_getchar(uart4, &rData);
//	if (0x80 == (rData & 0xC0))
//	{
//		if (rData & (1 << 5)) g_SlaveOutFlag = 1;
//		else g_SlaveOutFlag = 0;
//		g_StateSlave = MAX(g_StateSlave, (rData & 0x1F));
////		g_StateSlave = 0;
//	}
//}
//
////数据拆分宏定义，在发送大于1字节的数据类型时，比如int16、float等，需要把数据拆分成单独字节进行发送
//#define INTBYTE0(dwTemp)       ( *( (char *)(&dwTemp)) )
//#define INTBYTE1(dwTemp)       ( *( (char *)(&dwTemp) + 1) )

void SendData(unsigned char Data)
{
    static unsigned char storagedata[5];	//发送数据缓存
    unsigned char _cnt = 0;

    storagedata[_cnt++] = 0xAA;//0xAA为帧头
    storagedata[_cnt++] = 0xAA;
    
    storagedata[_cnt++] = Data;

    storagedata[_cnt++] = 0xAD;//0xAD为帧尾
    storagedata[_cnt++] = 0xAD;
    
    for (unsigned char i = 0; i < _cnt; i++)
    {
          uart_putchar(uart4, storagedata[i]);//调用发送数据函数
    }
}

void ReceiveData(void)
{
    static unsigned char _count = 0;
    static unsigned char data;
    unsigned char rData;

    uart_getchar(uart4, &data);
    
    switch(_count)
    {
    case 0:
            {
                if(data == 0xAA)
                  _count++;
                else
                  _count = 0;
            }
            break;
    case 1:
            {
                if(data == 0xAA)
                  _count++;
                else
                  _count = 0;
            }
            break;
    case 2:
            {
                rData = data;
                _count++;
            }
            break;
    case 3:
            {
                if(data == 0xAD)
                  _count++;
                else
                  _count = 0;
            }
            break;
    case 4:
            {
                if(data == 0xAD)
                {
                   _count = 0;
                    ReceiveFlag = rData; 
                }
                else
                  _count = 0;
            }
            break;
    default:
            break;
    }
    	
}