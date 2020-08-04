#ifndef __74HC165D_H
#define __74HC165D_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_conf.h"
/* Private macro -------------------------------------------------------------*/
/* Private variables type---------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern IODATA_Type	IODATA;
extern IODATA_Type laterRead;
/* Private functions ---------------------------------------------------------*/
uint32_t read_74165(void);

#endif

