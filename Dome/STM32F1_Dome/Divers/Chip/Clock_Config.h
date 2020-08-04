#ifndef CLOCK_CONFIG_H
#define CLOCK_CONFIG_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_conf.h"
/* Private macro -------------------------------------------------------------*/
#define delay_init SysTick_Init
/* Private variables ---------------------------------------------------------*/
extern volatile uint32_t sysTickDowncnt;
extern volatile uint32_t powerdisplaycnt;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
void SysTick_Init(void);
void delay_s(uint32_t s);
void delay_ms(uint32_t ms);
void delay_us(uint32_t us);



#endif
