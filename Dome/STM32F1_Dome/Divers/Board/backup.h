#ifndef BACKUP_H
#define BACKUP_H

/* Includes ------------------------------------------------------------------*/
#include "cmd_queue.h"
/* Private macro -------------------------------------------------------------*/
/* Private variables type ---------------------------------------------------------*/
/* Private variables -----------------------------------------------*/
extern QUEUE backup_que;      //指令队列
extern CMD backup_cmd;        //单条指令  
/* Private functions ---------------------------------------------------------*/

/*! 
*  \brief  从指令队列中取出一条完整的指令
*  \param  cmd 指令接收缓存区
*  \param  buf_len 指令接收缓存区大小
*  \return  指令长度，0表示队列中无完整指令
*/
uint16_t BackupQueue_Find_Cmd(QUEUE *que,CMD *cmd,uint16_t buf_len);

void BackupCMD_Analyze(uint8_t *cmdbuff,uint16_t length);

#endif
