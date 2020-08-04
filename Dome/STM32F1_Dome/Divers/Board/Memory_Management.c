
#include "Memory_Management.h"

Speed_Data_type Speed_Data[6] = {0};
Speed_Data_type Speed_Correction_Data[6] = {0};
system_set_type system_set_data = {0};
//Control_Data_type Control_Data = {0};
Line_Data_type Line_Data = {0};
/********************************************************************************************************
                                            EEPROM(AT24C512)�ڴ��ַ�ֲ�

         Ԥ��                        PWM���ٶȲ�����ԭʼֵ�����ɸĶ���              

                    1��         2��          3��                4��          5��            6��
         0-100    101-166     301-366       501-566           701-766      901-966       1101-1166
 
(Byte)   101        66          66            66                66            66            66
          1          2           3             4                 5             6             7
       ************************************************************************************************
                                       PWM���Ʋ�������                           

             1��         2��          3��                4��          5��            6��
         1301-1366    1501-1566    1701-1766         1901-1966      2101-2166      2301-2366 
 
(Byte)      66            66           66                66             66              66
            8             9            10                11             12              13
       ************************************************************************************************
         ��ŵ�        ��������       ��·����          ��·վ���Ų�          
  
         2501-2513    2701-2800        2901-3500          5001-5500(ǰ250��˳���Ų�վ�㣬��250��˳���Ų���·��)       
 
(Byte)     13            100            200*3=600             500
            14            15              16               17   18  19
       ************************************************************************************************
         ���ﶯ��                           
  
         6501-6750                 
 
(Byte)      250             
            21              
*********************************************************************************************************/
void Base_Data_Load(void)
{	
	//ϵͳ���ò�������
	AT24CXX_Read(MEMORY_SYSTEMSETADDR,system_set_data.all,6);
	
	//�ٶȲ������ٶ�������������
	AT24CXX_Read(MEMORY_SPEED1PIDADDR,Speed_Data[0].all,66);
	AT24CXX_Read(MEMORY_SPEED2PIDADDR,Speed_Data[1].all,66);
	AT24CXX_Read(MEMORY_SPEED3PIDADDR,Speed_Data[2].all,66);
	AT24CXX_Read(MEMORY_SPEED4PIDADDR,Speed_Data[3].all,66);
	AT24CXX_Read(MEMORY_SPEED5PIDADDR,Speed_Data[4].all,66);
	AT24CXX_Read(MEMORY_SPEED6PIDADDR,Speed_Data[5].all,66);
	delay_ms(1000);
	AT24CXX_Read(MEMORY_SPEED1CPIDADDR,Speed_Correction_Data[0].all,66);
	AT24CXX_Read(MEMORY_SPEED2CPIDADDR,Speed_Correction_Data[1].all,66);
	AT24CXX_Read(MEMORY_SPEED3CPIDADDR,Speed_Correction_Data[2].all,66);
	AT24CXX_Read(MEMORY_SPEED4CPIDADDR,Speed_Correction_Data[3].all,66);
	AT24CXX_Read(MEMORY_SPEED5CPIDADDR,Speed_Correction_Data[4].all,66);
	AT24CXX_Read(MEMORY_SPEED6CPIDADDR,Speed_Correction_Data[5].all,66);
  //���Ŀ��վ�㻺�������Ϊ0���ϱ�ʣ��Ŀ��վ�㣬������һ����ֵ��Control_Data.bit.terminal_station 
}


