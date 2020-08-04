
#include "control.h"

Control_Mode_type car_control_mode = AUTOMATIC;
manual_para manual_control = {MSTOP,{LEFT_BAFFLE_RISE,RIGHT_BAFFLE_RISE},{LOW,FORWARD}};
automatic_para automatic_control = {ASTOP,ASTRAIGHT,{LEFT_BAFFLE_RISE,RIGHT_BAFFLE_RISE},{LOW,FORWARD},0};
_car_info car_info = {0};
NavInformatiom_Type NavAInformatiom = {{0},0,0,0,0,0};
PID PIDcontrol = {0};

void Get_Magneticsensor_Information(void)
{
	int16_t i;
		
	/****************************�Ŵ���������жϼ���ֵ��ʼ************************/
		NavAInformatiom.Sum = 0;
		/****************************�Ŵ�����A����жϼ���ֵ��ʼ************************/
		if(NavA1 == 0)
	  {
			NavAInformatiom.Nav[0].Value = 0.5;
		  NavAInformatiom.Nav[0].Status = 1;
			NavAInformatiom.Sum++;
	  }
	  else
	  {
		  NavAInformatiom.Nav[0].Value = 0;
		  NavAInformatiom.Nav[0].Status = 0;
	  }
	  if(NavA2 == 0)
	  {
			NavAInformatiom.Nav[1].Value =0.4375;
		  NavAInformatiom.Nav[1].Status = 1;
			NavAInformatiom.Sum++;
	  }
	  else
	  {
		  NavAInformatiom.Nav[1].Value = 0;
		  NavAInformatiom.Nav[1].Status = 0;
	  }
	  if(NavA3 == 0)
	  {
			NavAInformatiom.Nav[2].Value = 0.375;
		  NavAInformatiom.Nav[2].Status = 1;
			NavAInformatiom.Sum++;
	  }
	  else
	  {
		  NavAInformatiom.Nav[2].Value = 0;
		  NavAInformatiom.Nav[2].Status = 0;
	  }
	  if(NavA4 == 0)
	  {
			NavAInformatiom.Nav[3].Value = 0.3125;
		  NavAInformatiom.Nav[3].Status = 1;
			NavAInformatiom.Sum++;
	  }
	  else
	  {
		  NavAInformatiom.Nav[3].Value = 0;
		  NavAInformatiom.Nav[3].Status = 0;
	  }
	  if(NavA5 == 0)
	  {
			NavAInformatiom.Nav[4].Value = 0.25;
		  NavAInformatiom.Nav[4].Status = 1;
			NavAInformatiom.Sum++;
	  }
	  else
	  {
		  NavAInformatiom.Nav[4].Value = 0;
		  NavAInformatiom.Nav[4].Status = 0;
	  }
	  if(NavA6 == 0)
	  {
			NavAInformatiom.Nav[5].Value = 0.1875;
		  NavAInformatiom.Nav[5].Status = 1;
			NavAInformatiom.Sum++;
	  }
	  else
	  {
		  NavAInformatiom.Nav[5].Value = 0;
		  NavAInformatiom.Nav[5].Status = 0;
	  }
	  if(NavA7 == 0)
	  {
			NavAInformatiom.Nav[6].Value = 0.125;
		  NavAInformatiom.Nav[6].Status = 1;
			NavAInformatiom.Sum++;
	  }
	  else
	  {
		  NavAInformatiom.Nav[6].Value = 0;
		  NavAInformatiom.Nav[6].Status = 0;
	  }
	  if(NavA8 == 0)
	  {
			NavAInformatiom.Nav[7].Value = 0.0625;
		  NavAInformatiom.Nav[7].Status = 1;
		  NavAInformatiom.Sum++;
	  }
	  else
	  {
		  NavAInformatiom.Nav[7].Value = 0;
		  NavAInformatiom.Nav[7].Status = 0;
	  }
    if(NavA9 == 0)
	  {
			NavAInformatiom.Nav[8].Value = -0.0625;
		  NavAInformatiom.Nav[8].Status = 1;
			NavAInformatiom.Sum++;
	  }
	  else
	  {
		  NavAInformatiom.Nav[8].Value = 0;
		  NavAInformatiom.Nav[8].Status = 0;
	  }
	  if(NavA10 == 0)
	  {
			NavAInformatiom.Nav[9].Value = -0.125;
		  NavAInformatiom.Nav[9].Status = 1;
			NavAInformatiom.Sum++;
	  }
	  else
	  {
		  NavAInformatiom.Nav[9].Value = 0;
		  NavAInformatiom.Nav[9].Status = 0;
	  }
	  if(NavA11 == 0)
	  {
			NavAInformatiom.Nav[10].Value = -0.1875;
		  NavAInformatiom.Nav[10].Status = 1;
			NavAInformatiom.Sum++;
	  }
	  else
	  {
		  NavAInformatiom.Nav[10].Value = 0;
		  NavAInformatiom.Nav[10].Status = 0;
	  }
	  if(NavA12 == 0)
	  {
			NavAInformatiom.Nav[11].Value = -0.25;
		  NavAInformatiom.Nav[11].Status = 1;
			NavAInformatiom.Sum++;
	  }
	  else
	  {
		  NavAInformatiom.Nav[11].Value = 0;
		  NavAInformatiom.Nav[11].Status = 0;
	  }
	  if(NavA13 == 0)
	  {
			NavAInformatiom.Nav[12].Value = -0.3125;
		  NavAInformatiom.Nav[12].Status = 1;
			NavAInformatiom.Sum++;
	  }
	  else
	  {
		  NavAInformatiom.Nav[12].Value = 0;
		  NavAInformatiom.Nav[12].Status = 0;
	  }
	  if(NavA14 == 0)
	  {
			NavAInformatiom.Nav[13].Value = -0.375;
		  NavAInformatiom.Nav[13].Status = 1;
			NavAInformatiom.Sum++;
	  }
	  else
	  {
		  NavAInformatiom.Nav[13].Value = 0;
		  NavAInformatiom.Nav[13].Status = 0;
	  }
	  if(NavA15 == 0)
	  {
			NavAInformatiom.Nav[14].Value = -0.4375;
		  NavAInformatiom.Nav[14].Status = 1;
			NavAInformatiom.Sum++;
	  }
	  else
	  {
		  NavAInformatiom.Nav[14].Value = 0;
		  NavAInformatiom.Nav[14].Status = 0;
	  }
	  if(NavA16 == 0)
	  {
			NavAInformatiom.Nav[15].Value = -0.5;
		  NavAInformatiom.Nav[15].Status = 1;
			NavAInformatiom.Sum++;
	  }
	  else
	  {
		  NavAInformatiom.Nav[15].Value = 0;
		  NavAInformatiom.Nav[15].Status = 0;
	  }
	  /****************************�Ŵ���������жϼ���ֵ����************************/
		
		//��ԭ�ŵ��������жϷ�Χ
    NavAInformatiom.StartJudgeNumber = 0;
    NavAInformatiom.EndJudgeNumber = 16;

	//��ȡ�ŵ������㷶Χ
	if (automatic_control.turn_mode == ASTRAIGHT)
	{
        for (i= 0;i < 16;i++)
        {
			     //��ôŵ���������Χ
			     if ((NavAInformatiom.ChangCount == 0) &&(NavAInformatiom.Nav[i].Status == 1))   
			     {
				      NavAInformatiom.StartJudgeNumber = i;
				      NavAInformatiom.ChangCount += 1;
			     }
           if ((NavAInformatiom.ChangCount == 1) &&(NavAInformatiom.Nav[i].Status == 0))
			     {
				      NavAInformatiom.EndJudgeNumber = i;
				      break;
			     }				
		    }
			 
				//���ֱ��ģʽ�£��ŵ���������ΧΪ�����ŵ�����˵����ʱΪʮ��·�ڣ�ֱ��
				if ((NavAInformatiom.StartJudgeNumber == 0) && (NavAInformatiom.EndJudgeNumber == 16))
				{
					 NavAInformatiom.StartJudgeNumber = 5;
					 NavAInformatiom.EndJudgeNumber = 11;
					
					 for (i = 0;i < 3; i++)
					 {
						  NavAInformatiom.Nav[i].Status = 0;
              NavAInformatiom.Nav[i + 13].Status = 0;						
					 }					
				}
				//���ֱ��ģʽ�£��ŵ��������������5����˵���в������ʱ���ù̶�5���ŵ���λ��
				else if ((NavAInformatiom.EndJudgeNumber - NavAInformatiom.StartJudgeNumber) > 6)
				{
					 //����8˵�����ŵ���ƫ����NavAInformatiom.EndJudgeNumber
					 if (((NavAInformatiom.StartJudgeNumber + NavAInformatiom.EndJudgeNumber)/2) > 8) 
					 {
						  if ((NavAInformatiom.StartJudgeNumber + 6) < 16)
							{
					       for (i = 0;i < 3; i++)
					       {
						       NavAInformatiom.Nav[i].Status = 0;
                   NavAInformatiom.Nav[i + 13].Status = 0;						
					       }
								 NavAInformatiom.EndJudgeNumber = NavAInformatiom.StartJudgeNumber + 6;
							}
							else
							{
								NavAInformatiom.EndJudgeNumber = 15;								
							}
					 }
					 else if (((NavAInformatiom.StartJudgeNumber + NavAInformatiom.EndJudgeNumber)/2) < 7)
					 {
						  if ((NavAInformatiom.EndJudgeNumber - 6) > 0)
							{
					       for (i = 0;i < 3; i++)
					       {
						       NavAInformatiom.Nav[i].Status = 0;
                   NavAInformatiom.Nav[i + 13].Status = 0;						
					       }							
								NavAInformatiom.StartJudgeNumber = NavAInformatiom.EndJudgeNumber - 6;								
							}
							else
							{
								NavAInformatiom.StartJudgeNumber = 0;								
							}						  
					 }
				}
	}
  else if (automatic_control.turn_mode == ATURN_LEFT)
  {
        for (i= 0;i < 16;i++)
        {
			     //��ôŵ���������Χ
			     if (NavAInformatiom.Nav[i].Status == 1)   
			     {
				      NavAInformatiom.StartJudgeNumber = i;
              break;
			     }					 
		    }
				if ((NavAInformatiom.StartJudgeNumber + 6) <= 16)
				{
          NavAInformatiom.EndJudgeNumber = NavAInformatiom.StartJudgeNumber + 6;
				}      			
	}
  else if (automatic_control.turn_mode == ATURN_RIGHT)
  {
        for (i= 15;i >= 0;i--)
        {
			     //��ôŵ���������Χ
			     if (NavAInformatiom.Nav[i].Status == 1)   
			     {
				      NavAInformatiom.EndJudgeNumber = i + 1;
				      break;
			     }
				}
				if (NavAInformatiom.EndJudgeNumber - 6 >= 0)
				{
          NavAInformatiom.StartJudgeNumber = NavAInformatiom.EndJudgeNumber - 6;
				} 			
	}
  NavAInformatiom.ChangCount = 0;	
}


	
//�����Ƕ�ȡ���������Ҳ���ǻ�õ�ǰֵ�����������ǰ���ֵ
void Calculate_Error(PID *pp)
{
	int16_t i = 0;
	
  //�ж����Ʒ�ʽ����ÿ���ƫ����	
	  if (NavAInformatiom.Sum != 0) //δ�ѹ�ʱ����������
	  {
			 for(i = NavAInformatiom.StartJudgeNumber;i < NavAInformatiom.EndJudgeNumber;i++)
	     {
   	     if (NavAInformatiom.Nav[i].Status == 1) 
  		   {
  			   NavAInformatiom.Average += NavAInformatiom.Nav[i].Value;
  		   } 			
  	   }
		   NavAInformatiom.Average /= (float)(NavAInformatiom.EndJudgeNumber - NavAInformatiom.StartJudgeNumber);
//			 sendware_buffer[0] = NavAInformatiom.Average;
	
       pp->Error[0] = NavAInformatiom.Average;

//		   sendware_buffer[1] = pp->Error[0];
			
		   NavAInformatiom.Average = 0;	

			 if (car_info.status.bit.nav_status_with_screen_control == 1) 
			 {
					
					SetTextStrings(1,50,"Normal"); //�ŵ����ڹ�
					delay_ms(100);
					car_info.status.bit.nav_status_with_screen_control = 0;
					if (car_info.status.all == 0)
					{
						//�׵�������˸
//						Twinkle_Status = TWINKLE_FREQUENCY + 3;
//						Light_Band_R = 1;
//				    Light_Band_B = 1;
//				    Light_Band_G = 1;
//						Alarm_Band_R=0;
					}
			 }			 
	  }
	  else
	  {
			 automatic_control.control_mode = ASTOP; //����ֹͣ
			 if (car_info.status.bit.nav_status_with_screen_control == 0) 
			 {
//					Alarm_Band_R=1;
//					//��Ƴ���
//					Twinkle_Status = 1;
//				  Light_Band_R = 1;
//				  Light_Band_B = 0;
//				  Light_Band_G = 0;
					SetTextStrings(1,50,"Alarm"); //�ŵ������ڹ�			  
					delay_ms(100);
					car_info.status.bit.nav_status_with_screen_control = 1;
			 }
	  }	
}

