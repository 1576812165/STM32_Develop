
/* Includes ------------------------------------------------------------------*/
#include "screen.h"
/* Private macro -------------------------------------------------------------*/
#define SCREEN_CMD_HEAD 0XEE               //帧头
#define SCREEN_CMD_TAIL 0XFFFCFFFF         //帧尾
#define CRC16_ENABLE 0                     //需使用CRC16校验功能，将0改为1即可

#define PTR2U16(PTR) ((((uint8_t *)(PTR))[0]<<8)|((uint8_t *)(PTR))[1])  //从缓冲区取16位数据
#define PTR2U32(PTR) ((((uint8_t *)(PTR))[0]<<24)|(((uint8_t *)(PTR))[1]<<16)|(((uint8_t *)(PTR))[2]<<8)|((uint8_t *)(PTR))[3])  //从缓冲区取32位数据
//向串口屏发数据
#define TX_8(P1) SEND_DATA((P1)&0xFF)  //发送单个字节
#define TX_8N(P,N) SendNU8((uint8_t *)P,N)  //发送N个字节
#define TX_16(P1) TX_8((P1)>>8);TX_8(P1)  //发送16位整数
#define TX_16N(P,N) SendNU16((uint16_t *)P,N)  //发送N个16位整数
#define TX_32(P1) TX_16((P1)>>16);TX_16((P1)&0xFFFF)  //发送32位整数
#define SEND_DATA(P) USART_SendChar(USART1,P)
#define BEGIN_CMD() TX_8(0XEE)
#define END_CMD() TX_32(0XFFFCFFFF)
/* Private variables ---------------------------------------------------------*/
static uint32_t cmd_state = 0;      //队列帧尾检测状态
static uint16_t cmd_pos = 0;        //当前指令指针位置
QUEUE screen_que = {0,0,{0}};       //指令队列
CMD screen_cmd = {{0},0};           //单条指令
uint8_t station_order[22] = {0};
uint16_t current_screen_id = 0;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*! 
*  \brief  从指令队列中取出一条完整的指令
*  \param  cmd 指令接收缓存区
*  \param  buf_len 指令接收缓存区大小
*  \return  指令长度，0表示队列中无完整指令
*/
uint16_t ScreenQueue_Find_Cmd(QUEUE *que,CMD *cmd,uint16_t buf_len)
{
    uint8_t _data = 0;
	
    while (queue_size(que)>0)
    {
        //取一个数据
        queue_pop(que,&_data);

        if(cmd_pos==0&&_data!=SCREEN_CMD_HEAD)                        //指令第一个字节必须是帧头，否则跳过
        {
            continue;
        }
        
        if(cmd_pos<buf_len)                                           //防止缓冲区溢出
            cmd->data[cmd_pos++] = _data;

        cmd_state = ((cmd_state<<8)|_data);                           //拼接最后2个字节，组成一个16位整数

        //最后4个字节与帧尾匹配，得到完整帧
        if (cmd_state==SCREEN_CMD_TAIL)
        {
					  cmd->size = cmd_pos;                                       //指令字节长度
            cmd_state = 0;                                            //重新检测帧尾巴
            cmd_pos = 0;
					
#if (CRC16_ENABLE)
            //去掉指令头尾EE，尾FFFCFFFF共计5个字节，只计算数据部分CRC
            if (!CRC16(buffer+1,cmd_pos-5))                      //CRC校验
                return 0;

            cmd_size -= 2;                                            //去掉CRC16（2字节）
#endif
						
            return cmd->size;
        }
    }
    return 0;                                                         //没有形成完整的一帧
}

//可用来清空字符数组
void memsett(void* s, uint8_t c, uint8_t n)
{
    uint8_t *p = (uint8_t*) s;

    while (n > 0) {
		*p++ = c;
		--n;
    }
}

//返回0x55,表示状态正常
void USARTScreenCheck(void)
{
	BEGIN_CMD();
	TX_8(0x04);
	END_CMD();
}


void GetNowScreen_id(void)
{
	BEGIN_CMD();
	TX_8(0xB1);
	TX_8(0x01);
	END_CMD();
}

