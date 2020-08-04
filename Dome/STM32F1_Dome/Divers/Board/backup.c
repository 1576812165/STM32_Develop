
/* Includes ------------------------------------------------------------------*/
#include "backup.h"
#include "delay.h"
#include "GPIO_Config.h"
#include "USART_Config.h"
#include "stm32f10x.h"
#include "wifi.h"
/* Private macro -------------------------------------------------------------*/
#define MCU_CMD_HEAD 0X4040             //帧头
#define MCU_CMD_TAIL 0X2323             //帧尾
#define CRC16_ENABLE 0                   //需使用CRC16校验功能，将0改为1即可
/* Private variables ---------------------------------------------------------*/
static uint16_t cmd_state = 0;      //队列帧尾检测状态
static uint16_t cmd_pos = 0;        //当前指令指针位置
QUEUE backup_que = {0,0,{0}};         //指令队列
CMD backup_cmd = {{0},0};             //单条指令
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


/*! 
*  \brief  从指令队列中取出一条完整的指令
*  \param  cmd 指令接收缓存区
*  \param  buf_len 指令接收缓存区大小
*  \return  指令长度，0表示队列中无完整指令
*/
uint16_t BackupQueue_Find_Cmd(QUEUE *que,CMD *cmd,uint16_t buf_len)
{
    uint8_t _data = 0;
	
    while (queue_size(que)>0)
    {
        //取一个数据
        queue_pop(que,&_data);

        if (cmd_pos==0&&cmd_state!=MCU_CMD_HEAD)  //指令前2个字节必须是帧头，否则跳过
        {
            cmd_state = ((cmd_state<<8)|_data);
            continue;
        }
        
        if(cmd_pos<buf_len)                                           //防止缓冲区溢出
            cmd->data[cmd_pos++] = _data;

        cmd_state = ((cmd_state<<8)|_data);                           //拼接最后2个字节，组成一个16位整数

        //最后2个字节与帧尾匹配，得到完整帧
        if (cmd_state==MCU_CMD_TAIL)
        {
					  cmd->size = cmd_pos;                                      //指令字节长度
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



void BackupCMD_Analyze(uint8_t *cmdbuff,uint16_t length)
{
	if (cmdbuff[0] == 1) //下发控制命令
	{
		if (cmdbuff[2] <= 11) //转发至main mcu
		{
			TransferData(UART5,cmdbuff,length - 2);//-2是为了去除帧尾
		}
		else if (cmdbuff[2] == 35) //wifi模块控制信号
		{
			  if (cmdbuff[3] == 0) //表示重启
			  {
           	WIFI_RESET = 0;
	          delay_ms(400);
	          WIFI_RESET = 1;					
				}
				else if (cmdbuff[3] == 1) //表示恢复出厂设置
				{
           WIFI_RELOAD = 1;
	         delay_s(4);
	         WIFI_RELOAD = 0;					
				}			
		}
	}
}


void MidMCUSendDataToBackup(uint8_t *databuff,uint8_t length)
{
	uint8_t buff[50] = {0}, m = 0;
	
	//帧头
	buff[m++] = 0x40;
	buff[m++] = 0x40;
	//命令标志
	buff[m++] = databuff[0];
	//数据长度
	buff[m++] = (length - 2) + 1;
	//类型标示符
	buff[m++] = databuff[1];
	//数据内容
	for (uint8_t n = 2;n < length;n++)
	{
	  buff[m++] = databuff[n];	
	}
	//CRC16校验
//	CRC16(
	
	buff[m++] = 0x00;
	buff[m++] = 0x00;
	//帧尾
	buff[m++] = 0x23;
	buff[m++] = 0x23;
	
	
	DE_RE_485 = 1;//使能发送
	USART_SendnData(USART1,buff,m);
	delay_ms(1);
  DE_RE_485 = 0;//恢复接收	
}
