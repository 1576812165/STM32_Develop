#ifndef WIFI_H
#define WIFI_H

/* Includes ------------------------------------------------------------------*/
#include "cmd_queue.h"
#include "stm32f10x.h"
/* Private macro -------------------------------------------------------------*/
/* Private variables type ---------------------------------------------------------*/
typedef struct handshake_t
{
	uint8_t status;
	uint32_t sendtimecnt;
	void (*SendHeartbeatbagDataToServer)(void);
}handshake_t;
/* Private variables -----------------------------------------------*/
extern QUEUE wifi_que;      //指令队列
extern CMD wifi_cmd;        //单条指令
extern uint8_t wifi_status;
extern uint8_t running_mode;
extern handshake_t handshake;
/* Private functions ---------------------------------------------------------*/

/*! 
*  \brief  从指令队列中取出一条完整的指令
*  \param  cmd 指令接收缓存区
*  \param  buf_len 指令接收缓存区大小
*  \return  指令长度，0表示队列中无完整指令
*/
uint16_t WifiQueue_Find_Cmd(QUEUE *que,CMD *cmd,uint16_t buf_len);

void WifiCMD_Analyze(uint8_t *cmdbuff,uint16_t length);

void TransferData(USART_TypeDef *pUSARTx,uint8_t *databuff,uint8_t length);

#endif
