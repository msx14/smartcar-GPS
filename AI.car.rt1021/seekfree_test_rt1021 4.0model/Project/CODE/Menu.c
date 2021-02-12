#include  "headfile.h"
#include  "Menu.h"
#include  "common.h"

#if _USE_LCD
#define LINE_MAX 8
#elif _USE_IPS
#define LINE_MAX 8
#else
#define LINE_MAX 4                                           //һҳ����ʾ�������� OLEDΪ4 LCD����Ϊ8 ����Ϊ10
#endif

signed char g_pageNum = 1;                                   //��ǰ����ҳ
signed char g_lineNum = 1;                                   //��ǰ������
signed char g_pageCount = 0;
signed char g_lineCount = 0;
signed char g_pageMax = 0;								     //ҳ������
signed char g_lineMax = 0;                                   //��ǰҳ�����ĸ���

signed char g_lineLock = 0;                                  //������־

signed char g_plusFlg = 0;                                   //�ӷ���־
signed char g_minisFlg = 0;                                  //������־
signed char g_imgFlg = 0;

signed char g_Rate = 0;                                      //����ָ�� ����Ӽ�
float g_addValue = 1;                                        //����
//signed char g_picture_show = 0;
//signed char g_explore_page = 0;								//�����ع⹦��ҳ

unsigned char Cursor[][16] =

{
#if _USE_LCD || _USE_IPS
	{0x00,0x00,0x00,0x02,0x04,0x08,0x10,0x20,0x40,0x20,0x10,0x08,0x04,0x02,0x00,0x00},//>
	{0x00,0x00,0x00,0x05,0x0A,0x14,0x28,0x50,0xA0,0x50,0x28,0x14,0x0A,0x05,0x00,0x00}//��
#else
	{0x00,0x08,0x10,0x20,0x40,0x80,0x00,0x00,0x00,0x20,0x10,0x08,0x04,0x02,0x01,0x00},//>
	{0x10,0x20,0x40,0x90,0x20,0x40,0x80,0x00,0x10,0x08,0x04,0x12,0x09,0x04,0x02,0x01}//��
#endif
};
//*
//*  @brief:		���˵�
//*  @param:		void
//*  @return:	    void
//*
void Menu(void)
{
	g_Key = Key_Check();
	Key_Function();

	Main_Show();
	Extra_Show();
}

void FlagChange(int* flag)
{
	if (1 == *flag)
	{
		*flag = 0;
		return;
	}
	else if (0 == *flag)
	{
		*flag = 1;
		return;
	}
}

//*
//*  @brief:	���
//*  @param:	void
//*  @return:   void
//*
void Dis_Cursor(unsigned char Position, signed char Number)
{
#if _USE_LCD
	lcd_set_region(0, 16 * Position, 7, 16 * Position + 15);
	uint8 i, j;
	uint8 temp;
	for (i = 0; i < 16; i++)
	{
		//		Lcd_SetRegion(x,y+i,x+7,y+i);
		temp = Cursor[Number][i];
		for (j = 0; j < 8; j++)
		{
			if (temp & 0x01)	lcd_writedata_16bit(PENCOLOR);
			else			lcd_writedata_16bit(BGCOLOR);
			temp >>= 1;
		}
	}
#elif _USE_IPS
	ips_set_region(0, 16 * Position, 7, 16 * Position + 15);
	uint8 i, j;
	uint8 temp;
	for (i = 0; i < 16; i++)
	{
		temp = Cursor[Number][i];
		for (j = 0; j < 8; j++)
		{
			if (temp & 0x01) ips_writedata_16bit(IPS_PENCOLOR);
			else ips_writedata_16bit(IPS_BGCOLOR);
			temp >>= 1;
		}
	}
#else
	OLED_Set_Pos(0, 2 * Position);
	for (unsigned char i = 0; i < 8; i++)
		OLED_Write_Data(Cursor[Number][i]);
	OLED_Set_Pos(0, 2 * Position + 1);
	for (unsigned char i = 0; i < 8; i++)
		OLED_Write_Data(Cursor[Number][i + 8]);
#endif
}

