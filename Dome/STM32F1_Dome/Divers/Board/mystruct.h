#ifndef MYSTRUCT_H
#define MYSTRUCT_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
/* Private macro -------------------------------------------------------------*/
/*  Cmd_queue中宏定义
 */



/* Private variables type-----------------------------------------------------*/



typedef struct PID  /*  PID运算结构体   */
{
  int SetPoint;     // 设定目标Desired value
  float Proportion;   // 比例常数Proportional Const
  float Integral;     // 积分常数Integral Const
  float Derivative;   // 微分常数Derivative Const
	float Error[5];    // Error[0]、Error[-1]、Error[-2]、Error[-3]、Error[-4]...
//  float LastError;    // Error[-1]
//  float PrevError;    // Error[-2]
  float SumError;     // Sums of Errors
}PID;



typedef union  /*  单精度浮点转4字节无符号整型联合体（具体内容查询IEEE754）*/
{
	float f;
	uint8_t u8[4];
}float4Byte;



#pragma pack(push)
#pragma pack(1)                           //按字节对齐

typedef union         /*  地图管理数据   */
{
	uint8_t all[4];
	struct
	{
    uint8_t line;  //线路号
    uint8_t roll;	 //环形标志 （1是/0不是）  
    uint8_t first; //该线路上首站点号
    uint8_t last;	 //该线路上尾站点号	
	}bit;		
}Line_Data_type;


typedef union         /*  速度控制数据   */
{
	uint8_t all[66];
	struct
	{
		uint8_t speed_value;              //1byte 速度值  
		int8_t speed_change_value[5];     //5byte 变速时改变量     
		float4Byte PID[5][3];             //5*3*4= 60byte PID控制参数  
	}bit;
}Speed_Data_type;


typedef union   /*系统设置参数，不能清空，只能通过手动设置改变，除非恢复出厂设置*/
{
	uint8_t all[6];
  struct
	{
		uint8_t running_mode;           //为0时表示单机模式，为1时表示联网模式
		uint8_t laser_status;           //表示激光测距是否使能，0为不使能，1为使能
		uint8_t laser_distance[2];      //激光防撞距离 2747-2748
    uint8_t roller_speed_mode;      //滚筒速度
		uint8_t speed_correction_gear;  //修正参数的速度档位
	}bit;
}system_set_type;


typedef union         /*   外部传感器IO信号   */
{
 struct 
 {
   uint8_t reserve3:2; //未使用
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
   uint8_t reserve1:8; //未使用	 
 }bits;	 
 uint32_t all; 
}IODATA_Type;


//typedef union
//{
//	uint8_t all[100];
//  struct
//	{
//		//运动逻辑所需参数
//	  uint8_t start_station;    //2701
//	  uint8_t start_line;       //2702
//	  uint8_t terminal_station; //2703
//	  uint8_t terminal_line;    //2704
//		uint8_t screen_id;        //2705
//		uint8_t control_id;       //2706
//		uint8_t reserve1[8];      //备用的4个字节 内存地址2707-2714
//		//运动过程数据
//    uint8_t turn_flag;            //2715 转弯标志，用于判断是入弯还是出弯		
//    uint8_t control_mode;         //2716
//	  uint8_t move_commend;         //2717
//		uint8_t running_status;       //2718
//		uint8_t current_speed_gear;   //2719 当前速度档位（0-5档，数字越大，速度越快）
//		uint8_t goal_speed_gear;      //2720 目标速度档位（0-5档，数字越大，速度越快）		
//		/***这些与设置相关，不能清空，只能通过手动设置改变，除非恢复出厂设置***/		
//		uint8_t motor_diver_mode;    //为0表示PWM驱动，为1表示485驱动//2721
//		uint8_t system_mode;         //为0时表示单机模式，为1时表示联网模式//2722
//		uint8_t laser_status;   //表示激光测距是否使能，0为不使能，1为使能//2723
//    uint8_t roller_speed_mode;   //2724
//		uint8_t speed_correction_gear; //修正参数的速度档位//2725
//		/**********************************************************************/
//		uint8_t reserve2[5];               //备用的6个字节  内存地址2726-2730
//		uint8_t station_order[16];         //站点排布     2731-2746
//    uint8_t laser_distance[2];         //激光防撞距离 2747-2748
//    uint8_t line_sum;		               //线路总条数   2749
//		uint8_t goal_station_count;        //预备站点个数计数 2750
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


typedef struct NavInformatiom_Type   /*   磁导航传感器相关数据   */
{
	struct 
	{ 
	  float	Value;            //磁传感器16位对应的权重值，越靠近1或者16，其绝对值越大，两边互为相反数
	  _Bool Status;           //16位对应状态值，检测到磁条即为1，否则0
	}Nav[16];
	uint16_t Sum;             //在轨个数总和
	uint16_t ChangCount;      //状态跳变时计数
	uint16_t StartJudgeNumber;//使用在轨状态首跳变时标号
	uint16_t EndJudgeNumber;  //使用在轨状态尾跳变时标号
	float Average;            //权重平均值
}NavInformatiom_Type;



typedef enum    /*   控制模式   */
{
  AUTOMATIC = 0,              //自动模式
  MANUAL	                //手动模式即串口屏模式	
}Control_Mode_type;


typedef  struct _baffle_mode       /* 挡板动作模式 */
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
  
typedef  struct _roller_mode    /*  滚筒控制模式  */
{
    enum
		{
	    LOW = 0,                //低速
	    MEDIUM,                 //中速
	    HIGH                    //高速					
		}speed_mode;
    enum
		{
	    FORWARD = 0,            //前进
		  BACKWARD,               //后退					
		}direction_mode;			
}_roller_mode;



typedef struct _automatic_para
{
	enum
	{
	  ASTOP = 0,               //停止
	  ATEMP_STOP,              //临时停止
    ASTART		               //启动
	}control_mode;
  enum               /* 转向模式 */
  {
	   ASTRAIGHT = 0,           //直走
		 ATURN,
	   ATURN_LEFT,              //左转
	   ATURN_RIGHT,             //右转
  }turn_mode;
	_baffle_mode baffle_mode;
  _roller_mode roller_mode;	
	/*   运动逻辑所需参数  */
	uint8_t start_station;        //
	uint8_t start_line;           //
	uint8_t terminal_station;     //
	uint8_t terminal_line;        //
  uint8_t screen_id;            //
  uint8_t control_id;           //
	uint8_t running_status;       //运动状态
	uint8_t later_running_status; //上一次运动状态
  uint8_t goal_station_count;   //预备站点个数计数 2750
  uint8_t goal_station_buff[50];//目标站点缓存区  	
	uint8_t current_speed_gear;   //当前速度档位（0-5档，数字越大，速度越快）
	uint8_t goal_speed_gear;      //目标速度档位（0-5档，数字越大，速度越快）
  float current_speed;  
}automatic_para;


typedef struct _manual_para
{
  enum               /* 转向模式 */
  {
		 MSTOP = 0,
	   MFORWARD,            //前进
		 MBACKWARD,               //后退
	   MTURN_LEFT,              //左转
	   MTURN_RIGHT,             //右转
		 MLEFT_HANDED,            //左旋
		 MRIGHT_HANDED            //右旋
  }turn_Mode;
	_baffle_mode baffle_mode;
  _roller_mode roller_mode;  		
}manual_para;

/* Private variables ---------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

#endif
