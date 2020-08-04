
/* Includes ------------------------------------------------------------------*/
#include "wifi.h"
#include "delay.h"
#include "GPIO_Config.h"
#include "USART_Config.h"
#include "main_mcu.h"

/* Private function prototypes -----------------------------------------------*/
void SendHeartbeatbagDataToServer(void);

/* Private macro -------------------------------------------------------------*/
#define WIFI_CMD_HEAD 0X4040             //֡ͷ
#define WIFI_CMD_TAIL 0X2323             //֡β
#define CRC16_ENABLE 0                   //��ʹ��CRC16У�鹦�ܣ���0��Ϊ1����
/* Private variables ---------------------------------------------------------*/
static uint16_t cmd_state = 0;      //����֡β���״̬
static uint16_t cmd_pos = 0;        //��ǰָ��ָ��λ��
QUEUE wifi_que = {0,0,{0}};         //ָ�����
CMD wifi_cmd = {{0},0};             //����ָ��
uint8_t wifi_status = 0;
uint8_t running_mode = 0;
handshake_t handshake = {0,0,SendHeartbeatbagDataToServer};       //
/* Private functions ---------------------------------------------------------*/


/*! 
*  \brief  ��ָ�������ȡ��һ��������ָ��
*  \param  cmd ָ����ջ�����
*  \param  buf_len ָ����ջ�������С
*  \return  ָ��ȣ�0��ʾ������������ָ��
*/
uint16_t WifiQueue_Find_Cmd(QUEUE *que,CMD *cmd,uint16_t buf_len)
{
    uint8_t _data = 0, uchCRCHi = 0, uchCRCLo = 0;
	  uint16_t CRC16value = 0;
	
    while (queue_size(que)>0)
    {
        //ȡһ������
        queue_pop(que,&_data);

        if (cmd_pos==0&&cmd_state!=WIFI_CMD_HEAD)  //ָ��ǰ2���ֽڱ�����֡ͷ����������
        {
            cmd_state = ((cmd_state<<8)|_data);
            continue;
        }
        
        if(cmd_pos<buf_len)                                           //��ֹ���������
            cmd->data[cmd_pos++] = _data;

        cmd_state = ((cmd_state<<8)|_data);                           //ƴ�����2���ֽڣ����һ��16λ����

        //���2���ֽ���֡βƥ�䣬�õ�����֡
        if (cmd_state==WIFI_CMD_TAIL)
        {
					  cmd->size = cmd_pos;                                      //ָ���ֽڳ���
            cmd_state = 0;                                            //���¼��֡β��
            cmd_pos = 0;
					
#if (CRC16_ENABLE)
									
            if (cmd->data[0] == 8)//У��������λ������������
						{
							 //ȥ��ָ��У���β��У���β0X2323����4���ֽ�
							 CRC16value = CRC16(cmd->data,cmd->size-4);
							 uchCRCHi = (CRC16value >> 8)&0xFF;
							 uchCRCLo = CRC16value&0xFF;	
             
							 if ((uchCRCLo != cmd->data[cmd->size-4])||(uchCRCHi != cmd->data[cmd->size-3]))//CRCУ�鲻ͨ�������
							 {
								 return 0;
							 }				
					  }					
#endif						
            return (cmd->size - 4);    //ȥ��CRC16��2�ֽڣ���β��2�ֽڣ�;
        }
    }
    return 0;                                                         //û���γ�������һ֡
}

void SendDataToServer(uint8_t *databuff,uint8_t length)
{
	uint8_t buff[50] = {0}, m = 0;
	uint16_t CRC16value = 0;
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
#if (CRC16_ENABLE)
	
  //ȥ��ָ��ͷ��ͷ0x4040����2���ֽ�
  CRC16value = CRC16(buff+2,m-2);                      //CRCУ��
  buff[m++] = CRC16value&0xFF;
	buff[m++] = (CRC16value >> 8)&0xFF;	

#else
	
  buff[m++] = 0;
	buff[m++] = 0;
	
#endif
	//֡β
	buff[m++] = 0x23;
	buff[m++] = 0x23;
	
	if (running_mode != 0)
	{	
	  USART_SendnData(UART4,buff,m);		
	}
}

void TransferData(USART_TypeDef *pUSARTx,uint8_t *databuff,uint8_t length)
{
	uint8_t buff[64] = {0}, m = 0;
	
	length -= 2;//-2��Ϊ��ȥ��֡β
	//֡ͷ
	buff[m++] = 0x40;
	buff[m++] = 0x40;
	//�����־
	buff[m++] = databuff[0];
	//���ݳ���
	buff[m++] = databuff[1];
	//���ͱ�ʾ��
	buff[m++] = databuff[2];
	//��������
	for (uint8_t n = 3;n < length;n++)
	{
	  buff[m++] = databuff[n];	
	}
	//֡β
	buff[m++] = 0x23;
	buff[m++] = 0x23;
	
	if ((pUSARTx != UART4)||(running_mode != 0))
	{
		if (pUSARTx == USART1)
		{
			DE_RE_485 = 1;//ʹ�ܷ���
		  USART_SendnData(pUSARTx,buff,m);
			delay_ms(1);
      DE_RE_485 = 0;//�ָ�����			
		}
		else
		{
   		USART_SendnData(pUSARTx,buff,m);		
		}
	}
}

void SendHeartbeatbagDataToServer(void)
{
	uint8_t buff[2] = {8,41};
	
	SendDataToServer(buff,2);
}

void WifiCMD_Analyze(uint8_t *cmdbuff,uint16_t length)
{
	if (cmdbuff[0] == 1) //�·���������
	{    
		TransferData(UART5,cmdbuff,length);
    if (cmdbuff[2] == 1) handshake.status = 1;
	}
	else if (cmdbuff[0] == 3)//�·���ѯ����
	{
		TransferData(UART5,cmdbuff,length);
	}
	else if (cmdbuff[0] == 8) //������
	{   
		delay_ms(100);	
    handshake.SendHeartbeatbagDataToServer();		
	} 
}

//		else if (cmdbuff[2] == 35) //wifiģ������ź�
//		{
//			  if (cmdbuff[3] == 0) //��ʾ����
//			  {
//           	WIFI_RESET = 0;
//	          delay_ms(400);
//	          WIFI_RESET = 1;					
//				}
//				else if (cmdbuff[3] == 1) //��ʾ�ָ���������
//				{
//           WIFI_RELOAD = 1;
//	         delay_s(4);
//	         WIFI_RELOAD = 0;					
//				}			
//		}

