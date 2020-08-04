#ifndef MYSTRUCT_H
#define MYSTRUCT_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
/* Private macro -------------------------------------------------------------*/
/*  Cmd_queue�к궨��
 */



/* Private variables type-----------------------------------------------------*/



typedef struct PID  /*  PID����ṹ��   */
{
  int SetPoint;     // �趨Ŀ��Desired value
  float Proportion;   // ��������Proportional Const
  float Integral;     // ���ֳ���Integral Const
  float Derivative;   // ΢�ֳ���Derivative Const
	float Error[5];    // Error[0]��Error[-1]��Error[-2]��Error[-3]��Error[-4]...
//  float LastError;    // Error[-1]
//  float PrevError;    // Error[-2]
  float SumError;     // Sums of Errors
}PID;



typedef union  /*  �����ȸ���ת4�ֽ��޷������������壨�������ݲ�ѯIEEE754��*/
{
	float f;
	uint8_t u8[4];
}float4Byte;



#pragma pack(push)
#pragma pack(1)                           //���ֽڶ���

typedef union         /*  ��ͼ��������   */
{
	uint8_t all[4];
	struct
	{
    uint8_t line;  //��·��
    uint8_t roll;	 //���α�־ ��1��/0���ǣ�  
    uint8_t first; //����·����վ���
    uint8_t last;	 //����·��βվ���	
	}bit;		
}Line_Data_type;


typedef union         /*  �ٶȿ�������   */
{
	uint8_t all[66];
	struct
	{
		uint8_t speed_value;              //1byte �ٶ�ֵ  
		int8_t speed_change_value[5];     //5byte ����ʱ�ı���     
		float4Byte PID[5][3];             //5*3*4= 60byte PID���Ʋ���  
	}bit;
}Speed_Data_type;


typedef union   /*ϵͳ���ò�����������գ�ֻ��ͨ���ֶ����øı䣬���ǻָ���������*/
{
	uint8_t all[6];
  struct
	{
		uint8_t running_mode;           //Ϊ0ʱ��ʾ����ģʽ��Ϊ1ʱ��ʾ����ģʽ
		uint8_t laser_status;           //��ʾ�������Ƿ�ʹ�ܣ�0Ϊ��ʹ�ܣ�1Ϊʹ��
		uint8_t laser_distance[2];      //�����ײ���� 2747-2748
    uint8_t roller_speed_mode;      //��Ͳ�ٶ�
		uint8_t speed_correction_gear;  //�����������ٶȵ�λ
	}bit;
}system_set_type;


typedef union         /*   �ⲿ������IO�ź�   */
{
 struct 
 {
   uint8_t reserve3:2; //δʹ��
   uint8_t Light_SW2:1;
   uint8_t Light_SW1:1;
   uint8_t Light_SW3:1;
   uint8_t Light_SW4:1;
   uint8_t Light_SW5:1;
   uint8_t Light_SW6:1;
   uint8_t Alarm2:1;
   uint8_t Alarm1:1;
   uint8_t SW6:1;
   uint8_t SW5:1;
   uint8_t SW1:1;
   uint8_t SW2:1;
   uint8_t SW3:1;
   uint8_t SW4:1;
   uint8_t K4:1;
   uint8_t K3:1;
   uint8_t K2:1;
   uint8_t K1:1;
   uint8_t K5:1;
   uint8_t K6:1;
   uint8_t K7:1;
   uint8_t K8:1;
   uint8_t reserve1:8; //δʹ��	 
 }bits;	 
 uint32_t all; 
}IODATA_Type;


//typedef union
//{
//	uint8_t all[100];
//  struct
//	{
//		//�˶��߼��������
//	  uint8_t start_station;    //2701
//	  uint8_t start_line;       //2702
//	  uint8_t terminal_station; //2703
//	  uint8_t terminal_line;    //2704
//		uint8_t screen_id;        //2705
//		uint8_t control_id;       //2706
//		uint8_t reserve1[8];      //���õ�4���ֽ� �ڴ��ַ2707-2714
//		//�˶���������
//    uint8_t turn_flag;            //2715 ת���־�������ж������仹�ǳ���		
//    uint8_t control_mode;         //2716
//	  uint8_t move_commend;         //2717
//		uint8_t running_status;       //2718
//		uint8_t current_speed_gear;   //2719 ��ǰ�ٶȵ�λ��0-5��������Խ���ٶ�Խ�죩
//		uint8_t goal_speed_gear;      //2720 Ŀ���ٶȵ�λ��0-5��������Խ���ٶ�Խ�죩		
//		/***��Щ��������أ�������գ�ֻ��ͨ���ֶ����øı䣬���ǻָ���������***/		
//		uint8_t motor_diver_mode;    //Ϊ0��ʾPWM������Ϊ1��ʾ485����//2721
//		uint8_t system_mode;         //Ϊ0ʱ��ʾ����ģʽ��Ϊ1ʱ��ʾ����ģʽ//2722
//		uint8_t laser_status;   //��ʾ�������Ƿ�ʹ�ܣ�0Ϊ��ʹ�ܣ�1Ϊʹ��//2723
//    uint8_t roller_speed_mode;   //2724
//		uint8_t speed_correction_gear; //�����������ٶȵ�λ//2725
//		/**********************************************************************/
//		uint8_t reserve2[5];               //���õ�6���ֽ�  �ڴ��ַ2726-2730
//		uint8_t station_order[16];         //վ���Ų�     2731-2746
//    uint8_t laser_distance[2];         //�����ײ���� 2747-2748
//    uint8_t line_sum;		               //��·������   2749
//		uint8_t goal_station_count;        //Ԥ��վ��������� 2750
//		uint8_t goal_station_buff[50];
//	}bit;
//}Control_Data_type;