//切换画面
void ChangePage(uint16_t screen_id)
{
   BEGIN_CMD();
   TX_8(0xB1);	
   TX_8(0x00);	
   TX_16(screen_id);	
   END_CMD();
}


//禁止/使能控件
void SetControlCmd(uint16_t screen_id,uint16_t control_id,FunctionalState NewState)
{
		BEGIN_CMD();
		TX_8(0xB1);
	  TX_8(0x04);
	  TX_16(screen_id);
		TX_16(control_id);
		TX_8(NewState);//禁止信号
		END_CMD();
}


//用于设置显示或者隐藏文本，1为显示0为隐藏
void SetTextDisplayCmd(uint16_t screen_id,uint16_t control_id,FunctionalState NewState)
{
	BEGIN_CMD();
	TX_8(0xB1);
	TX_8(0x03);
	TX_16(screen_id);
	TX_16(control_id);
	TX_8(NewState);//
	END_CMD();	
}


//用于设置是否更新文本显示，1为使能0为禁止
void TextUpdataEnable(FunctionalState NewState)
{
	BEGIN_CMD();
	TX_8(0xB3);
	TX_8(NewState);
	END_CMD();	
}


//设置文本控件值
void SetTextValue(uint16_t screen_id,uint16_t control_id,int32_t number)
{
	uint8_t buffer[10] = {0};
	
	BEGIN_CMD();
	TX_8(0xB1);
	TX_8(0x10);
	TX_16(screen_id);
	TX_16(control_id);
	if (number < 0)  
	{
    buffer[0] = 0x2d;  
		sprintf(buffer+1,"%d",-number);			
	}
	else
	{
		sprintf(buffer,"%d",number);							
	}
	USART_SendString(USART1,buffer);
	END_CMD();
}


//设置文本控件显示字符串
void SetTextStrings(uint16_t screen_id,uint16_t control_id,uint8_t *str)
{
	BEGIN_CMD();
	TX_8(0xB1);
	TX_8(0x10);
	TX_16(screen_id);
	TX_16(control_id);
  while(*str)
	{
		TX_8(*str);
		str++;
	}
	END_CMD();
}


/*! 
*  \brief     设置控件前景色
* \details  支持控件：进度条
*  \param  screen_id 画面ID
*  \param  control_id 控件ID
*  \param  color 前景色
*/
void SetControlForeColor(uint16_t screen_id,uint16_t control_id,uint16_t color)
{
    BEGIN_CMD();
    TX_8(0xB1);
    TX_8(0x19);
    TX_16(screen_id);
    TX_16(control_id);
    TX_16(color);
    END_CMD();
}

/*! 
*  \brief   设置进度值
*  \param  screen_id 画面ID
*  \param  control_id 控件ID
*  \param  value 数值
*/
void SetProgressValue(uint16_t screen_id,uint16_t control_id,uint32_t value)
{
    BEGIN_CMD();
    TX_8(0xB1);
    TX_8(0x10);
    TX_16(screen_id);
    TX_16(control_id);
    TX_32(value);
    END_CMD();
}


/*! 
*  \brief     设置按钮状态
*  \param  screen_id 画面ID
*  \param  control_id 控件ID
*  \param  value 按钮状态
*/
void SetButtonValue(uint16_t screen_id,uint16_t control_id,uint8_t state)
{
    BEGIN_CMD();
    TX_8(0xB1);
    TX_8(0x10);
    TX_16(screen_id);
    TX_16(control_id);
	  if (state == 0)
		{
      TX_8(state);
		}
		else
		{
			TX_8(1);
		}
    END_CMD();
}


