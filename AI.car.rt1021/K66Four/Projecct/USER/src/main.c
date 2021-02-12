#include "headfile.h"
#include "MK60_uart.h"
#include "DFlash.h"
#include "Bluetooth.h"
#include "Menu.h"
#include "isr.h"
#include "Init.h"
//#include "Meeting.h"
#include "Message.h"

void SelectVar(int n);

int main(void)
{
	get_clk();
	system_Init();
	systick_delay_ms(1000);
//        MyFlash_Write(0);
	MyFlash_Read(0);
	
	dialSwitchFlg1 = gpio_get(DIALSWITCH_PIN1); //保护
	dialSwitchFlg2 = gpio_get(DIALSWITCH_PIN2); //电磁模式
	dialSwitchFlg3 = gpio_get(DIALSWITCH_PIN3); //选择参数
	dialSwitchFlg4 = gpio_get(DIALSWITCH_PIN4); //选择参数
	SelectVar((dialSwitchFlg3 << 1) + dialSwitchFlg4);
	while (1)
	{
                //SendData(SendFlag);
                RampJudge();

                static int count = 0;
                if((ReceiveFlag == 1 && count == 0 && SingleFlag == 0 && g_drive_flag == 1)) 
                   //|| (SingleFlag == 0 && leftDrv.error_1 != 0 && rightDrv.error_1 != 0 && g_drive_flag == 1))
                {
                      count++;
                      CircleFlag = 0;
                      CircleState = 0;
                      InCircleState = 0;
                      Img_RampFlag = 0;
                      speed_type = 1;
                      if (1 == g_camera_open)
                              g_handle_open = 1;
                      g_steer_open = 1;
                      g_ad_flag = 1;
                      g_ramp_open = 1; 
                      g_garage_open = 0;
                }
		if (mt9v032_finish_flag)					//图像接收完成标志位
		{
			mt9v032_finish_flag = 0; //标志位清零
                        //gray2Binary(image[0],image[0]);
//                        if(ReceiveFlag == 1)
//                          g_handle_open = 1;
                        NavigationOut();                   //惯性导航出
			if (1 == g_handle_open)
			{
                            if (1)//dialSwitchFlg2)			//摄像头模式
                            {
                                //gpio_init(C15,GPO,0);
                                PhotoShow();
                                //gpio_init(C15,GPO,1);
                                NavigationIn();                   //惯性导航入  
                            }
                            else ;
			}
		}
                Menu();
                static int tempa = 0;
		if (ReceiveFlag == 1)//(SingleFlag == 0 && ReceiveFlag == 1) || SingleFlag == 1)//Img_RampFlag == 0)//dialSwitchFlg2)
                {
                    tempa = 1;
                    //gpio_set(A7, 0);
                }
                if(tempa == 1 || SingleFlag == 1)
                {
                    CarControl();
                }
//		else
//                {
//                    CarControl_Ind();
//                    gpio_set(A7, 1);
//                }
                    
		
		//BluetoothSendData(); //FreeCars
                //UserData();//匿名上位机
                
		//SendData(); //会车
					//		UserData();
		//SendAngle();
		//                LogGetData();

			
		// Bluebooth_Push_Data();
		//ExploreTime();
	}

}

void SelectVar(int n)
{
	switch (n)
	{

	case 1:				//28线稳定走中线
                g_speed_p = 500;
                g_speed_i = 18;
		p_max = 1.40;
		p_min = 1.93;
		Steer_D1 = 4.35;
		ProSpect = 38;
		Steer_P_CI = 1.25;
		spdBas1 = 38;
                spdExp4 = 30;
                spdBas3 = 22;
		KDet = 10;
                In_kdet = 8;
                StopDis = 550;
                StopRow = 38;
                Stop_UpRow = 43;
		break;
	case 2:			//31线稳妥寻中线
		g_speed_p = 520;
                g_speed_i = 20;
		p_max = 1.40;
		p_min = 2.53;
		Steer_D1 = 4.25;
		ProSpect = 38;
		Steer_P_CI = 1.25;
		spdBas1 = 40;
                spdExp4 = 30;
                spdBas3 = 28;
		KDet = 10;
                In_kdet = 8;
                StopDis = 550;
                StopRow = 38;
                Stop_UpRow = 43;
		break;
	case 3:				//33线较稳定
		p_max = 1.79;
		p_min = 2.10;
		Steer_D = 2.05;
		ProSpect = 38;
		Steer_P_CI = 1.90;
		spdBas1 = 33;
		KDet = 20;
		break;
        //修正
        case 4:
                p_max = 1.44;
		p_min = 1.54;
		Steer_D = 1.79;
		ProSpect = 37;
		Steer_P_CI = 1.49;
		spdBas1 = 28;
		KDet = 20;
		break;
        case 5:
                g_speed_p = 400;
                g_speed_i = 15;
                p_max = 1.24;
		p_min = 1.75;
		Steer_D = 1.69;
		ProSpect = 35;
		Steer_P_CI = 1.59;
		spdBas1 = 28;
		KDet = 20;
		break;
	default:
		break;
	}
}