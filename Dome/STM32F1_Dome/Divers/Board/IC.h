#ifndef IC_H
#define IC_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_conf.h"
/* Private macro -------------------------------------------------------------*/
#define IC_BUF_SIZE   27         //DMA���ڽ������ݳ���
/* Private variables type---------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern uint8_t icbuff[IC_BUF_SIZE + 3];
/* Private functions ---------------------------------------------------------*/

void ICData_Analyze(void);

#endif
