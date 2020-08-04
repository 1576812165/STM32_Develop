
/* Includes ------------------------------------------------------------------*/
#include "IC.h"
/* Private macro -------------------------------------------------------------*/
//路径卡中信息较多故采用宏定义，便于区分和检查
#define STATION1 11

#define LINE1 12

#define TURN1 13


#define STATION2 14

#define LINE2 15

#define TURN2 16



#define STATION3 17

#define LINE3 18

#define TURN3 19
/* Private variables ---------------------------------------------------------*/
uint8_t icbuff[IC_BUF_SIZE + 3] = {0};
uint8_t latericbuff[IC_BUF_SIZE + 3] = {0};
uint8_t Read_IC_Count = 0;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/********************************IC卡信息解析****************************************************

                             IC卡中数据均以16进制表示
1.卡类型：01 表示站点卡，02 表示路径卡，03 表示加减速卡
  转向代号：0x01 代表直行  0x02 代表左转  0x03 代表右转
	变速卡功能码：0x04 代表到站  0x05 代表转弯
2站点卡中信息
第一个字节    第二个字节        第三个字节      
                                                                                  
类别（0x01）  当前站点号    当前站点号所在线路编号

3.路径卡中信息
第一个字节    第二个字节        第三个字节           第四个字节    第五个字节           第六个字节           第七个字节
                                                                                  
类别（0x02）  能去往站点号    站点号所在线路编号       转向代号    能去往站点号        站点号所在线路编号       转向代号

4.变速卡中信息
第一个字节    第二个字节        第三个字节                 第四个字节        第五个字节（注：如果功能是到站则此处写0） 
                                                                                  
类别（0x03）    功能码     到站站点号/入弯速度        快到站速度/出弯速度      入弯（1）/出弯（0）
*************************************************************************************************/


void Get_Action_Commend(uint8_t number)
{
	switch(number)
	{
		case 0x00:break; //表示无动作		
		case 0x01: automatic_control.turn_mode = ASTRAIGHT;
		           break;	
		case 0x02: automatic_control.turn_mode = ATURN_LEFT;
		           break;		
	  case 0x03: automatic_control.turn_mode = ATURN_RIGHT;
		           break;
//		case 0x06: automatic_control.turn_mode = straight;	           
//							 break;		
	  default: automatic_control.control_mode = ASTOP; //停止
		         break;   
	}  	
}


void ICData_Analyze(void)
{
	uint8_t i,j,m,buff[30] = {0};
	static uint8_t number = 0;
	
	for (i = 0;i < 27;i++)
  {
		if ((icbuff[i] == 0x7f)&(icbuff[i+1] != 0x7f))
		{
			for (j = 0;j < (27-i);j++)
			{
				buff[j] = icbuff[i+j];
//				if ((icbuff[i+j] == 0x7f)&(icbuff[i+j+1] == 0x7f))
//				{
//					
//				}
			}
			
			for (m = 0;m < i ;m++)
			{
					buff[j+m] = icbuff[m];
			}		
		}
	}
	
	if ((buff[0] == 0x7f) && (buff[26] != 0x00) && (buff[26] != latericbuff[26]))//已完整接收到数据且不重复使用（站点卡除外）
	{		
			for (i = 0;i<27;i++)   //保存读卡数据，除非读卡数据有误才再使用一次RxBuff
			{
				 latericbuff[i] = buff[i];
//         RxBuff[i] = 0x00;				
			}
			
//			LED1=!LED1;
			//解析并保存数据
		  if (latericbuff[10] == 0x01)     //判断是否是站点卡,0x01代表站点卡
			{				 
				if (latericbuff[11] == automatic_control.terminal_station)//如果相等说明到了目的站点
				{
           automatic_control.control_mode = ATEMP_STOP; //车体停止
					 if (Read_IC_Count == 5)
					 {
							Read_IC_Count = 0;//清空计数
						  automatic_control.start_station = latericbuff[11];
						  automatic_control.start_line = latericbuff[12];
						  automatic_control.goal_station_count--;//
							SetTextValue(1, 52,latericbuff[11]);//发送当前站点号，且此时站点为起始站点
							delay_ms(100);
							SetTextValue(1, 68,latericbuff[12]);//发送当前站点号所在的线路号
							delay_ms(100);								
//							Twinkle_Status = TWINKLE_FREQUENCY + 2;//开始黄灯慢闪
//						  Light_Band_R = 1;
//				      Light_Band_B = 0;
//				      Light_Band_G = 1;
						  
						  //货物动作（自动或者手动）
						  
						  //判断且获取下个目标站点
						  if (automatic_control.goal_station_count > 0)
							{
								automatic_control.terminal_station = automatic_control.goal_station_buff[1]; //获取下一个目标站点
								for (i = 0;i < automatic_control.goal_station_count;i++)
								{
									automatic_control.goal_station_buff[i] = automatic_control.goal_station_buff[i+1];
								}								
							}
							else
							{
								automatic_control.goal_station_buff[0] = 0;								
							}
						}
					  else
			      {
							Read_IC_Count++;
              latericbuff[26] = 0x00;	//当为站点卡时需重复进入							
				    }
				 }					
			}
			else if ((latericbuff[10] == 0x02) && (automatic_control.start_line != automatic_control.terminal_line)) //0x02为路径卡
			{	
				
			}	
			else if (latericbuff[10] == 0x03) //0x03为变速卡
			{
				 if ((latericbuff[11] == 0x04)&&(latericbuff[12] == automatic_control.terminal_station))//功能码为0x04，代表快到站时变速且目标站点正确
				 {
            automatic_control.goal_speed_gear = latericbuff[13];
         }
         else if (latericbuff[11] == 0x05)//功能码为0x05，代表转弯时变速
				 {
					  if (latericbuff[14]	== 0x00) //转弯标志为0表示即将出弯
            {
							automatic_control.turn_mode = ASTRAIGHT;
              automatic_control.goal_speed_gear = latericbuff[13];
						}
            else                        //转弯标志为1表示即将入弯
						{						
							automatic_control.turn_mode = ATURN;
							automatic_control.goal_speed_gear = latericbuff[12];
						}
				 }					 
			}
	}
}
