#ifndef __PINGMU_H
#define __PINGMU_H 

extern signed char Temp_List[128];
extern float Battery;
#define Cross 48
#define Row 128


/******************************************************/
/********************  ���ɽӿ�    ********************/
/******************************************************/


/*--------------------*��Ļͷ��ʾ*--------------------*/

void Dis_Head   (signed char String[]);
// �ڱ�����������ʾ�ַ��������ø�ʽDis_Head("Head")

/*--------------------*��ʾ�ַ���*--------------------*/

void Dis_String (unsigned char Position,signed char String[]);
// �������е������������η�Ϊ1,2,3,4,5,6��������ʾ
// ���ø�ʽDis_String(1,"String")

/*--------------------*��ʾ������*--------------------*/      

void Dis_Int    (unsigned char Position,signed int Number);
// ���ø�ʽDis_Int(2,123)��Dis_Int(3,Temp_Int)

/*--------------------*��ʾ������*--------------------*/

void Dis_Float  (unsigned char Position,float Number);
// ���ø�ʽDis_Float(3,12.34)��Dis_Float(4,Temp_Float)

/*---------------------*��ʾ����*---------------------*/
    
extern void Dis_Battery(void);
// �����Ͻ���ʾ��Battery�������д���֮��ĵ���ֵ
// ��820ʱ��ʾ����������720ʱΪ��
                             
/*-------------------*�б������ʾ*-------------------*/      
   
void Paint_Fresh(float New_Data,float Paint_Ave,float Paint_Margin);
// �����ݴ�������ʾ��ͼ�ϣ��ﵽ��Ļ���Ҷ�ʱ�����ͼ�Σ����´���ʼ
// ���ø�ʽPaint_Fresh(Data,0,100)
// ��ʾ����Data���������ͼ�Σ�ͼ����0Ϊ���ߣ���ʾ����100���ڵ�����

/*-------------------*������ʾ����*-------------------*/      
  
void Paint_List (float New_Data,float Paint_Ave,float Paint_Margin);
// ��������ʾ���ﵽ��Ļ���Ҷ�ʱ������������������
// ���ø�ʽPaint_List(Data,0,50)
  
  
 
  
/******************************************************/
/********************  ���ܺ���    ********************/
/******************************************************/

extern char Change_To_Bit[8];

/*-----------------*OLEDд��λ�ַ���*-----------------*/

void OLED_Write_String_7(unsigned char y,unsigned char x,signed char String[]);


/*---------------------*���λ��*---------------------*/

void Position_Clear(unsigned char Position);


/*--------------------*��Ļͷ��ʾ*--------------------*/

void Dis_Head(signed char String[]);


/*--------------------*��ʾ�ַ���*--------------------*/

void Dis_String(unsigned char Position,signed char String[]);


/*--------------------*��ʾ������*--------------------*/      

void Dis_Int(unsigned char Position,signed int Number);
void Dis_Int_Flg(unsigned char Position,signed int Number);

/*--------------------*��ʾ������*--------------------*/

void Dis_Float(unsigned char Position,float Number);


/*-------------------*�б������ʾ*-------------------*/      
   
void Paint_Fresh(float New_Data,float Paint_Ave,float Paint_Margin);
// ��ĳ���������б�ˢ�µ���ʽ��ʾ����


/*---------------------*�б��ƶ�*---------------------*/      

void List_Move(signed char New_Data);
// �����������λ

/*-------------------*��ʾ�б�ͼ��*-------------------*/      

void List_Paint(void);



// ��Temp_List�б������������һ����ͼ������





/*-------------------*������ʾ����*-------------------*/     


  
#endif  