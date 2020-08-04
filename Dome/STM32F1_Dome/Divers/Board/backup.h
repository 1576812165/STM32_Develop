#ifndef BACKUP_H
#define BACKUP_H

/* Includes ------------------------------------------------------------------*/
#include "cmd_queue.h"
/* Private macro -------------------------------------------------------------*/
/* Private variables type ---------------------------------------------------------*/
/* Private variables -----------------------------------------------*/
extern QUEUE backup_que;      //ָ�����
extern CMD backup_cmd;        //����ָ��  
/* Private functions ---------------------------------------------------------*/

/*! 
*  \brief  ��ָ�������ȡ��һ��������ָ��
*  \param  cmd ָ����ջ�����
*  \param  buf_len ָ����ջ�������С
*  \return  ָ��ȣ�0��ʾ������������ָ��
*/
uint16_t BackupQueue_Find_Cmd(QUEUE *que,CMD *cmd,uint16_t buf_len);

void BackupCMD_Analyze(uint8_t *cmdbuff,uint16_t length);

#endif
