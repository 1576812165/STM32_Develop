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
extern QUEUE wifi_que;      //ָ�����
extern CMD wifi_cmd;        //����ָ��
extern uint8_t wifi_status;
extern uint8_t running_mode;
extern handshake_t handshake;
/* Private functions ---------------------------------------------------------*/

/*! 
*  \brief  ��ָ�������ȡ��һ��������ָ��
*  \param  cmd ָ����ջ�����
*  \param  buf_len ָ����ջ�������С
*  \return  ָ��ȣ�0��ʾ������������ָ��
*/
uint16_t WifiQueue_Find_Cmd(QUEUE *que,CMD *cmd,uint16_t buf_len);

void WifiCMD_Analyze(uint8_t *cmdbuff,uint16_t length);

void TransferData(USART_TypeDef *pUSARTx,uint8_t *databuff,uint8_t length);

#endif
