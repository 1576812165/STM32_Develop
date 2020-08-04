
/* Includes ------------------------------------------------------------------*/
#include "IC.h"
/* Private macro -------------------------------------------------------------*/
//·��������Ϣ�϶�ʲ��ú궨�壬�������ֺͼ��
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

/********************************IC����Ϣ����****************************************************

                             IC�������ݾ���16���Ʊ�ʾ
1.�����ͣ�01 ��ʾվ�㿨��02 ��ʾ·������03 ��ʾ�Ӽ��ٿ�
  ת����ţ�0x01 ����ֱ��  0x02 ������ת  0x03 ������ת
	���ٿ������룺0x04 ����վ  0x05 ����ת��
2վ�㿨����Ϣ
��һ���ֽ�    �ڶ����ֽ�        �������ֽ�      
                                                                                  
���0x01��  ��ǰվ���    ��ǰվ���������·���

3.·��������Ϣ
��һ���ֽ�    �ڶ����ֽ�        �������ֽ�           ���ĸ��ֽ�    ������ֽ�           �������ֽ�           ���߸��ֽ�
                                                                                  
���0x02��  ��ȥ��վ���    վ���������·���       ת�����    ��ȥ��վ���        վ���������·���       ת�����

4.���ٿ�����Ϣ
��һ���ֽ�    �ڶ����ֽ�        �������ֽ�                 ���ĸ��ֽ�        ������ֽڣ�ע����������ǵ�վ��˴�д0�� 
                                                                                  
���0x03��    ������     ��վվ���/�����ٶ�        �쵽վ�ٶ�/�����ٶ�      ���䣨1��/���䣨0��
*************************************************************************************************/


void Get_Action_Commend(uint8_t number)
{
	switch(number)
	{
		case 0x00:break; //��ʾ�޶���		
		case 0x01: automatic_control.turn_mode = ASTRAIGHT;
		           break;	
		case 0x02: automatic_control.turn_mode = ATURN_LEFT;
		           break;		
	  case 0x03: automatic_control.turn_mode = ATURN_RIGHT;
		           break;
//		case 0x06: automatic_control.turn_mode = straight;	           
//							 break;		
	  default: automatic_control.control_mode = ASTOP; //ֹͣ
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
	
	if ((buff[0] == 0x7f) && (buff[26] != 0x00) && (buff[26] != latericbuff[26]))//���������յ������Ҳ��ظ�ʹ�ã�վ�㿨���⣩
	{		
			for (i = 0;i<27;i++)   //����������ݣ����Ƕ��������������ʹ��һ��RxBuff
			{
				 latericbuff[i] = buff[i];
//         RxBuff[i] = 0x00;				
			}
			
//			LED1=!LED1;
			//��������������
		  if (latericbuff[10] == 0x01)     //�ж��Ƿ���վ�㿨,0x01����վ�㿨
			{				 
				if (latericbuff[11] == automatic_control.terminal_station)//������˵������Ŀ��վ��
				{
           automatic_control.control_mode = ATEMP_STOP; //����ֹͣ
					 if (Read_IC_Count == 5)
					 {
							Read_IC_Count = 0;//��ռ���
						  automatic_control.start_station = latericbuff[11];
						  automatic_control.start_line = latericbuff[12];
						  automatic_control.goal_station_count--;//
							SetTextValue(1, 52,latericbuff[11]);//���͵�ǰվ��ţ��Ҵ�ʱվ��Ϊ��ʼվ��
							delay_ms(100);
							SetTextValue(1, 68,latericbuff[12]);//���͵�ǰվ������ڵ���·��
							delay_ms(100);								
//							Twinkle_Status = TWINKLE_FREQUENCY + 2;//��ʼ�Ƶ�����
//						  Light_Band_R = 1;
//				      Light_Band_B = 0;
//				      Light_Band_G = 1;
						  
						  //���ﶯ�����Զ������ֶ���
						  
						  //�ж��һ�ȡ�¸�Ŀ��վ��
						  if (automatic_control.goal_station_count > 0)
							{
								automatic_control.terminal_station = automatic_control.goal_station_buff[1]; //��ȡ��һ��Ŀ��վ��
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
              latericbuff[26] = 0x00;	//��Ϊվ�㿨ʱ���ظ�����							
				    }
				 }					
			}
			else if ((latericbuff[10] == 0x02) && (automatic_control.start_line != automatic_control.terminal_line)) //0x02Ϊ·����
			{	
				
			}	
			else if (latericbuff[10] == 0x03) //0x03Ϊ���ٿ�
			{
				 if ((latericbuff[11] == 0x04)&&(latericbuff[12] == automatic_control.terminal_station))//������Ϊ0x04������쵽վʱ������Ŀ��վ����ȷ
				 {
            automatic_control.goal_speed_gear = latericbuff[13];
         }
         else if (latericbuff[11] == 0x05)//������Ϊ0x05������ת��ʱ����
				 {
					  if (latericbuff[14]	== 0x00) //ת���־Ϊ0��ʾ��������
            {
							automatic_control.turn_mode = ASTRAIGHT;
              automatic_control.goal_speed_gear = latericbuff[13];
						}
            else                        //ת���־Ϊ1��ʾ��������
						{						
							automatic_control.turn_mode = ATURN;
							automatic_control.goal_speed_gear = latericbuff[12];
						}
				 }					 
			}
	}
}
