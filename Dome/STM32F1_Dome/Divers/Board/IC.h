#ifndef IC_H
#define IC_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_conf.h"
/* Private macro -------------------------------------------------------------*/
#define IC_BUF_SIZE   27         //DMA串口接收数据长度
/* Private variables type---------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern uint8_t icbuff[IC_BUF_SIZE + 3];
/* Private functions ---------------------------------------------------------*/

void ICData_Analyze(void);

#endif