void Global_Speed_Control(float *Out_Speed)
{
			if (automatic_control.control_mode == ATEMP_STOP) 
			{
				  if (*Out_Speed > 10) //ƫ��ϴ�ʱ�����ټ��٣���ֹ���³���ƫ�����
					{	 
						  *Out_Speed -= Speed_Data[automatic_control.current_speed_gear].bit.speed_change_value[0];
					}
          else
					{
              *Out_Speed = 0;
					}						
			}
			else if (automatic_control.control_mode == ASTOP)
			{
				MOTOR_DISABLE
				car_control_mode = MANUAL;
				manual_control.turn_Mode = MSTOP;
			}
			else 
			{
					 if ((NavAInformatiom.Nav[15].Status != 0) || (NavAInformatiom.Nav[14].Status != 0) 
						   || (NavAInformatiom.Nav[13].Status != 0) || (NavAInformatiom.Nav[0].Status != 0)
					     || (NavAInformatiom.Nav[1].Status != 0) || (NavAInformatiom.Nav[2].Status != 0))
					 {        
							if (*Out_Speed > 10) //ƫ��ϴ�ʱ����ͬʱ���PIDʹ����ٻع�
							{	 
								 *Out_Speed -= 1;
							}
					 } 
					 else   //ƫ�������ָ��ٶ�
					 {
							 if (fabs(*Out_Speed - Speed_Data[automatic_control.goal_speed_gear].bit.speed_value) > 10.0)
							 {
                   if (automatic_control.goal_speed_gear > automatic_control.current_speed_gear)
                   {								 
											*Out_Speed += Speed_Data[automatic_control.goal_speed_gear].bit.speed_change_value[automatic_control.current_speed_gear];
									 }
									 else if (automatic_control.goal_speed_gear < automatic_control.current_speed_gear)
									 {
										  *Out_Speed -= Speed_Data[automatic_control.current_speed_gear].bit.speed_change_value[automatic_control.goal_speed_gear];
									 }
									 else
									 {
										  if ((uint8_t)*Out_Speed < (Speed_Data[automatic_control.goal_speed_gear].bit.speed_value))
										  {
												  *Out_Speed += 1;
											}
									 }
							 }
               else
							 {
	                  *Out_Speed = Speed_Data[automatic_control.goal_speed_gear].bit.speed_value;
                    if (automatic_control.current_speed_gear != automatic_control.goal_speed_gear) 
										{ 
											automatic_control.current_speed_gear = automatic_control.goal_speed_gear;
										}											
							 }								 
					 }				
			}
}