typedef struct _car_info
{
	union
	{
	  struct
	  {
      uint8_t safety_stop_flag:1;
      uint8_t emergency_stop_flag:1;
      uint8_t motor_alarm_flag:1;
      uint8_t nav_status_with_screen_control:1;
			uint8_t reserve:4;
	  }bit;
		uint8_t all;
	}status;
  uint8_t goods_status;
  uint8_t roller_status;	
	uint8_t light_band_status;
}_car_info;

#pragma pack(pop)


typedef struct NavInformatiom_Type   /*   �ŵ����������������   */
{
	struct 
	{ 
	  float	Value;            //�Ŵ�����16λ��Ӧ��Ȩ��ֵ��Խ����1����16�������ֵԽ�����߻�Ϊ�෴��
	  _Bool Status;           //16λ��Ӧ״ֵ̬����⵽������Ϊ1������0
	}Nav[16];
	uint16_t Sum;             //�ڹ�����ܺ�
	uint16_t ChangCount;      //״̬����ʱ����
	uint16_t StartJudgeNumber;//ʹ���ڹ�״̬������ʱ���
	uint16_t EndJudgeNumber;  //ʹ���ڹ�״̬β����ʱ���
	float Average;            //Ȩ��ƽ��ֵ
}NavInformatiom_Type;



typedef enum    /*   ����ģʽ   */
{
  AUTOMATIC = 0,              //�Զ�ģʽ
  MANUAL	                //�ֶ�ģʽ��������ģʽ	
}Control_Mode_type;


typedef  struct _baffle_mode       /* ���嶯��ģʽ */
{
    enum              
    {
      LEFT_BAFFLE_RISE = 0,
		  LEFT_BAFFLE_FALL,
	  }left;
    enum              
    {
		  RIGHT_BAFFLE_RISE = 0,
		  RIGHT_BAFFLE_FALL,
	  }right;	 
}_baffle_mode;
  
typedef  struct _roller_mode    /*  ��Ͳ����ģʽ  */
{
    enum
		{
	    LOW = 0,                //����
	    MEDIUM,                 //����
	    HIGH                    //����					
		}speed_mode;
    enum
		{
	    FORWARD = 0,            //ǰ��
		  BACKWARD,               //����					
		}direction_mode;			
}_roller_mode;



typedef struct _automatic_para
{
	enum
	{
	  ASTOP = 0,               //ֹͣ
	  ATEMP_STOP,              //��ʱֹͣ
    ASTART		               //����
	}control_mode;
  enum               /* ת��ģʽ */
  {
	   ASTRAIGHT = 0,           //ֱ��
		 ATURN,
	   ATURN_LEFT,              //��ת
	   ATURN_RIGHT,             //��ת
  }turn_mode;
	_baffle_mode baffle_mode;
  _roller_mode roller_mode;	
	/*   �˶��߼��������  */
	uint8_t start_station;        //
	uint8_t start_line;           //
	uint8_t terminal_station;     //
	uint8_t terminal_line;        //
  uint8_t screen_id;            //
  uint8_t control_id;           //
	uint8_t running_status;       //�˶�״̬
	uint8_t later_running_status; //��һ���˶�״̬
  uint8_t goal_station_count;   //Ԥ��վ��������� 2750
  uint8_t goal_station_buff[50];//Ŀ��վ�㻺����  	
	uint8_t current_speed_gear;   //��ǰ�ٶȵ�λ��0-5��������Խ���ٶ�Խ�죩
	uint8_t goal_speed_gear;      //Ŀ���ٶȵ�λ��0-5��������Խ���ٶ�Խ�죩
  float current_speed;  
}automatic_para;


typedef struct _manual_para
{
  enum               /* ת��ģʽ */
  {
		 MSTOP = 0,
	   MFORWARD,            //ǰ��
		 MBACKWARD,               //����
	   MTURN_LEFT,              //��ת
	   MTURN_RIGHT,             //��ת
		 MLEFT_HANDED,            //����
		 MRIGHT_HANDED            //����
  }turn_Mode;
	_baffle_mode baffle_mode;
  _roller_mode roller_mode;  		
}manual_para;

/* Private variables ---------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

#endif
