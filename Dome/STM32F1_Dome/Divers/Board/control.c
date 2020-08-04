
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
		
	/****************************磁传感器检测判断及赋值开始************************/
		NavAInformatiom.Sum = 0;
		/****************************磁传感器A检测判断及赋值开始************************/
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
	  /****************************磁传感器检测判断及赋值结束************************/
		
		//复原磁导航引导判断范围
    NavAInformatiom.StartJudgeNumber = 0;
    NavAInformatiom.EndJudgeNumber = 16;

	//获取磁导航计算范围
	if (automatic_control.turn_mode == ASTRAIGHT)
	{
        for (i= 0;i < 16;i++)
        {
			     //获得磁导航引导范围
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
			 
				//如果直走模式下，磁导航引导范围为整个磁导航，说明此时为十字路口，直走
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
				//如果直走模式下，磁导航个数如果大于5个，说明有岔道，此时采用固定5个磁导航位数
				else if ((NavAInformatiom.EndJudgeNumber - NavAInformatiom.StartJudgeNumber) > 6)
				{
					 //大于8说明，磁导航偏向于NavAInformatiom.EndJudgeNumber
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
			     //获得磁导航引导范围
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
			     //获得磁导航引导范围
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


	
//功能是读取输入变量，也就是获得当前值，进而算出当前误差值
void Calculate_Error(PID *pp)
{
	int16_t i = 0;
	
  //判定控制方式及获得控制偏差量	
	  if (NavAInformatiom.Sum != 0) //未脱轨时矫正量计算
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
					
					SetTextStrings(1,50,"Normal"); //磁导航在轨
					delay_ms(100);
					car_info.status.bit.nav_status_with_screen_control = 0;
					if (car_info.status.all == 0)
					{
						//白灯慢速闪烁
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
			 automatic_control.control_mode = ASTOP; //车体停止
			 if (car_info.status.bit.nav_status_with_screen_control == 0) 
			 {
//					Alarm_Band_R=1;
//					//红灯常亮
//					Twinkle_Status = 1;
//				  Light_Band_R = 1;
//				  Light_Band_B = 0;
//				  Light_Band_G = 0;
					SetTextStrings(1,50,"Alarm"); //磁导航不在轨			  
					delay_ms(100);
					car_info.status.bit.nav_status_with_screen_control = 1;
			 }
	  }	
}

void Global_Speed_Control(float *Out_Speed)
{
			if (automatic_control.control_mode == ATEMP_STOP) 
			{
				  if (*Out_Speed > 10) //偏差较大时先慢速减速，防止导致车体偏轨过大
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
							if (*Out_Speed > 10) //偏差较大时减速同时配合PID使其快速回归
							{	 
								 *Out_Speed -= 1;
							}
					 } 
					 else   //偏离回来后恢复速度
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
					 else   //偏离回来后恢复速度
					 {					 
              PIDInit(pp,Speed_Data[automatic_control.current_speed_gear].bit.PID[1],Speed_Correction_Data[automatic_control.current_speed_gear].bit.PID[1]);							 
					 }				
			}
			else if ((automatic_control.turn_mode == ATURN_LEFT)||(automatic_control.turn_mode == ATURN_RIGHT)||(automatic_control.turn_mode == ATURN))
			{		 
           PIDInit(pp,Speed_Data[automatic_control.current_speed_gear].bit.PID[3],Speed_Correction_Data[automatic_control.current_speed_gear].bit.PID[3]);			 
			}			
}




////为2时自由停止且其后参数无效，为0时以此时背面磁导航的中央为基准停止
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
//		//限幅
//	  if (LMotor_Out > 100) LMotor_Out = 100;
//	  if (RMotor_Out > 100) RMotor_Out = 100;
//	
//    if (LMotor_Out < 0) LMotor_Out = 0;
//	  if (RMotor_Out < 0) RMotor_Out = 0;
//		
//		Set_Motor_Out(LMotor_Out,RMotor_Out);
//  }	
//}

//功能是输出控制，也就是我们计算出的控制偏差传入这个函数中去执行，
//以达到预期的控制目标。
void Car_Move_Out(float *current_speed,PID *pp)
{
	float Out_temp = 0,RMotor_Out = 0,LMotor_Out = 0;

	Out_temp = PIDCal(pp);                //位置纠正差速量计算
  
	RMotor_Out = *current_speed - Out_temp;
	LMotor_Out = *current_speed + Out_temp;
	
  //限幅
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
	if ((IODATA.bits.SW5 == 0)&&(current_screen_id != 5))//安全触边检测
	{
    MOTOR_DISABLE
		manual_control.turn_Mode = MSTOP;
		automatic_control.control_mode = ASTOP;
		if (car_info.status.bit.safety_stop_flag == 0)		
	  {
			  SetControlCmd(1,60,DISABLE);//禁用启动
			  delay_ms(100);
			  SetTextStrings(1,85,"Alarm"); //触边传感器触发报警解除
			  delay_ms(100);
			  Can_Send_Msg(numS,8);
//        Alarm_Band_R=1;
//			  Twinkle_Status = 1;//红灯长亮
//			  Light_Band_R = 1;
//				Light_Band_B = 0;
//				Light_Band_G = 0;
        SetControlCmd(1,94,DISABLE);//禁用滚筒控件控制
        delay_ms(100);
        SetControlCmd(1,95,DISABLE);//禁用滚筒控件控制
        delay_ms(100);		    
        SetControlForeColor(1,93,WHITE);
			  delay_ms(100);
		    SetControlForeColor(1,91,WHITE);
			  delay_ms(100);     
		}
    car_info.status.bit.safety_stop_flag = 1;		
	}
  else if (IODATA.bits.K1 == 0) //急停K5对应于判断编码器U33的D4，若为0即为按下急停
	{
     MOTOR_DISABLE
		 manual_control.turn_Mode = MSTOP;
		 automatic_control.control_mode = ASTOP;
     if (car_info.status.bit.emergency_stop_flag == 0) 
		 {
			  Can_Send_Msg(numS,8);
//        Alarm_Band_R=1;
//			  Twinkle_Status = 1;//红灯长亮
//			  Light_Band_R = 1;
//				Light_Band_B = 0;
//				Light_Band_G = 0;
        SetControlCmd(1,94,DISABLE);//禁用滚筒控件控制
        delay_ms(100);
        SetControlCmd(1,95,DISABLE);//禁用滚筒控件控制
        delay_ms(100);		    
        SetControlForeColor(1,93,WHITE);
			  delay_ms(100);
		    SetControlForeColor(1,91,WHITE);
			  delay_ms(100);
		 }
     car_info.status.bit.emergency_stop_flag = 1;		
	}
	else if ((IODATA.bits.Alarm1 == 1)||(IODATA.bits.Alarm2 == 1))//检测电机驱动器是否正常
	{
		  MOTOR_DISABLE
		  manual_control.turn_Mode = MSTOP;
		  automatic_control.control_mode = ASTOP;
		  if (car_info.status.bit.motor_alarm_flag == 0)		
	    {
		    SetTextStrings(1,51,"Alarm"); //电机驱动器触发并报警
			  delay_ms(100);
//        Twinkle_Status = 1;//红灯长亮
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
		    SetTextStrings(1,51,"Normal"); //电机驱动器报警解除
			  delay_ms(100);
			  car_info.status.bit.motor_alarm_flag = 0;
				if (car_info.status.all == 0)
				{
//					Twinkle_Status = TWINKLE_FREQUENCY + 2;//开始黄灯慢闪
//					Light_Band_R = 1;
//				  Light_Band_B = 0;
//				  Light_Band_G = 1;
//					Alarm_Band_R=0;
				}
		}			
			
    if (car_info.status.bit.emergency_stop_flag == 1) 
    {
			 SetControlCmd(1,60,ENABLE);//使能启动
			 delay_ms(100);
		   car_info.status.bit.emergency_stop_flag = 0;//清空急停状态标志
       SetControlCmd(1,94,ENABLE);//使能滚筒控件控制
       delay_ms(100);
       SetControlCmd(1,95,ENABLE);//使能滚筒控件控制
       delay_ms(100);
			 if (car_info.status.all == 0)
			 {
//					Twinkle_Status = TWINKLE_FREQUENCY + 2;//开始黄灯慢闪
//					Light_Band_R = 1;
//				  Light_Band_B = 0;
//				  Light_Band_G = 1;
//					Alarm_Band_R=0;
			 }
		}
		
		if ((IODATA.bits.K3 == 0)&&(current_screen_id != 5))//停止按钮按下
		{
		    manual_control.turn_Mode = MSTOP;
		    automatic_control.control_mode = ASTOP;
			  car_info.status.bit.nav_status_with_screen_control = 0;
			  if (car_info.status.bit.safety_stop_flag == 1)		
	      {
					 SetControlCmd(1,60,ENABLE);//使能启动
					 delay_ms(100);
					 car_info.status.bit.safety_stop_flag = 0;
		       SetTextStrings(1,85,"Normal"); //触边传感器触发报警解除
			     delay_ms(100);
					 if (car_info.status.all == 0)
					 {
//             Twinkle_Status = TWINKLE_FREQUENCY + 2;//开始黄灯慢闪
//					   Light_Band_R = 1;
//				     Light_Band_B = 0;
//				     Light_Band_G = 1;
//             Alarm_Band_R=0;
					 }
				}
		}
		else if ((IODATA.bits.K4 == 0) && (automatic_control.terminal_station != 0) && (current_screen_id != 5))//启动按钮按下
		{
			
			/**              需要补充一个是否有起始站点                         ***/
//		     Twinkle_Status = 4;//绿灯长亮
//		     Light_Band_R = 0;
//		     Light_Band_B = 0;
//		     Light_Band_G = 1;				
  			 //如果目标速度档位为0，则表明车体是到了终点才停止的，
			   //此时启动是以最高速为目标速度，否则只需使用当前的目标速度档位值即可
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
		     //向上位机上报车体状况（包括位置，速度等）
		}
		
		if (automatic_control.control_mode == ASTOP)
		{
        MOTOR_DISABLE
			  Nav_Station_test();
//			  Deal_With_ICData();                 //IC卡数据处理				
//	      Get_Magneticsensor_Information();   //获得使用的磁导航信息
//	      Calculate_Error(&PIDcontrol);       //计算偏差
		}
		else if (car_control_mode == AUTOMATIC) //自动模式，也没按下停止键
		{
        MOTOR_ENABLE
        ICData_Analyze();                 //IC卡数据处理				
	      Get_Magneticsensor_Information();   //获得使用的磁导航信息
	      Calculate_Error(&PIDcontrol);       //计算偏差
				Global_Speed_Control(&(automatic_control.current_speed)); //控制速度			
        Global_PID_Control(&(automatic_control.current_speed),&PIDcontrol);	  //控制pid参数	        			
	      Car_Move_Out(&(automatic_control.current_speed),&PIDcontrol);		      //PID运算及电机控制输出
	   }
	   else if (car_control_mode == MANUAL) //串口屏模式
	   {
				Get_Magneticsensor_Information();
				if (NavAInformatiom.Sum != 0) //说明在磁条上
				{
//          //白灯慢速闪烁
//			    Twinkle_Status = TWINKLE_FREQUENCY + 3;
//					Light_Band_R = 1;
//				  Light_Band_B = 1;
//				  Light_Band_G = 1;					
				}
				else if (car_info.status.bit.nav_status_with_screen_control == 1)
				{
//          //红灯慢速闪烁
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
							SetTextStrings(1,85,"Normal"); //触边传感器触发报警解除
							delay_ms(100);
							if (car_info.status.all == 0)
							{
//								Twinkle_Status = TWINKLE_FREQUENCY + 2;//开始黄灯慢闪
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
	if (roller_direction) //为0表示不运动
	{
		if (roller_direction == 1)//表示向前运动
		{
		  if (before_status == 0)//表示前挡板到达低位，此时滚筒才可以向前运动
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
     	   roller_direction = 0;//清0，防止重复发送				
			}
		}
		else if (roller_direction == 2)//表示向后运动
    {
		  if (rear_status == 0)//表示后挡板到达低位，此时滚筒可以向前运动
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
     	  roller_direction = 0;//清0，防止重复发送				
			}
		}	
	}
}


void Nav_Station_test(void)
{
	uint8_t i,j,m,buff[30] = {0};
	
    Get_Magneticsensor_Information();
    if (NavAInformatiom.Sum != 0) //说明在磁条上
		{
      if (car_info.status.bit.nav_status_with_screen_control == 1) 
		  {
				
			 	SetTextStrings(1,50,"Normal"); //磁导航在轨
			  delay_ms(100);
				car_info.status.bit.nav_status_with_screen_control = 0;
				if (car_info.status.all == 0)
				{
//					//白灯慢速闪烁
//					Twinkle_Status = TWINKLE_FREQUENCY + 3;
//					Light_Band_R = 1;
//				  Light_Band_B = 1;
//				  Light_Band_G = 1;
//					Alarm_Band_R=0;
				}
		  }
		}
    else//否则不在磁条上
		{
      if (car_info.status.bit.nav_status_with_screen_control == 0) 
		  {
			 	SetTextStrings(1,50,"Alarm"); //磁导航不在轨
			  delay_ms(100);
				car_info.status.bit.nav_status_with_screen_control = 1;
//        //红灯慢速闪烁
//			  Twinkle_Status = TWINKLE_FREQUENCY + 1;
//			  Light_Band_R = 1;
//				Light_Band_B = 0;
//				Light_Band_G = 0;
//	      Alarm_Band_R=1;
		  }		
		}
	
	  //开始判断是否在运行中,为0表示未在运行
//	  if ((automatic_control.running_status == 0)&&(Twinkle_Status%10 == 3)&&(automatic_control.start_station == 0))//说明已停止，并重新上电,且在磁导航上 
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
//				if ((buff[0] == 0x7f) && (buff[26] != 0x00) && (buff[26] != RxBuffLast[26]))//已完整接收到数据且不重复使用（站点卡除外）
//				{		
//						for (uint8_t i = 0;i<27;i++)   //保存读卡数据，除非读卡数据有误才再使用一次RxBuff
//						{
//							 RxBuffLast[i] = buff[i];
//			//         RxBuff[i] = 0x00;				
//						}
//						LED1=!LED1;
//						//控制数据加载
//						AT24CXX_Read(MEMORY_ADRESSS15,Control_Data.all,10);
//						 //判断是否在站点上
//						if ((RxBuffLast[10] == 0x01)&&(RxBuffLast[11] == automatic_control.start_station)&&(RxBuffLast[12] == automatic_control.start_line))//和保存的起始站点相同，表明停止后未移动,只需将读出的数据显示
//						{
//						 //显示当前信息包括站点号、车头朝向、当前线路
//							SetTextValue(1, 52,automatic_control.start_station);//发送当前站点号，且此时站点为起始站点
//							delay_ms(100);
//							SetTextValue(1, 68,automatic_control.start_line);//发送当前站点号所在的线路号
//						  delay_ms(100);
//						  Twinkle_Status = TWINKLE_FREQUENCY + 2;
////						  USART5_Send_To_Computer(14,0,0,0,automatic_control.direction_mode,automatic_control.start_station,5);
//						  //当前朝向判断
//						  //先读当前线路管理信息，若当前站点不在该线路两端，则在当前站点号的EEPROM中向前、向后获取该条线路上比当前站点小、大的站点号，再根据车头朝向大还是小判断用哪个站点号
//						 
//					 }
//					 else //否则将相关数据清0
//					 {
//							memsett(Control_Data.all,0,10);
//					 }
//				 }
//		}				
}

