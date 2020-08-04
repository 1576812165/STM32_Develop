#ifndef MAIN_MCU_H
#define MAIN_MCU_H

/* Includes ------------------------------------------------------------------*/
#include "cmd_queue.h"
/* Private macro -------------------------------------------------------------*/
/* Private variables type ---------------------------------------------------------*/
/* Private variables -----------------------------------------------*/
extern QUEUE mainmcu_que;      //ָ�����
extern CMD mainmcu_cmd;        //����ָ��
extern uint8_t readey;
/* Private functions ---------------------------------------------------------*/

/*! 
*  \brief  ��ָ�������ȡ��һ��������ָ��
*  \param  cmd ָ����ջ�����
*  \param  buf_len ָ����ջ�������С
*  \return  ָ��ȣ�0��ʾ������������ָ��
*/
uint16_t MainMCUQueue_Find_Cmd(QUEUE *que,CMD *cmd,uint16_t buf_len);

void MainMCUCMD_Analyze(uint8_t *cmdbuff,uint16_t length);

//wifi״̬����
void SendWifiStatusToMainMCU(uint8_t status);

#endif
