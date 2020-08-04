
/* Includes ------------------------------------------------------------------*/
#include "main_mcu.h"
#include "wifi.h"
#include "delay.h"
#include "USART_Config.h"
#include "GPIO_Config.h"
/* Private macro -------------------------------------------------------------*/
#define MCU_CMD_HEAD 0X4040             //֡ͷ
#define MCU_CMD_TAIL 0X2323             //֡β
#define CRC16_ENABLE 0                   //��ʹ��CRC16У�鹦�ܣ���0��Ϊ1����
/* Private variables ---------------------------------------------------------*/
static uint16_t cmd_state = 0;      //����֡β���״̬
static uint16_t cmd_pos = 0;        //��ǰָ��ָ��λ��
QUEUE mainmcu_que = {0,0,{0}};         //ָ�����
CMD mainmcu_cmd = {{0},0};             //����ָ��
uint8_t readey = 0;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


/*! 
*  \brief  ��ָ�������ȡ��һ��������ָ��
*  \param  cmd ָ����ջ�����
*  \param  buf_len ָ����ջ�������С
*  \return  ָ��ȣ�0��ʾ������������ָ��
*/
uint16_t MainMCUQueue_Find_Cmd(QUEUE *que,CMD *cmd,uint16_t buf_len)
{
    uint8_t _data = 0;
	
    while (queue_size(que)>0)
    {
        //ȡһ������
        queue_pop(que,&_data);

        if (cmd_pos==0&&cmd_state!=MCU_CMD_HEAD)  //ָ��ǰ2���ֽڱ�����֡ͷ����������
        {
            cmd_state = ((cmd_state<<8)|_data);
            continue;
        }
        
        if(cmd_pos<buf_len)                                           //��ֹ���������
            cmd->data[cmd_pos++] = _data;

        cmd_state = ((cmd_state<<8)|_data);                           //ƴ�����2���ֽڣ����һ��16λ����

        //���2���ֽ���֡βƥ�䣬�õ�����֡
        if (cmd_state==MCU_CMD_TAIL)
        {
					  cmd->size = cmd_pos;                                      //ָ���ֽڳ���
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



void MainMCUCMD_Analyze(uint8_t *cmdbuff,uint16_t length)
{
	if(cmdbuff[0] == 2)//ת������λ��
	{
		if (running_mode)
		{
		  TransferData(UART4,cmdbuff,length);
		}
	}
	else if(cmdbuff[0] == 5)//ת������λ��
	{
		if (running_mode)
		{
		  TransferData(UART4,cmdbuff,length);
		}
	}
	else if(cmdbuff[0] == 7)//ת������λ��
	{
		if (running_mode)
		{
		  TransferData(UART4,cmdbuff,length);
		}
	}	
	else if (cmdbuff[0] == 6) //��Ƭ����
	{
	  if (cmdbuff[2] == 29) //�����������
		{
//			if (cmdbuff[3] == 2)
//			{				
				  TransferData(USART3,cmdbuff,length); //ת��laser2 mcu (ǰ����)
//			}
//			else if (cmdbuff[3] == 1)
//			{
          TransferData(USART2,cmdbuff,length); //ת��laser1 mcu (�󼤹�)
//			}			
		}
    else if (cmdbuff[2] == 20)//����ʹ�ܿ���
		{
//			if (cmdbuff[3] == 2)
//			{				
				  TransferData(USART3,cmdbuff,length); //ת��laser2 mcu (ǰ����)
//			}
//			else if (cmdbuff[3] == 1)
//			{
          TransferData(USART2,cmdbuff,length); //ת��laser1 mcu (�󼤹�)
//			} 
		}
    else if (cmdbuff[2] == 21)//WIFIʹ�ܿ���
	  {
      running_mode = cmdbuff[3];
      if (running_mode == 0)
      {
        handshake.status = 0;
        handshake.sendtimecnt = 0;
      }        
	  }			
		else if (cmdbuff[2] == 28)//��������״̬���
		{
			if (cmdbuff[3] == 2)
			{
			    TransferData(USART3,cmdbuff,length); //ת��laser2 mcu (ǰ����)   
			}
			else if (cmdbuff[3] == 1)
			{
			    TransferData(USART2,cmdbuff,length); //ת��laser1 mcu (�󼤹�)   
			}
		}
		else if (cmdbuff[2] == 31)//������������
		{
//			if (cmdbuff[3] == 2)
//			{
			    TransferData(USART3,cmdbuff,length); //ת��laser2 mcu (ǰ����)   
//			}
//			else if (cmdbuff[3] == 1)
//			{
			    TransferData(USART2,cmdbuff,length); //ת��laser1 mcu (�󼤹�)   
//			}			
		}
		else if (cmdbuff[2] == 35) //wifiģ������ź�
		{
			  if (cmdbuff[3] == 0) //��ʾ����
			  {
					  wifi_status = 0;
           	WIFI_RESET = 0;
	          delay_ms(400);
	          WIFI_RESET = 1;					
				}
//				else if (cmdbuff[3] == 1) //��ʾ�ָ���������
//				{
//           WIFI_RELOAD = 1;
//	         delay_s(4);
//	         WIFI_RELOAD = 0;					
//				}			
		}		
		else if (cmdbuff[2] == 40)//��Ƭ����readey�ź�
		{			
       readey = 1;			 			 
		}
	}
//	else if (cmdbuff[0] == 0) //������Ϣ����ͷ���
//	{
//    if (cmdbuff[2] == 40) //ʵʱ��������
//		{
//			TransferData(UART4,cmdbuff,length); //ת��server
//		}
//    else if (cmdbuff[2] == 14) //ʵʱ���ת��
//		{
//			TransferData(UART4,cmdbuff,length); //ת��server
//		}			
//	}
}


void MidMCUSendDataToMainMCU(uint8_t *databuff,uint8_t length)
{
	uint8_t buff[50] = {0}, m = 0;
	
	//֡ͷ
	buff[m++] = 0x40;
	buff[m++] = 0x40;
	//�����־
	buff[m++] = databuff[0];
	//���ݳ���
	buff[m++] = length - 1;
	//���ͱ�ʾ��
	buff[m++] = databuff[1];
	//��������
	for (uint8_t n = 2;n < length;n++)
	{
	  buff[m++] = databuff[n];	
	}
	//CRC16У��
//	CRC16(
	
	buff[m++] = 0x00;
	buff[m++] = 0x00;
	//֡β
	buff[m++] = 0x23;
	buff[m++] = 0x23;
	
	USART_SendnData(UART5,buff,m);
}

//wifi״̬����
void SendWifiStatusToMainMCU(uint8_t status)
{
	uint8_t buff[3] = {6,19,0};
	
	buff[2] = status;
	MidMCUSendDataToMainMCU(buff,3);
}

