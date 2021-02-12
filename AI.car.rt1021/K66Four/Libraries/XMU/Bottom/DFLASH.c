/*!
 * 	@file       ZS_DFlash.c
 * 	@brief      XMU SmartCar -> Group -> Camera
 * 	@author     WP
 * 	@version    New Car
 * 	@date       The Tenth in 2015
 */

#include<stdio.h>
#include<stdlib.h>

#include "headfile.h"
#include "DFlash.h"
#include "MK60_flash.h"
#include "MK60_savedata.h"
#include  "OLED.h"
#include <GlobalVar.h>
#include "common.h"



#define First_Time_Init 35


 /********** 以下为存储的数据 **********/
#define DFLASH_PARAM1       g_speed_p           //舵机P             
#define DFLASH_PARAM2       g_speed_i  // 前瞻
#define DFLASH_PARAM3       Steer_P_CI		//速度
#define DFLASH_PARAM4       p_max         //差速
#define DFLASH_PARAM5       p_min	//惯导停止距离
#define DFLASH_PARAM6       Steer_D1    //前进距离
#define DFLASH_PARAM7       spdBas1   //偏移角度
#define DFLASH_PARAM8       spdExp1	//识别延迟距离
#define DFLASH_PARAM9       ProSpect		
#define DFLASH_PARAM10      KDet	//舵机D
#define DFLASH_PARAM11      MidAD //环岛P
#define DFLASH_PARAM12      SteerP_Nav		//会车速度
#define DFLASH_PARAM13      SteerD_Nav	//进环岛判断距离阈值
#define DFLASH_PARAM14      exp_time	//摄像头曝光时间
#define DFLASH_PARAM15      p_max_Ind  //坡道
#define DFLASH_PARAM16      p_min_Ind	//路障
#define DFLASH_PARAM17      Steer_D_Ind	//单车模式
#define DFLASH_PARAM18      Steer_P_Ind	//速控p
#define DFLASH_PARAM19      Navagition_Dir	//速控i
#define DFLASH_PARAM20      CircleFlagSet	//canny高阈值
#define DFLASH_PARAM21      SingleFlag	//canny低阈值
#define DFLASH_PARAM22      StopDis      //摄像头中值
#define DFLASH_PARAM23      In_kdet
#define DFLASH_PARAM24      StopRow
#define DFLASH_PARAM25      spdBas3
#define DFLASH_PARAM26      Steer_D2
#define DFLASH_PARAM27      spdExp4
#define DFLASH_PARAM28      Stop_UpRow
#define DFLASH_PARAM29      ramp_speed_p
#define DFLASH_PARAM30      ramp_speed_i			//基准速度
#define DFLASH_PARAM31      Steer_P_Ramp			//会车基准速度

#define DFLASH_PARAM32          Steer_P_Ramp
#define DFLASH_PARAM33		Steer_P_Ind
#define DFLASH_PARAM34		Steer_D_Ind
#define DFLASH_PARAM35		p_max
#define DFLASH_PARAM36		p_min
#define DFLASH_PARAM37		p_max_Ind
#define DFLASH_PARAM38		p_min_Ind
#define DFLASH_PARAM39		p_LongRoad_Ind
#define DFLASH_PARAM40		spdBas3			//电磁基准速度
#define DFLASH_PARAM41		spdExp5
#define DFLASH_PARAM42		DarkThreshold
#define DFLASH_PARAM43		CircleDir[0]
#define DFLASH_PARAM44		CircleDir[1]
#define DFLASH_PARAM45		Ind_CI_TH
#define DFLASH_PARAM46		g_MeetingMode
#define DFLASH_PARAM47		g_MeetingDir
#define DFLASH_PARAM48		BlockDir[0]
#define DFLASH_PARAM49		BlockDir[1]
#define DFLASH_PARAM50		BlockDir[2]
#define DFLASH_PARAM51		BlockDir[3]
#define DFLASH_PARAM52		CircleDir[2]
#define DFLASH_PARAM53		CircleDir[3]
#define DFLASH_PARAM54		Img_GrayJumpOpen
#define DFLASH_PARAM55		BrokenThreshold
#define DFLASH_PARAM56		st_end
#define DFLASH_PARAM57		BlockCount
#define DFLASH_PARAM58		BrokenMode
#define DFLASH_PARAM59		MeetingStopMode
#define DFLASH_PARAM60		In_kdet
#define DFLASH_PARAM61		StopRow
#define DFLASH_PARAM62		spdBas3





/********** 以上为存储的数据 **********/

