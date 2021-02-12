#ifndef __GLOBALVAR_H__
#define __GLOBALVAR_H__

#include <Menu.h>
#include <math.h>

extern int temp;
extern int motor;
extern int Point1r;
extern int Point1c;
extern int Point2r;
extern int Point2c;
extern int Point3r;
extern int Point3c;
extern int Point4r;
extern int Point4c;

extern unsigned char SendFlag;
extern unsigned char ReceiveFlag;
extern int distance;
extern int SingleFlag;
//***********���Ե���**********//
extern float YawAngle;             //ƫ����
extern float YawAngle_exp;         //����ƫ����
extern float YawError;
extern float YawError_before;
extern float SteerP_Nav;
extern float SteerD_Nav;
extern int Navagition_Dir;                 //0�����⣬1��2��
extern int GarageLength;                  //���Ե����������
extern int StopDis;                       //���Ե���ͣ������
extern float PitAngle;


//==========================Ԫ�ؼ�������============================//

extern unsigned char CircleDir[10];
extern unsigned char Ind_CircleOpen;	//����жϻ�������

//==========================ͼ��궨��============================//
#define LEFT_EAGE 0			//ͼ����߽�
#define RIGHT_EAGE 187		//ͼ���ұ߽�
#define MIDDLE 94			//ͼ����ֵ
//#define UP_EAGE 25			//ͼ���ϱ߽�
extern int UP_EAGE;
#define DOWN_EAGE 70		//ͼ���±߽�
#define IMG_ROW 120			//ͼ������
#define IMG_COL 188			//ͼ������
//#define FIND_LEFT 0
//#define FIND_RIGHT 1

#define MAX(x, y) ((x) > (y)) ? (x) : (y)
#define MIN(x, y) ((x) < (y)) ? (x) : (y)

#define FINDLINE_TH 7		//������ֵ
#define IN_OFFSET 2 //����ƫ��
//#define OUT_OFFSET 6 //����ƫ��
#define CIRCLEUP_TH 15		//���뻷�������

#define CIRCLE 2			//��������
#define RAMP 1				//�µ�����
#define STOPLINE 1			//ͣ������
#define STOPEND 1			//ͣ������
#define CI_IND 1			//��������־
#define INF 0				//����ʶ��

typedef struct
{
	int Row;
	int Col;
}Point;


typedef struct
{
	int Type;               //0��ͨ��� 1���� 2���� 3�յ� 4�ϱ߽� 5��߽� 6�ұ߽� 7���ж��� 8��4��ʮ�ֲ��� 9����ѭ��
	int ErrRow; 
	int ErrCol;
}SpecialPoint;

enum CircleType
{
	CN, CL, CR
};

enum EageType
{
	NO, HIGH_TH, LOW_TH
};

//==========================ͼ�����==============================//
extern float Prevalue[16];

extern const int MidOffset[];
extern const float ErrorOffset[];
extern unsigned char ImageEage[IMG_ROW][IMG_COL];
extern int ML[IMG_ROW];
extern int LL[IMG_ROW];
extern int RL[IMG_ROW];
extern int ML_Count;									//������Ч��
extern SpecialPoint LeftPnt, RightPnt;					//���������������Ϣ
extern int LightThreshold;						//ȥ�߹�������ֵ
extern int LightThreshold2;						//ȥ�߹�������ֵ2
extern int BrightThreshold;                       //����ֵ���µ���
extern int FindLineType;							//�Ƿ����߹��˲���־
extern int g_RoadType;
extern int ErrorFlag;								//�����־λ
extern int LastMiddleLine;							//������֡����
extern int SpeedRow;			//���ٱ߽�����

extern int ConstLeftEage;		//��������趨����
extern int ConstRightEage;		//�ұ������趨����

extern int InCircleState;		//������ͼ״̬
extern int CircleFlag;
extern int CircleState;

extern int CircleFlagSet;
extern int InCircleSize;		//��С����˳��

extern float L_CircleEntrance1;		//������߽���ڱ�־��1/2��
extern float R_CircleEntrance1;		//�����ұ߽���ڱ�־��1/2��
extern float L_CircleEntrance2;		//������߽���ڱ�־��1/2��
extern float R_CircleEntrance2;		//�����ұ߽���ڱ�־��1/2��
extern float L_CircleDelta;		//������߽���ڱ�־��1/2��
extern float R_CircleDelta;		//�����ұ߽���ڱ�־��1/2��


