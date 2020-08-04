
/* Includes ------------------------------------------------------------------*/
#include "screen.h"
/* Private macro -------------------------------------------------------------*/
#define SCREEN_CMD_HEAD 0XEE               //֡ͷ
#define SCREEN_CMD_TAIL 0XFFFCFFFF         //֡β
#define CRC16_ENABLE 0                     //��ʹ��CRC16У�鹦�ܣ���0��Ϊ1����

#define PTR2U16(PTR) ((((uint8_t *)(PTR))[0]<<8)|((uint8_t *)(PTR))[1])  //�ӻ�����ȡ16λ����
#define PTR2U32(PTR) ((((uint8_t *)(PTR))[0]<<24)|(((uint8_t *)(PTR))[1]<<16)|(((uint8_t *)(PTR))[2]<<8)|((uint8_t *)(PTR))[3])  //�ӻ�����ȡ32λ����
//�򴮿���������
#define TX_8(P1) SEND_DATA((P1)&0xFF)  //���͵����ֽ�
#define TX_8N(P,N) SendNU8((uint8_t *)P,N)  //����N���ֽ�
#define TX_16(P1) TX_8((P1)>>8);TX_8(P1)  //����16λ����
#define TX_16N(P,N) SendNU16((uint16_t *)P,N)  //����N��16λ����
#define TX_32(P1) TX_16((P1)>>16);TX_16((P1)&0xFFFF)  //����32λ����
#define SEND_DATA(P) USART_SendChar(USART1,P)
#define BEGIN_CMD() TX_8(0XEE)
#define END_CMD() TX_32(0XFFFCFFFF)
/* Private variables ---------------------------------------------------------*/
static uint32_t cmd_state = 0;      //����֡β���״̬
static uint16_t cmd_pos = 0;        //��ǰָ��ָ��λ��
QUEUE screen_que = {0,0,{0}};       //ָ�����
CMD screen_cmd = {{0},0};           //����ָ��
uint8_t station_order[22] = {0};
uint16_t current_screen_id = 0;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*! 
*  \brief  ��ָ�������ȡ��һ��������ָ��
*  \param  cmd ָ����ջ�����
*  \param  buf_len ָ����ջ�������С
*  \return  ָ��ȣ�0��ʾ������������ָ��
*/
uint16_t ScreenQueue_Find_Cmd(QUEUE *que,CMD *cmd,uint16_t buf_len)
{
    uint8_t _data = 0;
	
    while (queue_size(que)>0)
    {
        //ȡһ������
        queue_pop(que,&_data);

        if(cmd_pos==0&&_data!=SCREEN_CMD_HEAD)                        //ָ���һ���ֽڱ�����֡ͷ����������
        {
            continue;
        }
        
        if(cmd_pos<buf_len)                                           //��ֹ���������
            cmd->data[cmd_pos++] = _data;

        cmd_state = ((cmd_state<<8)|_data);                           //ƴ�����2���ֽڣ����һ��16λ����

        //���4���ֽ���֡βƥ�䣬�õ�����֡
        if (cmd_state==SCREEN_CMD_TAIL)
        {
					  cmd->size = cmd_pos;                                       //ָ���ֽڳ���
            cmd_state = 0;                                            //���¼��֡β��
            cmd_pos = 0;
					
#if (CRC16_ENABLE)
            //ȥ��ָ��ͷβEE��βFFFCFFFF����5���ֽڣ�ֻ�������ݲ���CRC
            if (!CRC16(buffer+1,cmd_pos-5))                      //CRCУ��
                return 0;

            cmd_size -= 2;                                            //ȥ��CRC16��2�ֽڣ�
#endif
						
            return cmd->size;
        }
    }
    return 0;                                                         //û���γ�������һ֡
}

//����������ַ�����
void memsett(void* s, uint8_t c, uint8_t n)
{
    uint8_t *p = (uint8_t*) s;

    while (n > 0) {
		*p++ = c;
		--n;
    }
}

//����0x55,��ʾ״̬����
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

//�л�����
void ChangePage(uint16_t screen_id)
{
   BEGIN_CMD();
   TX_8(0xB1);	
   TX_8(0x00);	
   TX_16(screen_id);	
   END_CMD();
}


//��ֹ/ʹ�ܿؼ�
void SetControlCmd(uint16_t screen_id,uint16_t control_id,FunctionalState NewState)
{
		BEGIN_CMD();
		TX_8(0xB1);
	  TX_8(0x04);
	  TX_16(screen_id);
		TX_16(control_id);
		TX_8(NewState);//��ֹ�ź�
		END_CMD();
}