void Global_PID_Control(float *Out_Speed,PID *pp)
{
			if (automatic_control.control_mode == ATEMP_STOP)
			{
				 if (automatic_control.current_speed_gear == 0)
				 {
					 PIDInit(pp,Speed_Data[automatic_control.current_speed_gear].bit.PID[4],Speed_Correction_Data[automatic_control.current_speed_gear].bit.PID[4]);
				 }
         else
				 {
           PIDInit(pp,Speed_Data[automatic_control.current_speed_gear].bit.PID[2],Speed_Correction_Data[automatic_control.current_speed_gear].bit.PID[2]);
				 }					 
			}
			else if (automatic_control.turn_mode == ASTRAIGHT) 
			{
					 if ((NavAInformatiom.Nav[15].Status != 0) || (NavAInformatiom.Nav[14].Status != 0) 
						  || (NavAInformatiom.Nav[13].Status != 0) || (NavAInformatiom.Nav[0].Status != 0)
					    || (NavAInformatiom.Nav[1].Status != 0) || (NavAInformatiom.Nav[2].Status != 0))
					 {        
              PIDInit(pp,Speed_Data[automatic_control.current_speed_gear].bit.PID[0],Speed_Correction_Data[automatic_control.current_speed_gear].bit.PID[0]);
					 }						 
					 else   //ƫ�������ָ��ٶ�
					 {					 
              PIDInit(pp,Speed_Data[automatic_control.current_speed_gear].bit.PID[1],Speed_Correction_Data[automatic_control.current_speed_gear].bit.PID[1]);							 
					 }				
			}
			else if ((automatic_control.turn_mode == ATURN_LEFT)||(automatic_control.turn_mode == ATURN_RIGHT)||(automatic_control.turn_mode == ATURN))
			{		 
           PIDInit(pp,Speed_Data[automatic_control.current_speed_gear].bit.PID[3],Speed_Correction_Data[automatic_control.current_speed_gear].bit.PID[3]);			 
			}			
}