void ScreenInitDisplay(void)
{
	
//	//根据设置，相应显示和设置按钮状态
//	SetButtonValue(1,78,system_set_data.bit.running_mode);
//	delay_ms(100);
//	SetButtonValue(3,41,system_set_data.bit.laser_status);
//	delay_ms(100);
//	
//	//相应显示滚筒选择
//	if (system_set_data.bit.roller_speed_mode == low)
//	{
//	  SetControlForeColor(3,61,RED);
//	}
//  else if (system_set_data.bit.roller_speed_mode == medium)
//	{
//	  SetControlForeColor(3,64,RED);
//	}
//  else if (system_set_data.bit.roller_speed_mode == high)
//	{
//	  SetControlForeColor(3,67,RED);
//	}
////	Roller_Data.speed = system_set_data.bit.roller_speed_mode + 1;
//	delay_ms(100);	


//	//显示修正参数速度档位对应的速度值
//	SetTextValue(7,3,Speed_Data[Control_Data.bit.speed_correction_gear].bit.speed_value);
//  delay_ms(100);
//	//修正参数显示缓存添加
//	//显示变速改变量修正参数(采用大批量更新)	
//	/***画面7批量更新指令开始******/
//  BEGIN_CMD();
//	TX_8(0xB1);
//	TX_8(0x12);
//	TX_16(7);  //发送画面号
//	//显示减速改变量修正参数(采用大批量更新)
//	for (i = 0;i < 4;i++)
//	{
//		TX_16(8+i);  //发送控件号
//		temp = Speed_Correction_Data[Control_Data.bit.speed_correction_gear].bit.speed_change_value[i];
//		if (temp < 0)
//		{
//			buff[0] = 0x2d;
//		  sprintf(buff+1,"%d",-temp);
//		}
//		else
//		{
//		  sprintf(buff,"%d",temp);			
//		}
//		TX_16(strlen(buff));//发送当前文本控件显示的字符长度
//		SendStrings(buff);     		
//	}
//	//显示相应速度档位下各PID参数修正值
//	for (i = 0;i < 5;i++) 
//	{
//		for (j = 0;j < 3;j++)
//    {		
//			TX_16(14+i*3+j);  //发送控件号
//			temp = Speed_Correction_Data[Control_Data.bit.speed_correction_gear].bit.PID[i][j].f * 10;
//			if (temp < 0)
//			{
//				buff[0] = 0x2d;
//				sprintf(buff+1,"%d",-temp);
//			}
//			else
//			{
//				sprintf(buff,"%d",temp);			
//			}
//			TX_16(strlen(buff));//发送当前文本控件显示的字符长度
//			SendStrings(buff);  	
//		}			
//	}
//	END_CMD();
//	delay_ms(100);



//	//批量显示
//	/***画面1批量更新指令开始******/
//  BEGIN_CMD();
//	TX_8(0xB1);
//	TX_8(0x12);
//	TX_16(1);  //发送画面号
//	for (i = 0;i < 16;i++)
//	{
//		TX_16(1+i);  //发送控件号
//		sprintf(buff,"%d",Control_Data.bit.station_order[i]);
//		TX_16(strlen(buff));//发送当前文本控件显示的字符长度
//		SendStrings(buff);     		
//	}
//  END_CMD();
//  delay_ms(100);	
//	/***画面1批量更新指令结束******/
//	
//	/***画面3批量更新指令开始******/
//  BEGIN_CMD();
//	TX_8(0xB1);
//	TX_8(0x12);
//	TX_16(3);  //发送画面号
//	for (i = 0;i < 16;i++)
//	{
//		TX_16(1+i);  //发送控件号
//		sprintf(buff,"%d",Control_Data.bit.station_order[i]);
//		TX_16(strlen(buff));//发送当前文本控件显示的字符长度
//		SendStrings(buff);     		
//	}
//  END_CMD();
//  delay_ms(100);	
//	/***画面3批量更新指令结束******/		
//	temp = ((temp|system_set_data.bit.laser_distance[0])<<8) + system_set_data.bit.laser_distance[1];
//  SetTextValue(3,38,temp);
//  delay_ms(100);





//	//加载编号、服务器IP、端口号、本地IP
//	AT24CXX_Read(MEMORY_DISPLAYMSGADDR,buff,13);	
//	
//	//显示编号、服务器IP、端口号、本地IP
//	SetTextValue(1,53,buff[0]);
//  delay_ms(100);
//	/***画面3批量更新指令开始******/
//  BEGIN_CMD();
//	TX_8(0xB1);
//	TX_8(0x12);
//	TX_16(3);  //发送画面号
//	for (i = 1;i < 13;i++)
//	{
//		TX_16(22+i);  //发送控件号
//		sprintf(buffer,"%d",buff[i]);
//		TX_16(strlen(buffer));//发送当前文本控件显示的字符长度
//		SendStrings(buffer);     		
//	}
//  END_CMD();
//  delay_ms(100);	
//	/***画面3批量更新指令结束******/
	
	//读一次编码器值用于相关状态检测
	IODATA.all = read_74165();//读取编码器的值
	laterRead.all=IODATA.all;
	if ((IODATA.bits.Light_SW5 == 0)||(IODATA.bits.Light_SW4 == 0)||(IODATA.bits.Light_SW3 == 0))
	{	
		SetTextStrings(1,49,"ON");
		delay_ms(100);
	}
	
  //先禁用运行模式的选择，只维持在单机模式且wifi状态显示OFF，当wifi连接上后才能使能
	//然后切换到主界面（即画面1）
  SetControlCmd(1,78,DISABLE);//禁用运行模式控件选择
  delay_ms(100);
	
	ChangePage(1);//切换到主界面
	delay_ms(100);
}


