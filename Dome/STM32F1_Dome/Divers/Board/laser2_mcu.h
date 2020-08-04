#ifndef LASER2_MCU_H
#define LASER2_MCU_H

/* Includes ------------------------------------------------------------------*/
#include "cmd_queue.h"
/* Private macro -------------------------------------------------------------*/
/* Private variables type ---------------------------------------------------------*/
/* Private variables -----------------------------------------------*/
extern QUEUE laser2mcu_que;      //ָ�����
extern CMD laser2mcu_cmd;        //����ָ��  
/* Private functions ---------------------------------------------------------*/

/*! 
*  \brief  ��ָ�������ȡ��һ��������ָ��
*  \param  cmd ָ����ջ�����
*  \param  buf_len ָ����ջ�������С
*  \return  ָ��ȣ�0��ʾ������������ָ��
*/
uint16_t Laser2MCUQueue_Find_Cmd(QUEUE *que,CMD *cmd,uint16_t buf_len);

void Laser2MCUCMD_Analyze(uint8_t *cmdbuff,uint16_t length);

#endif