extern unsigned char Dist_ClearSevenFlag;
extern int Dist_Circle56;
extern int Dist_Circle35;

extern int LeftIntLine;		//��¼����������
extern int RightIntLine;		//��¼����������

extern int Img_SpecialElemFlag;    //����Ԫ�ر�־
extern int Img_StopLineFlag;		//ͣ���߱�־
extern int StopLineThreshold;		//ͣ�����ж�������ֵ
extern int StopMaxRow;				//ͣ���������
extern int StopMinRow;				//ͣ������С��
extern int Stop_UpRow;                        //��ͣ������ʼ��
extern int StopRow;                           //��ʼ���ת���λ��
extern int Img_GarageFlag;			//ͣ�����־
extern int Img_StopFlag;			//ͣ����־
extern int Garage_L;				//�����ߴ���벿�����ص�ĺ�
extern int Garage_R;				//�����ߴ��Ұ벿�����ص�ĺ�
extern int Img_RampFlag;			//�µ���־
extern int From;


extern unsigned char Img_CircleOpen;
extern unsigned char Img_StopOpen;
extern unsigned char Img_RampOpen;

void VarInit(void);

//==========================����ͷӲ������=================================//
#define ROW             120             //ԭʼͼ��������������              
#define COL             188             //ԭʼͼ�������������� 
#define ONE_METER		5800			//������һ��
extern unsigned char image[ROW][COL];
extern unsigned char g_Img_All_120x188[ROW][COL];
extern const unsigned char g_Bit_Val_Up[8];
extern const unsigned char g_Bit_Val_Down[8];
extern int exp_time;						//�ع�ʱ��
extern int HighThreshold;						//canny����ֵ
extern int LowThreshold;						//canny����ֵ
extern int ControlMid;						//ͼ�������ֵ

//extern int RoadType;
//extern int ErrorFlag;
//extern int MaxSpeedFlag;

//==========================�˵���־=================================//
#define InitSteer 995              //�����ʼֵ 75Hz 1149 50Hz 995,1052
#define SteerCorner 110              //��������,110,100

extern int g_car_lanuch;			//����������־
extern int g_drive_flag;                //�������
extern int g_ad_flag;                   //��п���
extern int g_steer_open;                //�������
extern int g_handle_open;               //��ͼ����
extern int g_ramp_open;            //�µ����ر�־
extern int g_garage_open;          //���⿪�ر�־

extern int g_camera_open;
extern int g_ind_open;
extern int g_camera_ctrl_flag;
extern int g_ind_ctrl_flag;
extern int g_broken_enable;

extern int BugFlag;

//=================================�������======================================//
extern int MaxSteerDuty5;  //����״̬5������ֵ
extern int SteerDutySet;
extern int Error_1;
extern int Error_2;
extern float Steer_P;
extern float Steer_P2;
extern float Steer_P_CI;
extern float Steer_P_Ramp;              //�µ�p
extern float p_max;
extern float p_min;
extern float p_long;
extern float d_max;
extern float Steer_D;
extern float Steer_D1;                  //����
extern float Steer_D2;                  //����
extern int ProSpect;
extern int SteerDuty;
extern float long_steer_p;
extern float long_steer_d;

extern float Steer_P_Ind;
extern float Steer_D_Ind;
extern float p_max_Ind;
extern float p_min_Ind;
extern float p_LongRoad_Ind;
extern unsigned char Ind_LongRoadFlag;

//=====================================���===================================//
#define MAXIND 4000
#define MININD 20

extern int ind_left, ind_right, ind_mid, ind_leftcol, ind_rightcol;	//��¼���
extern int ind_leftmax, ind_leftmin, ind_rightmax, ind_rightmin, ind_midmax, ind_midmin; 	//�����ֵ
extern int ind_leftcolmax, ind_leftcolmin, ind_rightcolmax, ind_rightcolmin;
extern float left_norm, right_norm, mid_norm, leftcol_norm, rightcol_norm;
extern float ad_error_1, ad_error_2;
extern int mul_ad_error;         //���error�Ŵ���
extern int ind_ci_th;			//����жϻ����Ӿ�
extern float Ind_CI_TH;			//���Բ���е���о�

extern int CircleCount;                    //����������1/2��3
extern int AD_CircleFlag;                  //����뻷����־
extern float MidAD;
/*=====================================����ʽ�ٶȿ���========================================*/
extern int KDet;
extern float In_kdet;