//*
//*  @brief:		����ҳ
//*  @param:		void
//*  @return:	    void
//*
void PageNumReduce(void)
{
#if _USE_LCD
	lcd_clear(BGCOLOR);
#elif _USE_IPS
	ips_clear(IPS_BGCOLOR);
#else
	OLED_Clear();
#endif
	g_pageNum--;
	if (g_pageNum < 1) g_pageNum = g_pageMax;
	g_lineNum = 1;
}

//*
//*  @brief:		���ҷ�ҳ
//*  @param:		void
//*  @return:	    void
//*
void PageNumAdd(void)
{
#if _USE_LCD
	lcd_clear(BGCOLOR);
#elif _USE_IPS
	ips_clear(IPS_BGCOLOR);
#else
	OLED_Clear();
#endif
	g_pageNum++;
	if (g_pageNum > g_pageMax) g_pageNum = 1;
	g_lineNum = 1;
}

//*
//*  @brief:		��������
//*  @param:		void
//*  @return:	    void
//*
void LineNumReduce(void)
{
	g_lineNum--;
	if (g_lineNum < 1) g_lineNum = g_lineMax;
}

//*
//*  @brief:		��������
//*  @param:		void
//*  @return:	    void
//*
void LineNumAdd(void)
{
	g_lineNum++;
	if (g_lineNum > g_lineMax) g_lineNum = 1;
}


void GotoGivenPage(void)
{
	OLED_Clear();

	g_pageNum = GIVEN_PAGE;
	g_lineLock = 0;
	g_lineNum = 1;
}

//*
//*  @brief:		����һ��ҳ��
//*  @param:		��Ҫ��ʾ�ı��⣬������Ҫ��ʾ����ʱ�ַ���д"\0"
//*  @return:	    void
//*  @note:     
//*
void Insert_Page(signed char String[])
{
	g_pageCount++;

	if (g_pageMax < g_pageCount) g_pageMax = g_pageCount;

	if (g_pageNum == g_pageCount)
	{
		g_imgFlg = 0;
		if (String != "\0")
		{
			Dis_Head(String);
		}
		g_lineMax = 0;
	}
	g_lineCount = 0;
}

//*
//*  @brief:		����һ��ͼ��
//*  @param:		�ڲ˵��е�λ�� ��Ҫ��ʾ�ı����Լ�ͼ����ʾ�ĺ�����������Ҫ��ʾ����ʱ�ַ���д"\0"
//*  @return:	    void
//*  @note:     
//*
void Insert_Img(signed char String[], void pfunc_show(void))
{
	g_pageCount++;

	if (g_pageMax < g_pageCount) g_pageMax = g_pageCount;

	if (g_pageNum == g_pageCount)
	{
		g_imgFlg = 1;
		if (String != "\0")
		{
			Dis_Head(String);
		}
		g_lineMax = 0;
	}
	g_lineCount = 0;

	if (g_pageNum == g_pageCount)pfunc_show();
}

//*
//*  @brief:		�����ַ�����
//*  @param:		�ڲ˵��е�λ�� ��Ҫ����ı������Լ������ĵ�ַ
//*  @return:	    void
//*  @note:     
//*
void Insert_Char(signed char String[], signed char* Number)
{
	char tmp_line;
	if (g_pageNum == g_pageCount)
	{
		g_lineCount++;
		if (g_lineMax < g_lineCount) g_lineMax = g_lineCount;

		if (g_lineNum < LINE_MAX)
		{
			tmp_line = g_lineCount;
			Dis_String(2 * tmp_line - 1, String);
			Dis_Int(2 * tmp_line, *Number);
		}
		else
		{
			if (g_lineNum >= g_lineCount)
			{
				tmp_line = LINE_MAX - 1 + g_lineCount - g_lineNum;
				Dis_String(2 * tmp_line - 1, String);
				Dis_Int(2 * tmp_line, *Number);
			}
		}

		if (g_lineNum == g_lineCount)
		{
			if (g_plusFlg)
			{
				*Number += (int)g_addValue;
				g_plusFlg = 0;
			}
			else if (g_minisFlg)
			{
				*Number -= (int)g_addValue;
				g_minisFlg = 0;
			}
		}
	}
}