void PowerAndIoSensorDataDisplay(void)
{
	
	
	
	
}



void Screen1_Handle(uint16_t control_id,uint8_t state)
{	

}





/*! 
*  \brief  按钮控件通知
*  \details  当按钮状态改变(或调用GetControlValue)时，执行此函数
*  \param screen_id 画面ID
*  \param control_id 控件ID
*  \param state 按钮状态：0弹起，1按下
*/
void NotifyButton(uint16_t screen_id, uint16_t control_id, uint8_t state)
{	
	switch(screen_id)
	{
    case 0x0001:Screen1_Handle(control_id,state);break; //主界面
//    case 0x0003:Screen3_Handle(control_id,state);break; //基础设置界面
//    case 0x0004:Screen4_Handle(control_id,state);break; //手动控制界面
//    case 0x0005:Screen5_Handle(control_id,state);break; //硬件检测界面
//    case 0x0006:Screen6_Handle(control_id);break; //修正参数设置界面
		default:break;
	}
}

void NotifyText(uint16_t screen_id, uint16_t control_id, uint8_t *str)
{	
	uint8_t size = 0,i = 0,buff[10] = {0};
	uint32_t temp = 0;
	if (screen_id == 0x0001)
	{
		
		
	}
  else if (screen_id == 0x0002)	
  {
			if (str[0]==0x38&&str[1]==0x38&&str[2]==0x38&&str[3]==0x38
				  &&str[4]==0x38&&str[5]==0x38&&str[6]==0x38&&str[7]==0x38)//密码界面，密码88888888
			{   
				ChangePage(3);//切换到基础设置界面
				delay_ms(100);
			}
	}
}	



void ScreenCMD_Analyze(PCTRL_MSG cmdbuff,uint16_t length)
{
    uint8_t cmd_type = cmdbuff->cmd_type;                                                  //指令类型
    uint8_t ctrl_msg = cmdbuff->ctrl_msg;                                                  //消息的类型
    uint16_t screen_id = PTR2U16(&cmdbuff->screen_id);                                     //画面ID
    uint16_t control_id = PTR2U16(&cmdbuff->control_id);                                   //控件ID
	  uint8_t control_type = cmdbuff->control_type;                                          //控件类型
    uint32_t value = PTR2U32(cmdbuff->param);                                              //数值

	 switch(cmd_type)  //0XB1
   { 
	   case NOTIFY_CONTROL://串口屏第二个数据为B1表示控件更新通知
		 {
			 if (ctrl_msg==MSG_GET_CURRENT_SCREEN)
			 {
//			   NotifyScreen(screen_id);//每次向串口屏发数据  先获取串口屏当前画面
			 }
		   else
			 {	
   				switch(control_type)//控件类型
					{
						 case kCtrlButton://按钮控件0x10
						  NotifyButton(screen_id,control_id,cmdbuff->param[1]);
						 break;
						 case kCtrlText://文本控件0x11
						  NotifyText(screen_id,control_id,cmdbuff->param);                       
						 break;						 
						 default:
						 break;						 
					}
			 }
			 break; 
		 }
	   case NOTIFY_HandShake:                                                          //握手通知                                                     
//	      NOTIFYHandShake();
	      break;
	   default:
        break;
	 }
}
