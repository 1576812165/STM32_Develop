/**
  ******************************************************************************
  * @file    User/main.c 
  * @author  XX
  * @version V1.0
  * @date    2020-3-2
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */  

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "Clock_Config.h"
#include "GPIO_Config.h"
#include "USART_Config.h"
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint8_t ALL_Init_Finish = 0;
/* Private function prototypes -----------------------------------------------*/
uint8_t ALL_Init(void);
/* Private functions ---------------------------------------------------------*/
/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{ 
  ALL_Init();				
  while (1)
  {
    
  }
}




uint8_t ALL_Init(void)
{
	//设置中断分组为2，表示高2位抢占优先级、2位子优先级
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  delay_init();	
  GPIO_AllInit();
	USART_AllInit(9600,57600,57600,57600,57600);
  return 0;
}



/***********************END OF FILE****/