//*
//*  @brief:		�������ͱ���
//*  @param:		�ڲ˵��е�λ�� ��Ҫ����ı������Լ������ĵ�ַ
//*  @return:	    void
//*  @note:     
//*
void Insert_Int(signed char String[], signed int* Number)
{
	char tmp_line;
	if (g_pageNum == g_pageCount)
	{
		g_lineCount++;
		if (g_lineMax < g_lineCount) g_lineMax = g_lineCount;

		if (g_lineNum < LINE_MAX)
		{
			tmp_line = g_lineCount;
			Dis_String(2 * tmp_line - 1, String);
			Dis_Int(2 * tmp_line, *Number);
		}
		else
		{
			if (g_lineNum >= g_lineCount)
			{
				tmp_line = LINE_MAX - 1 + g_lineCount - g_lineNum;
				Dis_String(2 * tmp_line - 1, String);
				Dis_Int(2 * tmp_line, *Number);
			}
		}

		if (g_lineNum == g_lineCount)
		{
			if (g_plusFlg)
			{
				*Number += (int)g_addValue;
				g_plusFlg = 0;
			}
			else if (g_minisFlg)
			{
				*Number -= (int)g_addValue;
				g_minisFlg = 0;
			}
		}
	}
}

//*
//*  @brief:		���븡���ͱ���
//*  @param:		�ڲ˵��е�λ��(0~127) ��Ҫ����ı������Լ������ĵ�ַ
//*  @return:	  void
//*
void Insert_Float(signed char String[], float* Number)
{
	char tmp_line;

	if (g_pageNum == g_pageCount)
	{
		g_lineCount++;
		if (g_lineMax < g_lineCount) g_lineMax = g_lineCount;

		if (g_lineNum < LINE_MAX)
		{
			tmp_line = g_lineCount;
			Dis_String(2 * tmp_line - 1, String);
			Dis_Float(2 * tmp_line, *Number);
		}
		else
		{
			if (g_lineNum >= g_lineCount)
			{
				tmp_line = LINE_MAX - 1 + g_lineCount - g_lineNum;
				Dis_String(2 * tmp_line - 1, String);
				Dis_Float(2 * tmp_line, *Number);
			}
		}

		if (g_lineNum == g_lineCount)
		{
			if (g_plusFlg)
			{
				*Number += g_addValue;
				g_plusFlg = 0;
			}
			else if (g_minisFlg)
			{
				*Number -= g_addValue;
				g_minisFlg = 0;
			}
		}
	}
}



//*
//*  @brief:		����volatile�����ͱ���
//*  @param:		�ڲ˵��е�λ��(0~127) ��Ҫ����ı������Լ������ĵ�ַ
//*  @return:	  void
//*
void Insert_VFloat(signed char String[], volatile float* Number)
{
	char tmp_line;

	if (g_pageNum == g_pageCount)
	{
		g_lineCount++;
		if (g_lineMax < g_lineCount) g_lineMax = g_lineCount;

		if (g_lineNum < LINE_MAX)
		{
			tmp_line = g_lineCount;
			Dis_String(2 * tmp_line - 1, String);
			Dis_Float(2 * tmp_line, *Number);
		}
		else
		{
			if (g_lineNum >= g_lineCount)
			{
				tmp_line = LINE_MAX - 1 + g_lineCount - g_lineNum;
				Dis_String(2 * tmp_line - 1, String);
				Dis_Float(2 * tmp_line, *Number);
			}
		}
		if (g_lineNum == g_lineCount)
		{
			if (g_plusFlg)
			{
				*Number += g_addValue;
				g_plusFlg = 0;
			}
			else if (g_minisFlg)
			{
				*Number -= g_addValue;
				g_minisFlg = 0;
			}
		}
	}
}



