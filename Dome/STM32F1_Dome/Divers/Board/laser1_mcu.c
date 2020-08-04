
/* Includes ------------------------------------------------------------------*/
#include "laser1_mcu.h"
#include "wifi.h"
#include "USART_Config.h"
/* Private macro -------------------------------------------------------------*/
#define MCU_CMD_HEAD 0X4040             //֡ͷ
#define MCU_CMD_TAIL 0X2323             //֡β
#define CRC16_ENABLE 0                   //��ʹ��CRC16У�鹦�ܣ���0��Ϊ1����
/* Private variables ---------------------------------------------------------*/
static uint16_t cmd_state = 0;      //����֡β���״̬
static uint16_t cmd_pos = 0;        //��ǰָ��ָ��λ��
QUEUE laser1mcu_que = {0,0,{0}};         //ָ�����
CMD laser1mcu_cmd = {{0},0};             //����ָ��
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


/*! 
*  \brief  ��ָ�������ȡ��һ��������ָ��
*  \param  cmd ָ����ջ�����
*  \param  buf_len ָ����ջ�������С
*  \return  ָ��ȣ�0��ʾ������������ָ��
*/
uint16_t Laser1MCUQueue_Find_Cmd(QUEUE *que,CMD *cmd,uint16_t buf_len)
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



void Laser1MCUCMD_Analyze(uint8_t *cmdbuff,uint16_t length)
{
	if (cmdbuff[0] == 6) //��Ƭ����
	{
		if (cmdbuff[2] == 18) //�����ײ״̬
		{
			cmdbuff[3] = 1;//����ģ����
      TransferData(UART5,cmdbuff,length); //ת��main mcu
		}
		else if (cmdbuff[2] == 28) //Ӳ�����
		{
			cmdbuff[3] = 1;//����ģ����
			TransferData(UART5,cmdbuff,length); //ת��main mcu
		}
	}
}


void MidMCUSendDataToLaser1MCU(uint8_t *databuff,uint8_t length)
{
	uint8_t buff[50] = {0}, m = 0;
	
	//֡ͷ
	buff[m++] = 0x40;
	buff[m++] = 0x40;
	//�����־
	buff[m++] = databuff[0];
	//���ݳ���
	buff[m++] = (length - 2) + 1;
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
	
	USART_SendnData(USART2,buff,m);
}