//*************************************************************************//
//--------------------------------存储数据---------------------------------//
//*************************************************************************//
void MyFlash_Write(signed int flashnum)
{
	DisableInterrupts;
	FLASH_EraseSector(SECTOR_NUM + flashnum);
	DFlash_Write_Int(SECTOR_NUM + flashnum, 0, First_Time_Init);



	/********** 以下为存储的数据 **********/
	DFlash_Write_Float(SECTOR_NUM + flashnum, 1, DFLASH_PARAM1);
	DFlash_Write_Float(SECTOR_NUM + flashnum, 2, DFLASH_PARAM2);
	DFlash_Write_Float(SECTOR_NUM + flashnum, 3, DFLASH_PARAM3);
	DFlash_Write_Float(SECTOR_NUM + flashnum, 4, DFLASH_PARAM4);
	DFlash_Write_Float(SECTOR_NUM + flashnum, 5, DFLASH_PARAM5);
	DFlash_Write_Float(SECTOR_NUM + flashnum, 6, DFLASH_PARAM6);
	DFlash_Write_Int(SECTOR_NUM + flashnum, 7, DFLASH_PARAM7);
	DFlash_Write_Int(SECTOR_NUM + flashnum, 8, DFLASH_PARAM8);
	DFlash_Write_Int(SECTOR_NUM + flashnum, 9, DFLASH_PARAM9);
	DFlash_Write_Int(SECTOR_NUM + flashnum, 10, DFLASH_PARAM10);
	DFlash_Write_Float(SECTOR_NUM + flashnum, 11, DFLASH_PARAM11);
	DFlash_Write_Float(SECTOR_NUM + flashnum, 12, DFLASH_PARAM12);
	DFlash_Write_Float(SECTOR_NUM + flashnum, 13, DFLASH_PARAM13);
	DFlash_Write_Int(SECTOR_NUM + flashnum, 14, DFLASH_PARAM14);
	DFlash_Write_Float(SECTOR_NUM + flashnum, 15, DFLASH_PARAM15);
	DFlash_Write_Float(SECTOR_NUM + flashnum, 16, DFLASH_PARAM16);
	DFlash_Write_Float(SECTOR_NUM + flashnum, 17, DFLASH_PARAM17);
	DFlash_Write_Float(SECTOR_NUM + flashnum, 18, DFLASH_PARAM18);
	DFlash_Write_Int(SECTOR_NUM + flashnum, 19, DFLASH_PARAM19);
	DFlash_Write_Int(SECTOR_NUM + flashnum, 20, DFLASH_PARAM20);
	DFlash_Write_Int(SECTOR_NUM + flashnum, 21, DFLASH_PARAM21);
	DFlash_Write_Int(SECTOR_NUM + flashnum, 22, DFLASH_PARAM22);
	DFlash_Write_Float(SECTOR_NUM + flashnum, 23, DFLASH_PARAM23);
	DFlash_Write_Int(SECTOR_NUM + flashnum, 24, DFLASH_PARAM24);
	DFlash_Write_Int(SECTOR_NUM + flashnum, 25, DFLASH_PARAM25);
	DFlash_Write_Float(SECTOR_NUM + flashnum, 26, DFLASH_PARAM26);
	DFlash_Write_Int(SECTOR_NUM + flashnum, 27, DFLASH_PARAM27);
	DFlash_Write_Int(SECTOR_NUM + flashnum, 28, DFLASH_PARAM28);
	DFlash_Write_Float(SECTOR_NUM + flashnum, 29, DFLASH_PARAM29);
	DFlash_Write_Float(SECTOR_NUM + flashnum, 30, DFLASH_PARAM30);
	DFlash_Write_Float(SECTOR_NUM + flashnum, 31, DFLASH_PARAM31);
//	DFlash_Write_Float(SECTOR_NUM + flashnum, 32, DFLASH_PARAM32);
//	DFlash_Write_Float(SECTOR_NUM + flashnum, 33, DFLASH_PARAM33);
//	DFlash_Write_Float(SECTOR_NUM + flashnum, 34, DFLASH_PARAM34);
//	DFlash_Write_Float(SECTOR_NUM + flashnum, 35, DFLASH_PARAM35);
//	DFlash_Write_Float(SECTOR_NUM + flashnum, 36, DFLASH_PARAM36);
//	DFlash_Write_Float(SECTOR_NUM + flashnum, 37, DFLASH_PARAM37);
//	DFlash_Write_Float(SECTOR_NUM + flashnum, 38, DFLASH_PARAM38);
//	DFlash_Write_Float(SECTOR_NUM + flashnum, 39, DFLASH_PARAM39);
//	DFlash_Write_Int(SECTOR_NUM + flashnum, 40, DFLASH_PARAM40);
//	DFlash_Write_Int(SECTOR_NUM + flashnum, 41, DFLASH_PARAM41);
//	DFlash_Write_Int(SECTOR_NUM + flashnum, 42, DFLASH_PARAM42);
//	DFlash_Write_Int(SECTOR_NUM + flashnum, 43, DFLASH_PARAM43);
//	DFlash_Write_Int(SECTOR_NUM + flashnum, 44, DFLASH_PARAM44);
//	DFlash_Write_Float(SECTOR_NUM + flashnum, 45, DFLASH_PARAM45);
//	DFlash_Write_Int(SECTOR_NUM + flashnum, 46, DFLASH_PARAM46);
//	DFlash_Write_Int(SECTOR_NUM + flashnum, 47, DFLASH_PARAM47);
//	DFlash_Write_Int(SECTOR_NUM + flashnum, 48, DFLASH_PARAM48);
//	DFlash_Write_Int(SECTOR_NUM + flashnum, 49, DFLASH_PARAM49);
//	DFlash_Write_Int(SECTOR_NUM + flashnum, 50, DFLASH_PARAM50);
//	DFlash_Write_Int(SECTOR_NUM + flashnum, 51, DFLASH_PARAM51);
//	DFlash_Write_Int(SECTOR_NUM + flashnum, 52, DFLASH_PARAM52);
//	DFlash_Write_Int(SECTOR_NUM + flashnum, 53, DFLASH_PARAM53);
//	DFlash_Write_Int(SECTOR_NUM + flashnum, 54, DFLASH_PARAM54);
//	DFlash_Write_Int(SECTOR_NUM + flashnum, 55, DFLASH_PARAM55);
//	DFlash_Write_Int(SECTOR_NUM + flashnum, 56, DFLASH_PARAM56);
//	DFlash_Write_Int(SECTOR_NUM + flashnum, 57, DFLASH_PARAM57);
//	DFlash_Write_Int(SECTOR_NUM + flashnum, 58, DFLASH_PARAM58);
//	DFlash_Write_Int(SECTOR_NUM + flashnum, 59, DFLASH_PARAM59);

	/********** 以上为存储的数据 **********/
#ifdef _USE_LCD
	LCD_DispChar(0, 0, '*');
#else
	OLED_Write_Char(0, 0, '*');
#endif
}
void MyFlash_Read(signed int flashnum)
{
	int FirstStart = 0;
	FirstStart = DFlash_Read_Int(SECTOR_NUM + flashnum, 0);
	if (FirstStart == First_Time_Init)
	{
		/********** 以下为存储的数据 **********/




		DFLASH_PARAM1 = DFlash_Read_Float(SECTOR_NUM + flashnum, 1);
		DFLASH_PARAM2 = DFlash_Read_Float(SECTOR_NUM + flashnum, 2);
		DFLASH_PARAM3 = DFlash_Read_Float(SECTOR_NUM + flashnum, 3);
		DFLASH_PARAM4 = DFlash_Read_Float(SECTOR_NUM + flashnum, 4);
		DFLASH_PARAM5 = DFlash_Read_Float(SECTOR_NUM + flashnum, 5);
		DFLASH_PARAM6 = DFlash_Read_Float(SECTOR_NUM + flashnum, 6);
		DFLASH_PARAM7 = DFlash_Read_Int(SECTOR_NUM + flashnum, 7);
		DFLASH_PARAM8 = DFlash_Read_Int(SECTOR_NUM + flashnum, 8);
		DFLASH_PARAM9 = DFlash_Read_Int(SECTOR_NUM + flashnum, 9);
		DFLASH_PARAM10 = DFlash_Read_Int(SECTOR_NUM + flashnum, 10);
		DFLASH_PARAM11 = DFlash_Read_Float(SECTOR_NUM + flashnum, 11);
		DFLASH_PARAM12 = DFlash_Read_Float(SECTOR_NUM + flashnum, 12);
		DFLASH_PARAM13 = DFlash_Read_Float(SECTOR_NUM + flashnum, 13);
		DFLASH_PARAM14 = DFlash_Read_Int(SECTOR_NUM + flashnum, 14);
		DFLASH_PARAM15 = DFlash_Read_Float(SECTOR_NUM + flashnum, 15);
		DFLASH_PARAM16 = DFlash_Read_Float(SECTOR_NUM + flashnum, 16);
		DFLASH_PARAM17 = DFlash_Read_Float(SECTOR_NUM + flashnum, 17);
		DFLASH_PARAM18 = DFlash_Read_Float(SECTOR_NUM + flashnum, 18);
		DFLASH_PARAM19 = DFlash_Read_Int(SECTOR_NUM + flashnum, 19);
		DFLASH_PARAM20 = DFlash_Read_Int(SECTOR_NUM + flashnum, 20);
		DFLASH_PARAM21 = DFlash_Read_Int(SECTOR_NUM + flashnum, 21);
		DFLASH_PARAM22 = DFlash_Read_Int(SECTOR_NUM + flashnum, 22);
		DFLASH_PARAM23 = DFlash_Read_Float(SECTOR_NUM + flashnum, 23);
		DFLASH_PARAM24 = DFlash_Read_Int(SECTOR_NUM + flashnum, 24);
		DFLASH_PARAM25 = DFlash_Read_Int(SECTOR_NUM + flashnum, 25);
		DFLASH_PARAM26 = DFlash_Read_Int(SECTOR_NUM + flashnum, 26);
		DFLASH_PARAM27 = DFlash_Read_Int(SECTOR_NUM + flashnum, 27);
		DFLASH_PARAM28 = DFlash_Read_Int(SECTOR_NUM + flashnum, 28);
		DFLASH_PARAM29 = DFlash_Read_Float(SECTOR_NUM + flashnum, 29);
		DFLASH_PARAM30 = DFlash_Read_Float(SECTOR_NUM + flashnum, 30);
		DFLASH_PARAM31 = DFlash_Read_Float(SECTOR_NUM + flashnum, 31);
//		DFLASH_PARAM32 = DFlash_Read_Float(SECTOR_NUM + flashnum, 32);
//		DFLASH_PARAM33 = DFlash_Read_Float(SECTOR_NUM + flashnum, 33);
//		DFLASH_PARAM34 = DFlash_Read_Float(SECTOR_NUM + flashnum, 34);
//		DFLASH_PARAM35 = DFlash_Read_Float(SECTOR_NUM + flashnum, 35);
//		DFLASH_PARAM36 = DFlash_Read_Float(SECTOR_NUM + flashnum, 36);
//		DFLASH_PARAM37 = DFlash_Read_Float(SECTOR_NUM + flashnum, 37);
//		DFLASH_PARAM38 = DFlash_Read_Float(SECTOR_NUM + flashnum, 38);
//		DFLASH_PARAM39 = DFlash_Read_Float(SECTOR_NUM + flashnum, 39);
//		DFLASH_PARAM40 = DFlash_Read_Int(SECTOR_NUM + flashnum, 40);
//		DFLASH_PARAM41 = DFlash_Read_Int(SECTOR_NUM + flashnum, 41);
//		DFLASH_PARAM42 = DFlash_Read_Int(SECTOR_NUM + flashnum, 42);
//		DFLASH_PARAM43 = DFlash_Read_Int(SECTOR_NUM + flashnum, 43);
//		DFLASH_PARAM44 = DFlash_Read_Int(SECTOR_NUM + flashnum, 44);
//		DFLASH_PARAM45 = DFlash_Read_Float(SECTOR_NUM + flashnum, 45);
//		DFLASH_PARAM46 = DFlash_Read_Int(SECTOR_NUM + flashnum, 46);
//		DFLASH_PARAM47 = DFlash_Read_Int(SECTOR_NUM + flashnum, 47);
//		DFLASH_PARAM48 = DFlash_Read_Int(SECTOR_NUM + flashnum, 48);
//		DFLASH_PARAM49 = DFlash_Read_Int(SECTOR_NUM + flashnum, 49);
//		DFLASH_PARAM50 = DFlash_Read_Int(SECTOR_NUM + flashnum, 50);
//		DFLASH_PARAM51 = DFlash_Read_Int(SECTOR_NUM + flashnum, 51);
//		DFLASH_PARAM52 = DFlash_Read_Int(SECTOR_NUM + flashnum, 52);
//		DFLASH_PARAM53 = DFlash_Read_Int(SECTOR_NUM + flashnum, 53);
//		DFLASH_PARAM54 = DFlash_Read_Int(SECTOR_NUM + flashnum, 54);
//		DFLASH_PARAM55 = DFlash_Read_Int(SECTOR_NUM + flashnum, 55);
//		DFLASH_PARAM56 = DFlash_Read_Int(SECTOR_NUM + flashnum, 56);
//		DFLASH_PARAM57 = DFlash_Read_Int(SECTOR_NUM + flashnum, 57);
//		DFLASH_PARAM58 = DFlash_Read_Int(SECTOR_NUM + flashnum, 58);
//		DFLASH_PARAM59 = DFlash_Read_Int(SECTOR_NUM + flashnum, 59);



		/********** 以上为存储的数据 **********/

	}

}