//����������ʾ���������ı���1Ϊ��ʾ0Ϊ����
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


//���������Ƿ�����ı���ʾ��1Ϊʹ��0Ϊ��ֹ
void TextUpdataEnable(FunctionalState NewState)
{
	BEGIN_CMD();
	TX_8(0xB3);
	TX_8(NewState);
	END_CMD();	
}


//�����ı��ؼ�ֵ
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


//�����ı��ؼ���ʾ�ַ���
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
*  \brief     ���ÿؼ�ǰ��ɫ
* \details  ֧�ֿؼ���������
*  \param  screen_id ����ID
*  \param  control_id �ؼ�ID
*  \param  color ǰ��ɫ
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
*  \brief   ���ý���ֵ
*  \param  screen_id ����ID
*  \param  control_id �ؼ�ID
*  \param  value ��ֵ
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
*  \brief     ���ð�ť״̬
*  \param  screen_id ����ID
*  \param  control_id �ؼ�ID
*  \param  value ��ť״̬
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
	
//	//�������ã���Ӧ��ʾ�����ð�ť״̬
//	SetButtonValue(1,78,system_set_data.bit.running_mode);
//	delay_ms(100);
//	SetButtonValue(3,41,system_set_data.bit.laser_status);
//	delay_ms(100);
//	
//	//��Ӧ��ʾ��Ͳѡ��
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


//	//��ʾ���������ٶȵ�λ��Ӧ���ٶ�ֵ
//	SetTextValue(7,3,Speed_Data[Control_Data.bit.speed_correction_gear].bit.speed_value);
//  delay_ms(100);
//	//����������ʾ�������
//	//��ʾ���ٸı�����������(���ô���������)	
//	/***����7��������ָ�ʼ******/
//  BEGIN_CMD();
//	TX_8(0xB1);
//	TX_8(0x12);
//	TX_16(7);  //���ͻ����
//	//��ʾ���ٸı�����������(���ô���������)
//	for (i = 0;i < 4;i++)
//	{
//		TX_16(8+i);  //���Ϳؼ���
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
//		TX_16(strlen(buff));//���͵�ǰ�ı��ؼ���ʾ���ַ�����
//		SendStrings(buff);     		
//	}
//	//��ʾ��Ӧ�ٶȵ�λ�¸�PID��������ֵ
//	for (i = 0;i < 5;i++) 
//	{
//		for (j = 0;j < 3;j++)
//    {		
//			TX_16(14+i*3+j);  //���Ϳؼ���
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
//			TX_16(strlen(buff));//���͵�ǰ�ı��ؼ���ʾ���ַ�����
//			SendStrings(buff);  	
//		}			
//	}
//	END_CMD();
//	delay_ms(100);



//	//������ʾ
//	/***����1��������ָ�ʼ******/
//  BEGIN_CMD();
//	TX_8(0xB1);
//	TX_8(0x12);
//	TX_16(1);  //���ͻ����
//	for (i = 0;i < 16;i++)
//	{
//		TX_16(1+i);  //���Ϳؼ���
//		sprintf(buff,"%d",Control_Data.bit.station_order[i]);
//		TX_16(strlen(buff));//���͵�ǰ�ı��ؼ���ʾ���ַ�����
//		SendStrings(buff);     		
//	}
//  END_CMD();
//  delay_ms(100);	
//	/***����1��������ָ�����******/
//	
//	/***����3��������ָ�ʼ******/
//  BEGIN_CMD();
//	TX_8(0xB1);
//	TX_8(0x12);
//	TX_16(3);  //���ͻ����
//	for (i = 0;i < 16;i++)
//	{
//		TX_16(1+i);  //���Ϳؼ���
//		sprintf(buff,"%d",Control_Data.bit.station_order[i]);
//		TX_16(strlen(buff));//���͵�ǰ�ı��ؼ���ʾ���ַ�����
//		SendStrings(buff);     		
//	}
//  END_CMD();
//  delay_ms(100);	
//	/***����3��������ָ�����******/		
//	temp = ((temp|system_set_data.bit.laser_distance[0])<<8) + system_set_data.bit.laser_distance[1];
//  SetTextValue(3,38,temp);
//  delay_ms(100);