//�������޷�
#define SPEED_OUT_MAX  9999  //��ת���
#define SPEED_OUT_MIN -9999  //��ת���


extern int g_steer_error; //���ƫ��

typedef struct
{
	float error_1;//ƫ��
	float error_2;
	float error_3;
	int d_duty; //���ƫ����
	float p;
	float i;
	float d;
}SPEED;

extern int speed_type;

extern float curSpeed;
extern int lCurSpeed;
extern int rCurSpeed;
extern SPEED leftDrv;
extern SPEED rightDrv;
//�����ٶ�
extern int spdExp;
extern const int spdExp0;
extern int spdExp1;
extern int spdExp2;
extern int spdExp3;
extern int spdExp4;
extern int spdExp5;		//·���ٶ�
extern int spdBas1;		//ƽ�ܻ�׼�ٶ�
extern int spdBas2;		//�ᳵ��׼�ٶ�
extern int spdBas3;
extern float leftExpect; //���������ٶ�
extern float rightExpect;//���������ٶ�

extern signed int leftSpeedOut; //�����ٶ����
extern signed int rightSpeedOut;//�����ٶ����
//�ٶȿ���pi
extern float g_speed_p;
extern float g_speed_i;
extern float g_speed_d;
extern float speederror;
extern float ramp_speed_p;       //�µ�p
extern float ramp_speed_i;        //�µ�i

//extern int s4;
//extern int s5;
//extern int s6;
//extern int s7;

extern int d_spd_max;
extern int d_spd_high;
extern int d_spd_mid;
extern int d_spd_min;

extern int s_width;
extern int m_width;
extern int l_width;

//==================================ɲ��=================//
extern int g_stop_line;
extern int g_stop_dis;
extern int times_go;
extern int times_stop;
extern int rount;          //Ȧ��
extern int DistantStop;

//*****************TF������*******************
#define GATHER_DATA_KIND    10                          //�ɼ��ı�������

extern unsigned int g_SD_Gather_Data[GATHER_DATA_KIND]; //�ɼ�������
extern unsigned char g_Img_All_128x320[128 * 160];        //SD��������ͼ����
extern unsigned char g_Img_All_240x320[240 * 160];        //SD��������ͼ����
extern unsigned char g_Img_All_60x80[60 * 40];


/*=====================================���뿪��========================================*/
extern int dialSwitchFlg1;
extern int dialSwitchFlg2;
extern int dialSwitchFlg3;
extern int dialSwitchFlg4;
extern int dialSwitchcal;
//extern signed int DialSwitchFlag1;            //���뿪��1
//extern signed int DialSwitchFlag2;            //���뿪��2
//extern signed int DialSwitchFlag3;            //���뿪��3
//extern signed int DialSwitchFlag4;        
#define DIALSWITCH_PIN1 E8
#define DIALSWITCH_PIN2 E6
#define DIALSWITCH_PIN3 E7
#define DIALSWITCH_PIN4 E9
/*===================================˫��ͨѶ��=========================================*/
typedef struct
{
	signed char infotype;// 1.      0������� 1�����־λ
	char begin;           // 4.      ͨ������
	char state;           // 5-8.      
}btInfo;

extern signed char btMessage;

extern signed char btRcvMessage;

extern btInfo btSndInfo, btRcvInfo;

/*=====================================˫��״̬======================================*/
enum MeetingState {
	Ready, WaitingBegin, CarGo,
	StateOne = 4, StateTwo, StateThree, StateFour, StateFive, StateSix, StateSeven,
	WaitingStop = 11, IsStopLine, StateGo, StateStop, CarFinish
};

//extern unsigned char g_GetMeetingMaster;            //��������ᳵ����־
//extern unsigned char g_GetMeetingSlave;             //�ӳ�����ᳵ����־
//extern unsigned char g_MeetingCtrlFlag;             //�ᳵ״̬�������Ʊ�־
//extern unsigned char g_MeetingCtrlEndFlag;             //�ᳵ״̬�������ƽ�����־
//extern unsigned char g_EndMeetingMaster;           //���������ᳵ��־
extern unsigned char g_MasterOutFlag;              //��������
extern unsigned char g_SlaveOutFlag;               //�ӳ�����
extern unsigned char g_StateMaster;
extern unsigned char g_StateSlave;
extern unsigned char g_MeetingMode;
extern unsigned char g_MeetingDir;			//ת���� 2Ϊ��ת 1Ϊ��ת
extern unsigned char g_GetMeetingFlag;
extern unsigned char g_GetMeetingState;