//*
//*  @brief:		��������
//*  @param:		void
//*  @return:	    void
//*  @note:    
//* 
void Key_Function(void)
{
	if (!g_lineLock)
	{
		switch (g_Key)
		{
		case 1:  stop_tiktok=0;global_judge=0;vc_flag=0;	break;
		case 2:		LineNumReduce();		break; //��������
		case 3:
#if _USE_LCD
			lcd_init();
#elif _USE_IPS
			ips_init();
#else
			OLED_Init();               //ˢ����Ļ
			lcd_init();
#endif
																	break;
		case 4:		PageNumReduce();		break; //���Ϸ�ҳ
		case 5:		g_lineLock = 1;			break;	//������ֵ�޸�
		case 6:  	PageNumAdd();				break;  //���·�ҳ
		case 7:												break;
		case 8:		LineNumAdd();				break;//��������
		case 9:		adc_read++;     		break;
		default:                 	    break;
		}
	}
	else
	{
		switch (g_Key)
		{
		case 1: stop_tiktok=0;global_judge=0;vc_flag=0;    break;    //д��FLASH
		case 2: LineNumReduce();    break;    //��������
		case 3: g_plusFlg = 1;      break;    //��ֵ��
		case 4: g_Rate--;           break;    //���ٱ���
		case 5: g_lineLock = 0;     break;    //�˳���ֵ�޸�
		case 6: g_Rate++;           break;    //���ӱ���
		case 7: exp_num++;          break;
		case 8: LineNumAdd();       break;    //��������
		case 9: g_minisFlg = 1;     break;    //��ֵ��
		default:                    break;
		}
	}
//	INTR_Keyboard_Init();
}