////Ϊ2ʱ����ֹͣ����������Ч��Ϊ0ʱ�Դ�ʱ����ŵ���������Ϊ��׼ֹͣ
//void Car_Stop(uint8_t STATUS,float Out_temp)
//{
//	float LMotor_Out = 0,RMotor_Out = 0;
//		
//  if (STATUS == 2)     //
//  {
//    Set_Motor_Out(0,0);
//  }
//  else if (STATUS == 0)
//  {
//  	LMotor_Out = 0 + Out_temp;
//		RMotor_Out = 0 - Out_temp;
//		
//		//�޷�
//	  if (LMotor_Out > 100) LMotor_Out = 100;
//	  if (RMotor_Out > 100) RMotor_Out = 100;
//	
//    if (LMotor_Out < 0) LMotor_Out = 0;
//	  if (RMotor_Out < 0) RMotor_Out = 0;
//		
//		Set_Motor_Out(LMotor_Out,RMotor_Out);
//  }	
//}

//������������ƣ�Ҳ�������Ǽ�����Ŀ���ƫ������������ȥִ�У�
//�ԴﵽԤ�ڵĿ���Ŀ�ꡣ
void Car_Move_Out(float *current_speed,PID *pp)
{
	float Out_temp = 0,RMotor_Out = 0,LMotor_Out = 0;

	Out_temp = PIDCal(pp);                //λ�þ�������������
  
	RMotor_Out = *current_speed - Out_temp;
	LMotor_Out = *current_speed + Out_temp;
	
  //�޷�
	if (LMotor_Out > 100) LMotor_Out = 100;
	if (RMotor_Out > 100) RMotor_Out = 100;
	
  if (LMotor_Out < 0) LMotor_Out = 0;
	if (RMotor_Out < 0) RMotor_Out = 0;
	
	
//	sendware_buffer[2] = (float)LMotor_Out;
//	sendware_buffer[3] = (float)RMotor_Out;
//	vcan_sendware(sendware_buffer,sizeof(sendware_buffer));	
	   Set_Motor_Out(LMotor_Out,RMotor_Out);
}