/*====================================�ᳵ���ߵ�����=====================================*/
extern int sum_distance_1;
extern int sum_distance_2;
extern int sum_distance_3;

/*====================================�µ�=====================================*/

/*=====================================�����Ǳ���======================================*/
extern signed int I2C_Wait_Times;        //i2c�ȴ�����
extern signed int I2C_Wait_Err_Flg;      //i2c�ȴ���ѭ�������־

extern float g_gyroBalance;           //������ƽ��ֵ
extern float g_gyroIntegration;             //�����ǻ�����

extern int g_gyroDimension;               //������ת�����ٶȼ�����

extern float g_angleResult;                 //�Ƕȼ�����
extern float g_angleResult_last;
extern float g_angle_temp;

extern int g_gyroGet;                     //�����Ƕ�ȡֵ
extern signed int g_gyroGet_max;
extern signed int g_gyroGet_min;
extern int g_gyro_jolt;
extern int g_jolt_flag;

extern signed int gyroClearRamp;         //�����Ǽ�����µ���־

extern int g_gyro_cnt;//�µ�


extern int g_ramp_judge;

///*=====================================pwm����========================================*/
//extern int Left_Pwm;
//extern int Left_Pwm2;
//extern int Right_Pwm;
//extern int Right_Pwm2;
///*=====================================�ٶȿ���========================================*/
//
//extern int opposite_ready,opposite_wait,opposite_done;
//extern int KDet;
//
////�������޷�
//#define SPEED_OUT_MAX  9999  //��ת���
//#define SPEED_OUT_MIN -9999  //��ת���
//#define IOUT_MAX       9500  //�������
//#define IOUT_MIN      -6000  //������С
//
//
//
//extern int g_steer_error; //���ƫ��
//
//typedef struct
//{
//    float error;//ƫ��
//    float iError;//ƫ�������
//    float iOut;//���������
//    
//     float p;
//     float i;
//}SPEED;
//
//
//extern float curSpeed;
//extern int lCurSpeed;
//extern int rCurSpeed;
//extern int sidetype;//��������
//extern SPEED leftDrv;
//extern SPEED rightDrv;
////�����ٶ�
//extern int spdExp;
//extern int spdExp0;
//extern int spdExp1;
//extern int spdExp2;
//extern int spdExp3;
//extern int spdExp4;
//extern float leftExpect; //���������ٶ�
//extern float rightExpect;//���������ٶ�
//
//extern signed int leftSpeedOut; //�����ٶ����
//extern signed int rightSpeedOut;//�����ٶ����
////�ٶȿ���pi
//extern float g_speed_p;
//extern float g_speed_i;
//
//extern signed int lOverflowFlg;//�������޷�����������־
//extern signed int rOverflowFlg;//�������޷�����������־
////extern int s4;
////extern int s5;
////extern int s6;
////extern int s7;
//
//extern int d_spd_max;
//extern int d_spd_high;
//extern int d_spd_mid;
//extern int d_spd_low;
//
//extern int s_width;
//extern int m_width;
//extern int l_width;