//	//���ر�š�������IP���˿ںš�����IP
//	AT24CXX_Read(MEMORY_DISPLAYMSGADDR,buff,13);	
//	
//	//��ʾ��š�������IP���˿ںš�����IP
//	SetTextValue(1,53,buff[0]);
//  delay_ms(100);
//	/***����3��������ָ�ʼ******/
//  BEGIN_CMD();
//	TX_8(0xB1);
//	TX_8(0x12);
//	TX_16(3);  //���ͻ����
//	for (i = 1;i < 13;i++)
//	{
//		TX_16(22+i);  //���Ϳؼ���
//		sprintf(buffer,"%d",buff[i]);
//		TX_16(strlen(buffer));//���͵�ǰ�ı��ؼ���ʾ���ַ�����
//		SendStrings(buffer);     		
//	}
//  END_CMD();
//  delay_ms(100);	
//	/***����3��������ָ�����******/
	
	//��һ�α�����ֵ�������״̬���
	IODATA.all = read_74165();//��ȡ��������ֵ
	laterRead.all=IODATA.all;
	if ((IODATA.bits.Light_SW5 == 0)||(IODATA.bits.Light_SW4 == 0)||(IODATA.bits.Light_SW3 == 0))
	{	
		SetTextStrings(1,49,"ON");
		delay_ms(100);
	}
	
  //�Ƚ�������ģʽ��ѡ��ֻά���ڵ���ģʽ��wifi״̬��ʾOFF����wifi�����Ϻ����ʹ��
	//Ȼ���л��������棨������1��
  SetControlCmd(1,78,DISABLE);//��������ģʽ�ؼ�ѡ��
  delay_ms(100);
	
	ChangePage(1);//�л���������
	delay_ms(100);
}


void PowerAndIoSensorDataDisplay(void)
{
	
	
	
	
}



void Screen1_Handle(uint16_t control_id,uint8_t state)
{	

}





/*! 
*  \brief  ��ť�ؼ�֪ͨ
*  \details  ����ť״̬�ı�(�����GetControlValue)ʱ��ִ�д˺���
*  \param screen_id ����ID
*  \param control_id �ؼ�ID
*  \param state ��ť״̬��0����1����
*/
void NotifyButton(uint16_t screen_id, uint16_t control_id, uint8_t state)
{	
	switch(screen_id)
	{
    case 0x0001:Screen1_Handle(control_id,state);break; //������
//    case 0x0003:Screen3_Handle(control_id,state);break; //�������ý���
//    case 0x0004:Screen4_Handle(control_id,state);break; //�ֶ����ƽ���
//    case 0x0005:Screen5_Handle(control_id,state);break; //Ӳ��������
//    case 0x0006:Screen6_Handle(control_id);break; //�����������ý���
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
				  &&str[4]==0x38&&str[5]==0x38&&str[6]==0x38&&str[7]==0x38)//������棬����88888888
			{   
				ChangePage(3);//�л����������ý���
				delay_ms(100);
			}
	}
}	



void ScreenCMD_Analyze(PCTRL_MSG cmdbuff,uint16_t length)
{
    uint8_t cmd_type = cmdbuff->cmd_type;                                                  //ָ������
    uint8_t ctrl_msg = cmdbuff->ctrl_msg;                                                  //��Ϣ������
    uint16_t screen_id = PTR2U16(&cmdbuff->screen_id);                                     //����ID
    uint16_t control_id = PTR2U16(&cmdbuff->control_id);                                   //�ؼ�ID
	  uint8_t control_type = cmdbuff->control_type;                                          //�ؼ�����
    uint32_t value = PTR2U32(cmdbuff->param);                                              //��ֵ

	 switch(cmd_type)  //0XB1
   { 
	   case NOTIFY_CONTROL://�������ڶ�������ΪB1��ʾ�ؼ�����֪ͨ
		 {
			 if (ctrl_msg==MSG_GET_CURRENT_SCREEN)
			 {
//			   NotifyScreen(screen_id);//ÿ���򴮿���������  �Ȼ�ȡ��������ǰ����
			 }
		   else
			 {	
   				switch(control_type)//�ؼ�����
					{
						 case kCtrlButton://��ť�ؼ�0x10
						  NotifyButton(screen_id,control_id,cmdbuff->param[1]);
						 break;
						 case kCtrlText://�ı��ؼ�0x11
						  NotifyText(screen_id,control_id,cmdbuff->param);                       
						 break;						 
						 default:
						 break;						 
					}
			 }
			 break; 
		 }
	   case NOTIFY_HandShake:                                                          //����֪ͨ                                                     
//	      NOTIFYHandShake();
	      break;
	   default:
        break;
	 }
}