void Car_Move_control(void)
{  	
	if ((IODATA.bits.SW5 == 0)&&(current_screen_id != 5))//��ȫ���߼��
	{
    MOTOR_DISABLE
		manual_control.turn_Mode = MSTOP;
		automatic_control.control_mode = ASTOP;
		if (car_info.status.bit.safety_stop_flag == 0)		
	  {
			  SetControlCmd(1,60,DISABLE);//��������
			  delay_ms(100);
			  SetTextStrings(1,85,"Alarm"); //���ߴ����������������
			  delay_ms(100);
			  Can_Send_Msg(numS,8);
//        Alarm_Band_R=1;
//			  Twinkle_Status = 1;//��Ƴ���
//			  Light_Band_R = 1;
//				Light_Band_B = 0;
//				Light_Band_G = 0;
        SetControlCmd(1,94,DISABLE);//���ù�Ͳ�ؼ�����
        delay_ms(100);
        SetControlCmd(1,95,DISABLE);//���ù�Ͳ�ؼ�����
        delay_ms(100);		    
        SetControlForeColor(1,93,WHITE);
			  delay_ms(100);
		    SetControlForeColor(1,91,WHITE);
			  delay_ms(100);     
		}
    car_info.status.bit.safety_stop_flag = 1;		
	}
  else if (IODATA.bits.K1 == 0) //��ͣK5��Ӧ���жϱ�����U33��D4����Ϊ0��Ϊ���¼�ͣ
	{
     MOTOR_DISABLE
		 manual_control.turn_Mode = MSTOP;
		 automatic_control.control_mode = ASTOP;
     if (car_info.status.bit.emergency_stop_flag == 0) 
		 {
			  Can_Send_Msg(numS,8);
//        Alarm_Band_R=1;
//			  Twinkle_Status = 1;//��Ƴ���
//			  Light_Band_R = 1;
//				Light_Band_B = 0;
//				Light_Band_G = 0;
        SetControlCmd(1,94,DISABLE);//���ù�Ͳ�ؼ�����
        delay_ms(100);
        SetControlCmd(1,95,DISABLE);//���ù�Ͳ�ؼ�����
        delay_ms(100);		    
        SetControlForeColor(1,93,WHITE);
			  delay_ms(100);
		    SetControlForeColor(1,91,WHITE);
			  delay_ms(100);
		 }
     car_info.status.bit.emergency_stop_flag = 1;		
	}
	else if ((IODATA.bits.Alarm1 == 1)||(IODATA.bits.Alarm2 == 1))//������������Ƿ�����
	{
		  MOTOR_DISABLE
		  manual_control.turn_Mode = MSTOP;
		  automatic_control.control_mode = ASTOP;
		  if (car_info.status.bit.motor_alarm_flag == 0)		
	    {
		    SetTextStrings(1,51,"Alarm"); //�������������������
			  delay_ms(100);
//        Twinkle_Status = 1;//��Ƴ���
//			  Light_Band_R = 1;
//				Light_Band_B = 0;
//				Light_Band_G = 0;
//        Alarm_Band_R=1;
		  }
      car_info.status.bit.motor_alarm_flag = 1;		
	} 
  else
	{
		if (car_info.status.bit.motor_alarm_flag == 1)		
	  {
		    SetTextStrings(1,51,"Normal"); //����������������
			  delay_ms(100);
			  car_info.status.bit.motor_alarm_flag = 0;
				if (car_info.status.all == 0)
				{
//					Twinkle_Status = TWINKLE_FREQUENCY + 2;//��ʼ�Ƶ�����
//					Light_Band_R = 1;
//				  Light_Band_B = 0;
//				  Light_Band_G = 1;
//					Alarm_Band_R=0;
				}
		}			
			
    if (car_info.status.bit.emergency_stop_flag == 1) 
    {
			 SetControlCmd(1,60,ENABLE);//ʹ������
			 delay_ms(100);
		   car_info.status.bit.emergency_stop_flag = 0;//��ռ�ͣ״̬��־
       SetControlCmd(1,94,ENABLE);//ʹ�ܹ�Ͳ�ؼ�����
       delay_ms(100);
       SetControlCmd(1,95,ENABLE);//ʹ�ܹ�Ͳ�ؼ�����
       delay_ms(100);
			 if (car_info.status.all == 0)
			 {
//					Twinkle_Status = TWINKLE_FREQUENCY + 2;//��ʼ�Ƶ�����
//					Light_Band_R = 1;
//				  Light_Band_B = 0;
//				  Light_Band_G = 1;
//					Alarm_Band_R=0;
			 }
		}
		
		if ((IODATA.bits.K3 == 0)&&(current_screen_id != 5))//ֹͣ��ť����
		{
		    manual_control.turn_Mode = MSTOP;
		    automatic_control.control_mode = ASTOP;
			  car_info.status.bit.nav_status_with_screen_control = 0;
			  if (car_info.status.bit.safety_stop_flag == 1)		
	      {
					 SetControlCmd(1,60,ENABLE);//ʹ������
					 delay_ms(100);
					 car_info.status.bit.safety_stop_flag = 0;
		       SetTextStrings(1,85,"Normal"); //���ߴ����������������
			     delay_ms(100);
					 if (car_info.status.all == 0)
					 {
//             Twinkle_Status = TWINKLE_FREQUENCY + 2;//��ʼ�Ƶ�����
//					   Light_Band_R = 1;
//				     Light_Band_B = 0;
//				     Light_Band_G = 1;
//             Alarm_Band_R=0;
					 }
				}
		}
		else if ((IODATA.bits.K4 == 0) && (automatic_control.terminal_station != 0) && (current_screen_id != 5))//������ť����
		{
			
			/**              ��Ҫ����һ���Ƿ�����ʼվ��                         ***/
//		     Twinkle_Status = 4;//�̵Ƴ���
//		     Light_Band_R = 0;
//		     Light_Band_B = 0;
//		     Light_Band_G = 1;				
  			 //���Ŀ���ٶȵ�λΪ0������������ǵ����յ��ֹͣ�ģ�
			   //��ʱ�������������ΪĿ���ٶȣ�����ֻ��ʹ�õ�ǰ��Ŀ���ٶȵ�λֵ����
         if (automatic_control.goal_speed_gear == 0) 			
  		   {
					 automatic_control.goal_speed_gear = 6;
           car_control_mode = AUTOMATIC;
					 automatic_control.control_mode = ASTART;
           automatic_control.turn_mode = ASTRAIGHT;					 
  			 }
				 else
				 {
					 car_control_mode = AUTOMATIC;
					 automatic_control.control_mode = ASTART;
					 automatic_control.turn_mode = ASTRAIGHT;					 
				 }
		     //����λ���ϱ�����״��������λ�ã��ٶȵȣ�
		}
		
		if (automatic_control.control_mode == ASTOP)
		{
        MOTOR_DISABLE
			  Nav_Station_test();
//			  Deal_With_ICData();                 //IC�����ݴ���				
//	      Get_Magneticsensor_Information();   //���ʹ�õĴŵ�����Ϣ
//	      Calculate_Error(&PIDcontrol);       //����ƫ��
		}
		else if (car_control_mode == AUTOMATIC) //�Զ�ģʽ��Ҳû����ֹͣ��
		{
        MOTOR_ENABLE
        ICData_Analyze();                 //IC�����ݴ���				
	      Get_Magneticsensor_Information();   //���ʹ�õĴŵ�����Ϣ
	      Calculate_Error(&PIDcontrol);       //����ƫ��
				Global_Speed_Control(&(automatic_control.current_speed)); //�����ٶ�			
        Global_PID_Control(&(automatic_control.current_speed),&PIDcontrol);	  //����pid����	        			
	      Car_Move_Out(&(automatic_control.current_speed),&PIDcontrol);		      //PID���㼰����������
	   }
	   else if (car_control_mode == MANUAL) //������ģʽ
	   {
				Get_Magneticsensor_Information();
				if (NavAInformatiom.Sum != 0) //˵���ڴ�����
				{
//          //�׵�������˸
//			    Twinkle_Status = TWINKLE_FREQUENCY + 3;
//					Light_Band_R = 1;
//				  Light_Band_B = 1;
//				  Light_Band_G = 1;					
				}
				else if (car_info.status.bit.nav_status_with_screen_control == 1)
				{
//          //���������˸
//          Twinkle_Status = 1;
//					Light_Band_R = 1;
//				  Light_Band_B = 0;
//				  Light_Band_G = 0;
				}
				
			  if (manual_control.turn_Mode == MSTOP)
				{
			    	MOTOR_DISABLE
			      if (car_info.status.bit.safety_stop_flag == 1)		
	          {
					    car_info.status.bit.safety_stop_flag = 0;
							SetTextStrings(1,85,"Normal"); //���ߴ����������������
							delay_ms(100);
							if (car_info.status.all == 0)
							{
//								Twinkle_Status = TWINKLE_FREQUENCY + 2;//��ʼ�Ƶ�����
//					      Light_Band_R = 1;
//				        Light_Band_B = 0;
//				        Light_Band_G = 1;
//								Alarm_Band_R=0;
							}
				    }
						car_info.status.bit.nav_status_with_screen_control = 0;
				}
				else
				{
			    	MOTOR_ENABLE					
				}
			 
			  if (manual_control.turn_Mode == MFORWARD)
        {
					 Motor_Reverse(LMOTOR_BACK_STATUS_OFF,RMOTOR_BACK_STATUS_OFF);
           Set_Motor_Out(10,10);
				}
        else if (manual_control.turn_Mode == MBACKWARD)
				{
					 Motor_Reverse(LMOTOR_BACK_STATUS_ON,RMOTOR_BACK_STATUS_ON);
           Set_Motor_Out(10,10);
				}
        else if (manual_control.turn_Mode == MTURN_LEFT)
				{
					 Motor_Reverse(LMOTOR_BACK_STATUS_OFF,RMOTOR_BACK_STATUS_OFF);
           Set_Motor_Out(0,10);
				}
        else if (manual_control.turn_Mode == MTURN_RIGHT)
				{
					 Motor_Reverse(LMOTOR_BACK_STATUS_OFF,RMOTOR_BACK_STATUS_OFF);
           Set_Motor_Out(10,0);
				}
        else if (manual_control.turn_Mode == MRIGHT_HANDED)
				{
					 Motor_Reverse(LMOTOR_BACK_STATUS_OFF,RMOTOR_BACK_STATUS_ON);
           Set_Motor_Out(10,10);
				}
        else if (manual_control.turn_Mode == MLEFT_HANDED)
				{
					 Motor_Reverse(LMOTOR_BACK_STATUS_ON,RMOTOR_BACK_STATUS_OFF);
           Set_Motor_Out(10,10);
				}				
	   }
	}
}

