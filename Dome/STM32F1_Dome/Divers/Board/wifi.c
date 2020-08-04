
/* Includes ------------------------------------------------------------------*/
#include "wifi.h"
#include "delay.h"
#include "GPIO_Config.h"
#include "USART_Config.h"
#include "main_mcu.h"

/* Private function prototypes -----------------------------------------------*/
void SendHeartbeatbagDataToServer(void);

/* Private macro -------------------------------------------------------------*/
#define WIFI_CMD_HEAD 0X4040             //帧头
#define WIFI_CMD_TAIL 0X2323             //帧尾
#define CRC16_ENABLE 0                   //需使用CRC16校验功能，将0改为1即可
/* Private variables ---------------------------------------------------------*/
static uint16_t cmd_state = 0;      //队列帧尾检测状态
static uint16_t cmd_pos = 0;        //当前指令指针位置
QUEUE wifi_que = {0,0,{0}};         //指令队列
CMD wifi_cmd = {{0},0};             //单条指令
uint8_t wifi_status = 0;
uint8_t running_mode = 0;
handshake_t handshake = {0,0,SendHeartbeatbagDataToServer};       //
/* Private functions ---------------------------------------------------------*/


/*! 
*  \brief  从指令队列中取出一条完整的指令
*  \param  cmd 指令接收缓存区
*  \param  buf_len 指令接收缓存区大小
*  \return  指令长度，0表示队列中无完整指令
*/
uint16_t WifiQueue_Find_Cmd(QUEUE *que,CMD *cmd,uint16_t buf_len)
{
    uint8_t _data = 0, uchCRCHi = 0, uchCRCLo = 0;
	  uint16_t CRC16value = 0;
	
    while (queue_size(que)>0)
    {
        //取一个数据
        queue_pop(que,&_data);

        if (cmd_pos==0&&cmd_state!=WIFI_CMD_HEAD)  //指令前2个字节必须是帧头，否则跳过
        {
            cmd_state = ((cmd_state<<8)|_data);
            continue;
        }
        
        if(cmd_pos<buf_len)                                           //防止缓冲区溢出
            cmd->data[cmd_pos++] = _data;

        cmd_state = ((cmd_state<<8)|_data);                           //拼接最后2个字节，组成一个16位整数

        //最后2个字节与帧尾匹配，得到完整帧
        if (cmd_state==WIFI_CMD_TAIL)
        {
					  cmd->size = cmd_pos;                                      //指令字节长度
            cmd_state = 0;                                            //重新检测帧尾巴
            cmd_pos = 0;
					
#if (CRC16_ENABLE)
									
            if (cmd->data[0] == 8)//校验来自上位机的心跳数据
						{
							 //去掉指令校验和尾，校验和尾0X2323共计4个字节
							 CRC16value = CRC16(cmd->data,cmd->size-4);
							 uchCRCHi = (CRC16value >> 8)&0xFF;
							 uchCRCLo = CRC16value&0xFF;	
             
							 if ((uchCRCLo != cmd->data[cmd->size-4])||(uchCRCHi != cmd->data[cmd->size-3]))//CRC校验不通过则进入
							 {
								 return 0;
							 }				
					  }					
#endif						
            return (cmd->size - 4);    //去掉CRC16（2字节）和尾（2字节）;
        }
    }
    return 0;                                                         //没有形成完整的一帧
}

void SendDataToServer(uint8_t *databuff,uint8_t length)
{
	uint8_t buff[50] = {0}, m = 0;
	uint16_t CRC16value = 0;
	//帧头
	buff[m++] = 0x40;
	buff[m++] = 0x40;
	//命令标志
	buff[m++] = databuff[0];
	//数据长度
	buff[m++] = length - 1;
	//类型标示符
	buff[m++] = databuff[1];
	//数据内容
	for (uint8_t n = 2;n < length;n++)
	{
	  buff[m++] = databuff[n];	
	}
#if (CRC16_ENABLE)
	
  //去掉指令头，头0x4040共计2个字节
  CRC16value = CRC16(buff+2,m-2);                      //CRC校验
  buff[m++] = CRC16value&0xFF;
	buff[m++] = (CRC16value >> 8)&0xFF;	

#else
	
  buff[m++] = 0;
	buff[m++] = 0;
	
#endif
	//帧尾
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
	
	length -= 2;//-2是为了去除帧尾
	//帧头
	buff[m++] = 0x40;
	buff[m++] = 0x40;
	//命令标志
	buff[m++] = databuff[0];
	//数据长度
	buff[m++] = databuff[1];
	//类型标示符
	buff[m++] = databuff[2];
	//数据内容
	for (uint8_t n = 3;n < length;n++)
	{
	  buff[m++] = databuff[n];	
	}
	//帧尾
	buff[m++] = 0x23;
	buff[m++] = 0x23;
	
	if ((pUSARTx != UART4)||(running_mode != 0))
	{
		if (pUSARTx == USART1)
		{
			DE_RE_485 = 1;//使能发送
		  USART_SendnData(pUSARTx,buff,m);
			delay_ms(1);
      DE_RE_485 = 0;//恢复接收			
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
	if (cmdbuff[0] == 1) //下发控制命令
	{    
		TransferData(UART5,cmdbuff,length);
    if (cmdbuff[2] == 1) handshake.status = 1;
	}
	else if (cmdbuff[0] == 3)//下发查询命令
	{
		TransferData(UART5,cmdbuff,length);
	}
	else if (cmdbuff[0] == 8) //心跳包
	{   
		delay_ms(100);	
    handshake.SendHeartbeatbagDataToServer();		
	} 
}

//		else if (cmdbuff[2] == 35) //wifi模块控制信号
//		{
//			  if (cmdbuff[3] == 0) //表示重启
//			  {
//           	WIFI_RESET = 0;
//	          delay_ms(400);
//	          WIFI_RESET = 1;					
//				}
//				else if (cmdbuff[3] == 1) //表示恢复出厂设置
//				{
//           WIFI_RELOAD = 1;
//	         delay_s(4);
//	         WIFI_RELOAD = 0;					
//				}			
//		}