////==========================Ӳ��������============================//
//
//extern float EncoderCount;		//��������ֵ
//extern signed int DialSwitchFlag1;            //���뿪��1
//extern signed int DialSwitchFlag2;            //���뿪��2
//extern signed int DialSwitchFlag3;            //���뿪��3
//extern signed int DialSwitchFlag4;        
//#define DIALSWITCH_PIN1 E6
//#define DIALSWITCH_PIN2 E7
//#define DIALSWITCH_PIN3 E8
//#define DIALSWITCH_PIN4 E9
//
//
//
////==========================���������============================//
//extern float SteeringMin;			//�����Сֵ
//extern float SteeringMid;			//�����ֵ
//extern float SteeringMax;			//������ֵ
//extern float SteerPWMOut;			//������ֵ
//
//extern float SteeringCtrlP ;			//������Ʋ���P
//extern float SteeringCtrlDi ;			//��������������
//extern float SteeringCtrlDo ;		//������Ƴ������D
//
//
//extern float SteeringCtrlP_universe ;			//������Ʋ���P
//extern float SteeringCtrlDi_universe ;			//��������������
//extern float SteeringCtrlDo_universe ;		//������Ƴ������D
//
//
//
//extern float SteeringCtrlP_circle;			//������Ʋ���P
//extern float SteeringCtrlDi_circle ;			//��������������
//extern float SteeringCtrlDo_circle ;		//������Ƴ������D
//
//extern float SteerStartDist;	//ƫ���ȡ����ױ���ʼ����
//extern float SteerStartDist_universe ;			//ƫ���ȡ����ױ���ʼ����
//
//extern float SteerEndDist;		//ƫ���ȡ����ױ���ֹ����
//extern float SteerEndDist_circle ;			//ƫ���ȡ����ױ���ֹ����
//extern float High_pass_paramentA;     //ƫ���ͨϵ��
//extern float High_pass_paramentB;     //ƫ���ͨϵ��
//
//extern float  Compensate;      //ƫ���ϵ��
//
//
///*=====================================�ٶȿ���========================================*/
//extern int g_drive_flag;
//extern int g_stop;
//extern int g_distance_count;
//extern float g_distance_k; 
//extern int g_state,g_state_opposite,g_single_enable;
//extern int g_protect_enable;
//extern int lock_count;
//#define ONE_METER      5350
////�������޷�
//#define SPEED_OUT_MAX  9999  //��ת���
//#define SPEED_OUT_MIN -9999  //��ת���
//#define IOUT_MAX       9500  //�������
//#define IOUT_MIN      -6000  //������С
//typedef struct
//{
//    int error;//ƫ��
//    int iError;//ƫ�������
//    int iOut;//���������
//    
//    float p;
//    float i;
//    float d;
//    
//    int pre_error;
//    int pre_derror;
//}SPEED;
//
//extern float curSpeed;
//extern int lCurSpeed;
//extern int rCurSpeed;
//extern int sidetype;//��������
//extern SPEED leftDrv;
//extern SPEED rightDrv;
//extern int KDet;
//extern int g_speed_type;
//
//extern int car_start_flag;
////�����ٶ�
//extern int spdExp;
//extern int spdExp0;
//extern int spdExp1;
//extern int spdExp2;
//extern int spdExp3;
//extern int spdExp4;
//extern int spdExp5;
//extern float leftExpect; //���������ٶ�
//extern float rightExpect;//���������ٶ�
//
//extern signed int leftSpeedOut; //�����ٶ����
//extern signed int rightSpeedOut;//�����ٶ����
////�ٶȿ���pi
//extern float g_speed_p;
//extern float g_speed_i;
//extern float g_speed_d;
//
//extern signed int lOverflowFlg;//�������޷�����������־
//extern signed int rOverflowFlg;//�������޷�����������־
//
//
//
//
//
//extern int error;
//extern int error_max;
//extern int error_cnt;
//extern int error_cnt_max;
//extern int last_error;
//extern int g_steer_duty;
//extern float g_p;
//extern float g_d;
//
//
//
//extern int second;
//extern int pit2_cnt;
////==========================�µ�����============================//
//extern unsigned char g_Ramp_Flg ;//�µ����ȷ�ϱ�־
//extern float g_Angle_Result ; //�Ƕȼ�����
//extern float g_Angle_threshold;        //����ʶ����ֵ
//extern float g_Gyro_Balance ;               //������ƽ��ֵ
//extern float g_Gyto_integration ;               //�����ǻ�����
//extern float g_Gyro_Dimension ;                //������ת�����ٶȼ�����
//extern signed int g_Gyro_Get ;                  //�����Ƕ�ȡֵ
//extern signed int Ramp_time;                  //�µ����ʱ��
////==========================����·�����============================//
//extern float Jolt_Open;            //����·��ʶ������־
//extern signed int Jolt_Get;            //����������ٶ�
//extern signed int Jolt_Get_min;            //����������ٶ���Сֵ
//extern signed int Jolt_Get_max;            //����������ٶ����ֵ
//extern signed int Jolt_Get_delta;            //����������ٶȼ���
//extern float Jolt_delta;             //����ʶ����ֵ
//extern signed int Jolt_Balance;      //����������ٶ�ƽ��ֵ
//extern unsigned char Jolt_Flag;        //������־λ
//extern float Jolt_Down_Speed;           //����·���½��ٶ�
//extern float Jolt_time;            //����·��ʱ�䣺����



#endif