void Roller_With_Screen(uint8_t before_status,uint8_t rear_status,uint8_t roller_direction)
{
	if (roller_direction) //Ϊ0��ʾ���˶�
	{
		if (roller_direction == 1)//��ʾ��ǰ�˶�
		{
		  if (before_status == 0)//��ʾǰ���嵽���λ����ʱ��Ͳ�ſ�����ǰ�˶�
			{
				 if (automatic_control.roller_mode.speed_mode == LOW)
				 {
					 Can_Send_Msg(numspeed_l,8);delay_ms(5);Can_Send_Msg(numZ,8);
				 }
         else if (automatic_control.roller_mode.speed_mode == MEDIUM)
				 {
           Can_Send_Msg(numspeed_m,8);delay_ms(5);Can_Send_Msg(numZ,8);
				 }
         else if (automatic_control.roller_mode.speed_mode == HIGH)
				 {
           Can_Send_Msg(numspeed_h,8);delay_ms(5);Can_Send_Msg(numZ,8);
				 }
     	   roller_direction = 0;//��0����ֹ�ظ�����				
			}
		}
		else if (roller_direction == 2)//��ʾ����˶�
    {
		  if (rear_status == 0)//��ʾ�󵲰嵽���λ����ʱ��Ͳ������ǰ�˶�
			{
				 if (automatic_control.roller_mode.speed_mode == LOW)
				 {
					 Can_Send_Msg(numspeed_l,8);delay_ms(5);Can_Send_Msg(numF,8);
				 }
         else if (automatic_control.roller_mode.speed_mode == MEDIUM)
				 {
           Can_Send_Msg(numspeed_m,8);delay_ms(5);Can_Send_Msg(numF,8);
				 }
         else if (automatic_control.roller_mode.speed_mode == HIGH)
				 {
           Can_Send_Msg(numspeed_h,8);delay_ms(5);Can_Send_Msg(numF,8);
				 }
     	  roller_direction = 0;//��0����ֹ�ظ�����				
			}
		}	
	}
}


