#ifndef LASER1_MCU_H
#define LASER1_MCU_H

/* Includes ------------------------------------------------------------------*/
#include "cmd_queue.h"
/* Private macro -------------------------------------------------------------*/
/* Private variables type ---------------------------------------------------------*/
/* Private variables -----------------------------------------------*/
extern QUEUE laser1mcu_que;      //ָ�����
extern CMD laser1mcu_cmd;        //����ָ��  
/* Private functions ---------------------------------------------------------*/

/*! 
*  \brief  ��ָ�������ȡ��һ��������ָ��
*  \param  cmd ָ����ջ�����
*  \param  buf_len ָ����ջ�������С
*  \return  ָ��ȣ�0��ʾ������������ָ��
*/
uint16_t Laser1MCUQueue_Find_Cmd(QUEUE *que,CMD *cmd,uint16_t buf_len);

void Laser1MCUCMD_Analyze(uint8_t *cmdbuff,uint16_t length);

void MidMCUSendDataToLaser1MCU(uint8_t *databuff,uint8_t length);
#endif
