#ifndef MAIN_MCU_H
#define MAIN_MCU_H

/* Includes ------------------------------------------------------------------*/
#include "cmd_queue.h"
/* Private macro -------------------------------------------------------------*/
/* Private variables type ---------------------------------------------------------*/
/* Private variables -----------------------------------------------*/
extern QUEUE mainmcu_que;      //指令队列
extern CMD mainmcu_cmd;        //单条指令
extern uint8_t readey;
/* Private functions ---------------------------------------------------------*/

/*! 
*  \brief  从指令队列中取出一条完整的指令
*  \param  cmd 指令接收缓存区
*  \param  buf_len 指令接收缓存区大小
*  \return  指令长度，0表示队列中无完整指令
*/
uint16_t MainMCUQueue_Find_Cmd(QUEUE *que,CMD *cmd,uint16_t buf_len);

void MainMCUCMD_Analyze(uint8_t *cmdbuff,uint16_t length);

//wifi状态发送
void SendWifiStatusToMainMCU(uint8_t status);

#endif