void Nav_Station_test(void)
{
	uint8_t i,j,m,buff[30] = {0};
	
    Get_Magneticsensor_Information();
    if (NavAInformatiom.Sum != 0) //˵���ڴ�����
		{
      if (car_info.status.bit.nav_status_with_screen_control == 1) 
		  {
				
			 	SetTextStrings(1,50,"Normal"); //�ŵ����ڹ�
			  delay_ms(100);
				car_info.status.bit.nav_status_with_screen_control = 0;
				if (car_info.status.all == 0)
				{
//					//�׵�������˸
//					Twinkle_Status = TWINKLE_FREQUENCY + 3;
//					Light_Band_R = 1;
//				  Light_Band_B = 1;
//				  Light_Band_G = 1;
//					Alarm_Band_R=0;
				}
		  }
		}
    else//�����ڴ�����
		{
      if (car_info.status.bit.nav_status_with_screen_control == 0) 
		  {
			 	SetTextStrings(1,50,"Alarm"); //�ŵ������ڹ�
			  delay_ms(100);
				car_info.status.bit.nav_status_with_screen_control = 1;
//        //���������˸
//			  Twinkle_Status = TWINKLE_FREQUENCY + 1;
//			  Light_Band_R = 1;
//				Light_Band_B = 0;
//				Light_Band_G = 0;
//	      Alarm_Band_R=1;
		  }		
		}
	
	  //��ʼ�ж��Ƿ���������,Ϊ0��ʾδ������
//	  if ((automatic_control.running_status == 0)&&(Twinkle_Status%10 == 3)&&(automatic_control.start_station == 0))//˵����ֹͣ���������ϵ�,���ڴŵ����� 
//	  {
//				for (i = 0;i < 27;i++)
//				{
//					if (RxBuff[i] == 0x7f)
//					{
//						for (j = 0;j < (27-i);j++)
//						{
//							buff[j] = RxBuff[i+j];
//						}
//						
//						for (m = 0;m < i ;m++)
//						{
//								buff[j+m] = RxBuff[m];
//						}		
//					}
//				}			
//				if ((buff[0] == 0x7f) && (buff[26] != 0x00) && (buff[26] != RxBuffLast[26]))//���������յ������Ҳ��ظ�ʹ�ã�վ�㿨���⣩
//				{		
//						for (uint8_t i = 0;i<27;i++)   //����������ݣ����Ƕ��������������ʹ��һ��RxBuff
//						{
//							 RxBuffLast[i] = buff[i];
//			//         RxBuff[i] = 0x00;				
//						}
//						LED1=!LED1;
//						//�������ݼ���
//						AT24CXX_Read(MEMORY_ADRESSS15,Control_Data.all,10);
//						 //�ж��Ƿ���վ����
//						if ((RxBuffLast[10] == 0x01)&&(RxBuffLast[11] == automatic_control.start_station)&&(RxBuffLast[12] == automatic_control.start_line))//�ͱ������ʼվ����ͬ������ֹͣ��δ�ƶ�,ֻ�轫������������ʾ
//						{
//						 //��ʾ��ǰ��Ϣ����վ��š���ͷ���򡢵�ǰ��·
//							SetTextValue(1, 52,automatic_control.start_station);//���͵�ǰվ��ţ��Ҵ�ʱվ��Ϊ��ʼվ��
//							delay_ms(100);
//							SetTextValue(1, 68,automatic_control.start_line);//���͵�ǰվ������ڵ���·��
//						  delay_ms(100);
//						  Twinkle_Status = TWINKLE_FREQUENCY + 2;
////						  USART5_Send_To_Computer(14,0,0,0,automatic_control.direction_mode,automatic_control.start_station,5);
//						  //��ǰ�����ж�
//						  //�ȶ���ǰ��·������Ϣ������ǰվ�㲻�ڸ���·���ˣ����ڵ�ǰվ��ŵ�EEPROM����ǰ������ȡ������·�ϱȵ�ǰվ��С�����վ��ţ��ٸ��ݳ�ͷ�������С�ж����ĸ�վ���
//						 
//					 }
//					 else //�������������0
//					 {
//							memsett(Control_Data.all,0,10);
//					 }
//				 }
//		}				
}