//*
//*  @brief:		��ʾ���ʺ͹��
//*  @param:		void
//*  @return:	  void
//*
void Extra_Show(void)
{
	if (!g_imgFlg)
	{
		switch (g_lineNum)
		{
#if _USE_LCD
		case 1:
			Dis_Cursor(1, g_lineLock);
			lcd_showchar(0, 2*16, ' ');
			lcd_showchar(0, 3*16, ' ');
			lcd_showchar(0, 4*16, ' ');
			lcd_showchar(0, 5*16, ' ');
			lcd_showchar(0, 6*16, ' ');
			lcd_showchar(0, 7*16, ' ');
			break;
		case 2:
			Dis_Cursor(2, g_lineLock);
			lcd_showchar(0, 1*16, ' ');
			lcd_showchar(0, 3*16, ' ');
			lcd_showchar(0, 4*16, ' ');
			lcd_showchar(0, 5*16, ' ');
			lcd_showchar(0, 6*16, ' ');
			lcd_showchar(0, 7*16, ' ');
			break;
		case 3:
			Dis_Cursor(3, g_lineLock);
			lcd_showchar(0, 1*16, ' ');
			lcd_showchar(0, 2*16, ' ');
			lcd_showchar(0, 4*16, ' ');
			lcd_showchar(0, 5*16, ' ');
			lcd_showchar(0, 6*16, ' ');
			lcd_showchar(0, 7*16, ' ');
			break;
		case 4:
			Dis_Cursor(4, g_lineLock);
			lcd_showchar(0, 2*16, ' ');
			lcd_showchar(0, 3*16, ' ');
			lcd_showchar(0, 1*16, ' ');
			lcd_showchar(0, 5*16, ' ');
			lcd_showchar(0, 6*16, ' ');
			lcd_showchar(0, 7*16, ' ');
			break;
		case 5:
			Dis_Cursor(5, g_lineLock);
			lcd_showchar(0, 2*16, ' ');
			lcd_showchar(0, 3*16, ' ');
			lcd_showchar(0, 4*16, ' ');
			lcd_showchar(0, 1*16, ' ');
			lcd_showchar(0, 6*16, ' ');
			lcd_showchar(0, 7*16, ' ');
			break;
		case 6:
			Dis_Cursor(6, g_lineLock);
			lcd_showchar(0, 2*16, ' ');
			lcd_showchar(0, 3*16, ' ');
			lcd_showchar(0, 4*16, ' ');
			lcd_showchar(0, 5*16, ' ');
			lcd_showchar(0, 1*16, ' ');
			lcd_showchar(0, 7*16, ' ');
			break;
		default:
			Dis_Cursor(7, g_lineLock);
			lcd_showchar(0, 2*16, ' ');
			lcd_showchar(0, 3*16, ' ');
			lcd_showchar(0, 4*16, ' ');
			lcd_showchar(0, 5*16, ' ');
			lcd_showchar(0, 6*16, ' ');
			lcd_showchar(0, 1*16, ' ');
			break;
#elif _USE_IPS
		case 1:
			Dis_Cursor(1, g_lineLock);
			IPS_DispString(0, 4, " ");
			IPS_DispString(0, 6, " ");
			IPS_DispString(0, 8, " ");
			IPS_DispString(0, 10, " ");
			IPS_DispString(0, 12, " ");
			IPS_DispString(0, 14, " ");
			break;
		case 2:
			Dis_Cursor(2, g_lineLock);
			IPS_DispString(0, 2, " ");
			IPS_DispString(0, 6, " ");
			IPS_DispString(0, 8, " ");
			IPS_DispString(0, 10, " ");
			IPS_DispString(0, 12, " ");
			IPS_DispString(0, 14, " ");
			break;
		case 3:
			Dis_Cursor(3, g_lineLock);
			IPS_DispString(0, 4, " ");
			IPS_DispString(0, 2, " ");
			IPS_DispString(0, 8, " ");
			IPS_DispString(0, 10, " ");
			IPS_DispString(0, 12, " ");
			IPS_DispString(0, 14, " ");
			break;
		case 4:
			Dis_Cursor(4, g_lineLock);
			IPS_DispString(0, 4, " ");
			IPS_DispString(0, 6, " ");
			IPS_DispString(0, 2, " ");
			IPS_DispString(0, 10, " ");
			IPS_DispString(0, 12, " ");
			IPS_DispString(0, 14, " ");
			break;
		case 5:
			Dis_Cursor(5, g_lineLock);
			IPS_DispString(0, 4, " ");
			IPS_DispString(0, 6, " ");
			IPS_DispString(0, 8, " ");
			IPS_DispString(0, 2, " ");
			IPS_DispString(0, 12, " ");
			IPS_DispString(0, 14, " ");
			break;
		case 6:
			Dis_Cursor(6, g_lineLock);
			IPS_DispString(0, 4, " ");
			IPS_DispString(0, 6, " ");
			IPS_DispString(0, 8, " ");
			IPS_DispString(0, 10, " ");
			IPS_DispString(0, 2, " ");
			IPS_DispString(0, 14, " ");
			break;
		default:
			Dis_Cursor(7, g_lineLock);
			IPS_DispString(0, 4, " ");
			IPS_DispString(0, 6, " ");
			IPS_DispString(0, 8, " ");
			IPS_DispString(0, 10, " ");
			IPS_DispString(0, 12, " ");
			IPS_DispString(0, 2, " ");
			break;
#else
		case 1:
			Dis_Cursor(1, g_lineLock);
			OLED_Write_String(4, 0, " ");
			OLED_Write_String(6, 0, " ");
			break;
		case 2:
			OLED_Write_String(2, 0, " ");
			Dis_Cursor(2, g_lineLock);
			OLED_Write_String(6, 0, " ");
			break;
		default:
			OLED_Write_String(2, 0, " ");
			OLED_Write_String(4, 0, " ");
			Dis_Cursor(3, g_lineLock);
			break;
#endif
		}
	}
	switch (g_Rate)
	{
	case -4: g_Rate = 3;                         break;
	case -3: g_addValue = 0.001;                 break;
	case -2: g_addValue = 0.01;                  break;
	case -1: g_addValue = 0.1;                   break;
	case 0: g_addValue = 1;                      break;
	case 1: g_addValue = 10;                     break;
	case 2: g_addValue = 100;                    break;
	case 3: g_addValue = 1000;                  break;
	case 4: g_Rate = -3;                         break;
	default: g_Rate = 0;                       break;
	}

#if _USE_LCD
	if (g_Rate >= 0)                                      //��ʾ����
	{
		LCD_DispChar(144, 0, ' ');
		OLED_Write_Int(0, 152, g_Rate);
	}
	else OLED_Write_Int(0, 144, g_Rate);
#elif _USE_IPS
	if (g_Rate >= 0)
	{
		IPS_DispChar(224, 0, ' ');
		OLED_Write_Int(0, 232, g_Rate);
	}
	else OLED_Write_Int(0, 224, g_Rate);
#else
	if (g_Rate >= 0)                                      //��ʾ����
	{
		OLED_Write_String(0, 112, " ");
		OLED_Write_Int(0, 120, g_Rate);
	}
	else OLED_Write_Int(0, 112, g_Rate);
#endif  
}


