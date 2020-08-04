
/* Includes ------------------------------------------------------------------*/
#include "Clock_Config.h"
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
volatile uint32_t sysTickDowncnt = 0;
volatile uint32_t powerdisplaycnt = 0;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*******************************************************
*滴答时钟配置
*主要用于系统的延时以及时基
******************************************************/
void SysTick_Init(void)
{
	//滴答计时器时钟源配置
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);
	
  /* HCLK = SYSCLK = SystemCoreClock
	 * SystemFrequency / (1000) 1ms 中断一次
   * SystemFrequency / (100000) 10us 中断一次
   * SystemFrequency / (1000000) 1us 中断一次
   */
  if (SysTick_Config(SystemCoreClock / (1000)))
	{
      /* Capture error */
      while (1);
  }
  
  //重新设定滴答定时器中断优先级为最高
  NVIC_SetPriority (SysTick_IRQn, 0);  /* set Priority for Cortex-M0 System Interrupts */
}


/**********************************************
*函数名称：us级延时函数
*函数功能：用作us级延时等待
***********************************************/
void delay_us(uint32_t us)  
{
    register uint32_t ticks;
    register uint32_t told;
    register uint32_t tnow;
    register uint32_t tcnt = 0;

    ticks = us * (SystemCoreClock / 1000000);	 /* 需要的节拍数 */

    tcnt = 0;
    told = SysTick->VAL;             /* 刚进入时的计数器值 */

    while (1)
    {
        tnow = SysTick->VAL;
        if (tnow != told)
        {
            /* SYSTICK是一个递减的计数器 */
            if (tnow < told)
            {
                tcnt += told - tnow;
            }
            /* 重新装载递减 */
            else
            {
                tcnt += SysTick->LOAD - tnow + told;
            }
            told = tnow;

            /* 时间超过/等于要延迟的时间,则退出 */
            if (tcnt >= ticks)
            {
            	break;
            }
        }
    }
}

/**********************************************
*函数名称：ms级延时函数
*函数功能：用作ms级延时等待
***********************************************/
void delay_ms(uint32_t ms) 
{
	sysTickDowncnt = ms;	
  while (sysTickDowncnt);
}

/**********************************************
*函数名称：s级延时函数
*函数功能：用作s级延时等待
***********************************************/
void delay_s(uint32_t s) 
{
  while (s--)
  {
		delay_ms(1000);
  }
}