void Car_Move_Parametr_Init(void)
{
	Speed_Data_type test_speed_data[6] = {0};
/********************************�ٶ�ֵ��PID������ʼ��********************************************/
	
	//��1���ٶȣ���Ϊ����ٶȣ�������λ��ֵԽ���ٶ�Խ�죩
  test_speed_data[0].bit.speed_value = 10;
	
	/*****************************ֱ������PID**********************/
	//�õ��ٶ���ƫ�����PID����
	test_speed_data[0].bit.PID[0][0].f = 30.0;//14.0     11.5  16.5
	test_speed_data[0].bit.PID[0][1].f = 0.0;//         0.5    0.0
	test_speed_data[0].bit.PID[0][2].f = 0.005;//         2.5  0.025	
	
  //ƫ������PID����	
	test_speed_data[0].bit.PID[1][0].f = 37.0;//8.5      8.5     15.5
	test_speed_data[0].bit.PID[1][1].f = 4.0;//         0.2      3.0
	test_speed_data[0].bit.PID[1][2].f = 14.0;//           0.5   14.0
	
	//��ʱͣ��PID����
	test_speed_data[0].bit.PID[2][0].f = 0.0;//         0.0        0 
	test_speed_data[0].bit.PID[2][1].f = 5.0;//        0.08       4.0
	test_speed_data[0].bit.PID[2][2].f = 1.5;//         0.8       1.0
	
	/*****************************�������PID**********************/
	test_speed_data[0].bit.PID[3][0].f = 30.0;//         0.0        0 
	test_speed_data[0].bit.PID[3][1].f = 5.0;//        0.08       4.0
	test_speed_data[0].bit.PID[3][2].f = 1.5;//     	
	
	/*****************************ͣ������PID**********************/
	test_speed_data[0].bit.PID[4][0].f = 30.0;//         0.0        0 
	test_speed_data[0].bit.PID[4][1].f = 5.0;//        0.08       4.0
	test_speed_data[0].bit.PID[4][2].f = 1.5;//     		
	
	/*****************************�����������ٶ�������ٳ̶�(��5����0-4)**********************/
	test_speed_data[0].bit.speed_change_value[0] = 1;     //ͣ�����ü��ٻ���	

	test_speed_data[0].bit.speed_change_value[1] = 0;     //δ��
	
	test_speed_data[0].bit.speed_change_value[2] = 0;     //δ��
	
	test_speed_data[0].bit.speed_change_value[3] = 0;     //δ��
	
	test_speed_data[0].bit.speed_change_value[4] = 0;     //δ��


	AT24CXX_Write(MEMORY_SPEED1PIDADDR,test_speed_data[0].all,66);
	
	
	//��2���ٶ�
  test_speed_data[1].bit.speed_value = 50;
	
	/*****************************ֱ������PID**********************/
	//�õ��ٶ���ƫ�����PID����
	test_speed_data[1].bit.PID[0][0].f = 18.0;//14.0     11.5  16.5
	test_speed_data[1].bit.PID[0][1].f = 0.0;//          0.5    0.0
	test_speed_data[1].bit.PID[0][2].f = 0.005;//         2.5  0.025	
	
  //ƫ������PID����	
	test_speed_data[1].bit.PID[1][0].f = 17.0;//8.5      8.5     15.5
	test_speed_data[1].bit.PID[1][1].f = 4.0;//         0.2      3.0
	test_speed_data[1].bit.PID[1][2].f = 14.0;//           0.5   14.0
	
	//��ʱͣ��PID����
	test_speed_data[1].bit.PID[2][0].f = 0.0;//         0.0        0 
	test_speed_data[1].bit.PID[2][1].f = 5.0;//        0.08       4.0
	test_speed_data[1].bit.PID[2][2].f = 1.5;//         0.8       1.0
	
	/*****************************�������PID**********************/
	test_speed_data[1].bit.PID[3][0].f = 30.0;//         0.0        0 
	test_speed_data[1].bit.PID[3][1].f = 5.0;//        0.08       4.0
	test_speed_data[1].bit.PID[3][2].f = 1.5;//    

	/*****************************ͣ������PID**********************/
	test_speed_data[1].bit.PID[4][0].f = 30.0;//         0.0        0 
	test_speed_data[1].bit.PID[4][1].f = 5.0;//        0.08       4.0
	test_speed_data[1].bit.PID[4][2].f = 1.5;// 
	
	/*****************************�����������ٶ�������ٳ̶�(��5����0-4)**********************/
	test_speed_data[1].bit.speed_change_value[0] = 2;     //ͣ�����ü��ٻ���	

	test_speed_data[1].bit.speed_change_value[1] = 1;     //���ٵ���1���ٶ����ü��ٻ���
	
	test_speed_data[1].bit.speed_change_value[2] = 0;     //δ��
	
	test_speed_data[1].bit.speed_change_value[3] = 0;     //δ��
	
	test_speed_data[1].bit.speed_change_value[4] = 0;     //δ��

	AT24CXX_Write(MEMORY_SPEED2PIDADDR,test_speed_data[1].all,66);
	


	//��3���ٶ�
  test_speed_data[2].bit.speed_value = 60;
	
	/*****************************ֱ������PID**********************/
	//�õ��ٶ���ƫ�����PID����
	test_speed_data[2].bit.PID[0][0].f = 18.0;//14.0     11.5  16.5
	test_speed_data[2].bit.PID[0][1].f = 0.0;//         0.5    0.0
	test_speed_data[2].bit.PID[0][2].f = 0.005;//         2.5  0.025	
	
  //ƫ������PID����	
	test_speed_data[2].bit.PID[1][0].f = 17.0;//8.5      8.5     15.5
	test_speed_data[2].bit.PID[1][1].f = 4.0;//         0.2      3.0
	test_speed_data[2].bit.PID[1][2].f = 14.0;//           0.5   14.0
	
	//��ʱͣ��PID����
	test_speed_data[2].bit.PID[2][0].f = 0.0;//         0.0        0 
	test_speed_data[2].bit.PID[2][1].f = 5.0;//        0.08       4.0
	test_speed_data[2].bit.PID[2][2].f = 1.5;//         0.8       1.0
	
	/*****************************�������PID**********************/
	test_speed_data[2].bit.PID[3][0].f = 30.0;//         0.0        0 
	test_speed_data[2].bit.PID[3][1].f = 5.0;//        0.08       4.0
	test_speed_data[2].bit.PID[3][2].f = 1.5;//     	
	
	/*****************************ͣ������PID**********************/
	test_speed_data[2].bit.PID[4][0].f = 30.0;//         0.0        0 
	test_speed_data[2].bit.PID[4][1].f = 5.0;//        0.08       4.0
	test_speed_data[2].bit.PID[4][2].f = 1.5;// 


	/*****************************�����������ٶ�������ٳ̶�(��5����0-4)**********************/
	test_speed_data[2].bit.speed_change_value[0] = 3;     //ͣ�����ü��ٻ���	

	test_speed_data[2].bit.speed_change_value[1] = 2;     //���ٵ���1���ٶ����ü��ٻ���
	
	test_speed_data[2].bit.speed_change_value[2] = 1;     //���ٵ���2���ٶ����ü��ٻ���
	
	test_speed_data[2].bit.speed_change_value[3] = 0;     //δ��
	
	test_speed_data[2].bit.speed_change_value[4] = 0;     //δ��


	AT24CXX_Write(MEMORY_SPEED3PIDADDR,test_speed_data[2].all,66);
	
	
	
	//��4���ٶ�
  test_speed_data[3].bit.speed_value = 60;
	
	/*****************************ֱ������PID**********************/
	//�õ��ٶ���ƫ�����PID����
	test_speed_data[3].bit.PID[0][0].f = 18.0; //14.0     11.5  16.5
	test_speed_data[3].bit.PID[0][1].f = 0.0;  //          0.5    0.0
	test_speed_data[3].bit.PID[0][2].f = 0.005;//         2.5  0.025	
	
  //ƫ������PID����	
	test_speed_data[3].bit.PID[1][0].f = 17.0;//8.5      8.5     15.5
	test_speed_data[3].bit.PID[1][1].f = 4.0; //         0.2      3.0
	test_speed_data[3].bit.PID[1][2].f = 14.0;//           0.5   14.0
	
	//��ʱͣ��PID����
	test_speed_data[3].bit.PID[2][0].f = 0.0;//         0.0        0 
	test_speed_data[3].bit.PID[2][1].f = 5.0;//        0.08       4.0
	test_speed_data[3].bit.PID[2][2].f = 1.5;//         0.8       1.0
	
	/*****************************�������PID**********************/
	test_speed_data[3].bit.PID[3][0].f = 30.0;//         0.0        0 
	test_speed_data[3].bit.PID[3][1].f = 5.0;//        0.08       4.0
	test_speed_data[3].bit.PID[3][2].f = 1.5;//    

	/*****************************ͣ������PID**********************/
	test_speed_data[3].bit.PID[4][0].f = 30.0;//         0.0        0 
	test_speed_data[3].bit.PID[4][1].f = 5.0;//        0.08       4.0
	test_speed_data[3].bit.PID[4][2].f = 1.5;// 

	/*****************************�����������ٶ�������ٳ̶�(��5����0-4)**********************/
	test_speed_data[3].bit.speed_change_value[0] = 4;     //ͣ�����ü��ٻ���	

	test_speed_data[3].bit.speed_change_value[1] = 3;     //���ٵ���1���ٶ����ü��ٻ���
	
	test_speed_data[3].bit.speed_change_value[2] = 2;     //���ٵ���2���ٶ����ü��ٻ���
	
	test_speed_data[3].bit.speed_change_value[3] = 1;     //���ٵ���3���ٶ����ü��ٻ���
	
	test_speed_data[3].bit.speed_change_value[4] = 0;     //δ��

	AT24CXX_Write(MEMORY_SPEED4PIDADDR,test_speed_data[3].all,66);
	


	//��5���ٶ�
  test_speed_data[4].bit.speed_value = 60;
	
	/*****************************ֱ������PID**********************/
	//�õ��ٶ���ƫ�����PID����
	test_speed_data[4].bit.PID[0][0].f = 18.0;//14.0     11.5  16.5
	test_speed_data[4].bit.PID[0][1].f = 0.0;//         0.5    0.0
	test_speed_data[4].bit.PID[0][2].f = 0.005;//         2.5  0.025	
	
  //ƫ������PID����	
	test_speed_data[4].bit.PID[1][0].f = 17.0;//8.5      8.5     15.5
	test_speed_data[4].bit.PID[1][1].f = 4.0;//         0.2      3.0
	test_speed_data[4].bit.PID[1][2].f = 14.0;//           0.5   14.0
	
	//��ʱͣ��PID����
	test_speed_data[4].bit.PID[2][0].f = 0.0;//         0.0        0 
	test_speed_data[4].bit.PID[2][1].f = 5.0;//        0.08       4.0
	test_speed_data[4].bit.PID[2][2].f = 1.5;//         0.8       1.0
	
	/*****************************�������PID**********************/
	test_speed_data[4].bit.PID[3][0].f = 30.0;//         0.0        0 
	test_speed_data[4].bit.PID[3][1].f = 5.0;//        0.08       4.0
	test_speed_data[4].bit.PID[3][2].f = 1.5;//     	

	/*****************************ͣ������PID**********************/
	test_speed_data[4].bit.PID[4][0].f = 30.0;//         0.0        0 
	test_speed_data[4].bit.PID[4][1].f = 5.0;//        0.08       4.0
	test_speed_data[4].bit.PID[4][2].f = 1.5;// 

	/*****************************�����������ٶ�������ٳ̶�(��5����0-4)**********************/
	test_speed_data[4].bit.speed_change_value[0] = 5;     //ͣ�����ü��ٻ���	

	test_speed_data[4].bit.speed_change_value[1] = 4;     //���ٵ���1���ٶ����ü��ٻ���
	
	test_speed_data[4].bit.speed_change_value[2] = 3;     //���ٵ���2���ٶ����ü��ٻ���
	
	test_speed_data[4].bit.speed_change_value[3] = 2;     //���ٵ���3���ٶ����ü��ٻ���
	
	test_speed_data[4].bit.speed_change_value[4] = 1;     //���ٵ���4���ٶ����ü��ٻ���


	AT24CXX_Write(MEMORY_SPEED5PIDADDR,test_speed_data[4].all,66);
	
	
	
	//��6���ٶ�
  test_speed_data[5].bit.speed_value = 30;
	
	/*****************************ֱ������PID**********************/
	//�õ��ٶ���ƫ�����PID����
	test_speed_data[5].bit.PID[0][0].f = 20.0;//14.0     11.5  16.5
	test_speed_data[5].bit.PID[0][1].f = 0.0;//          0.5    0.0
	test_speed_data[5].bit.PID[0][2].f = 0.005;//         2.5  0.025	
	
  //ƫ������PID����	
	test_speed_data[5].bit.PID[1][0].f = 25.0;//8.5      8.5     15.5
	test_speed_data[5].bit.PID[1][1].f = 4.0;//         0.2      3.0
	test_speed_data[5].bit.PID[1][2].f = 14.0;//           0.5   14.0
	
	//��ʱͣ��PID����
	test_speed_data[5].bit.PID[2][0].f = 0.0;//         0.0        0 
	test_speed_data[5].bit.PID[2][1].f = 5.0;//        0.08       4.0
	test_speed_data[5].bit.PID[2][2].f = 1.5;//         0.8       1.0
	
	/*****************************�������PID**********************/
	test_speed_data[5].bit.PID[3][0].f = 30.0;//         0.0        0 
	test_speed_data[5].bit.PID[3][1].f = 5.0;//        0.08       4.0
	test_speed_data[5].bit.PID[3][2].f = 1.5;//    

	/*****************************ͣ������PID**********************/
	test_speed_data[5].bit.PID[4][0].f = 30.0;//         0.0        0 
	test_speed_data[5].bit.PID[4][1].f = 5.0;//        0.08       4.0
	test_speed_data[5].bit.PID[4][2].f = 1.5;// 

	/*****************************�����������ٶ�������ٳ̶�(��5����0-4)**********************/
	test_speed_data[5].bit.speed_change_value[0] = 5;     //���ٵ���1���ٶ����ü��ٻ���	

	test_speed_data[5].bit.speed_change_value[1] = 4;     //���ٵ���2���ٶ����ü��ٻ���
	
	test_speed_data[5].bit.speed_change_value[2] = 3;     //���ٵ���3���ٶ����ü��ٻ���
	
	test_speed_data[5].bit.speed_change_value[3] = 2;     //���ٵ���4���ٶ����ü��ٻ���
	
	test_speed_data[5].bit.speed_change_value[4] = 1;     //���ٵ���5���ٶ����ü��ٻ���

	AT24CXX_Write(MEMORY_SPEED6PIDADDR,test_speed_data[5].all,66);
	
}