//*
//*  @brief:		�˵�������ʾ ����������ʾ��ͼ����ʾ
//*  @param:		void
//*  @return:	    void
//*
extern int speed_sum;
void Main_Show(void)
{
	g_pageCount = 0;			
	  	Insert_Page("1_Change");
				Insert_Int("C_v", &spdExp1);//����ٶ�
				Insert_Int("I_v", &spdExp2);//ֱ���ٶ�
				Insert_Int("flag",&g_convert_flag);//����ģʽ
				Insert_Int("adc",&adc_read);//���ģʽ
				Insert_Int("k",&KDet);							//����ϵ��	
				Insert_Int("v", &spdExp0);//����ٶ�
	
		Insert_Page("2_ADC");
			Insert_Float("LO_L",&LO_L);
			Insert_Float("LI_L",&LI_L);
			Insert_Float("M_L",&M_L);
			Insert_Float("RI_L",&RI_L);
			Insert_Float("RO_L",&RO_L);
			Insert_Float("R_L",&belly_R_L);
			Insert_Float("L_L",&belly_L_L);
			Insert_Float("LO_r1",&LO_L_r1);
			Insert_Float("LI_r1",&LI_L_r1);
			Insert_Float("M_r1",&M_L_r1);
			Insert_Float("RI_r1",&RI_L_r1);
			Insert_Float("RO_r1",&RO_L_r1);
			Insert_Float("R_L_r1",&belly_R_L_r1);
			Insert_Float("L_L_r1",&belly_L_L_r1);	
			
//			Insert_Page("R");
//				Insert_Int("LO",&W_LO);
//				Insert_Int("LI",&W_LI);
//				Insert_Int("M",&W_M);
//				Insert_Int("RI",&W_RI);
//				Insert_Int("RO",&W_RO);
//				Insert_Int("L",&W_belly_L);
//				Insert_Int("R",&W_belly_R);
			
		Insert_Page("3_short");
			Insert_Float("r_steer_p",&g_steer_p_right);//�����pid
			Insert_Float("r_steer_d",&g_steer_d_right);//�����pid
			Insert_Float("l_steer_p",&g_steer_p_left);//�����pid
			Insert_Float("l_steer_d",&g_steer_d_left);//�����pid			
}

