
/* Includes ------------------------------------------------------------------*/
#include "Clock_Config.h"
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
volatile uint32_t sysTickDowncnt = 0;
volatile uint32_t powerdisplaycnt = 0;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*******************************************************
*�δ�ʱ������
*��Ҫ����ϵͳ����ʱ�Լ�ʱ��
******************************************************/
void SysTick_Init(void)
{
	//�δ��ʱ��ʱ��Դ����
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);
	
  /* HCLK = SYSCLK = SystemCoreClock
	 * SystemFrequency / (1000) 1ms �ж�һ��
   * SystemFrequency / (100000) 10us �ж�һ��
   * SystemFrequency / (1000000) 1us �ж�һ��
   */
  if (SysTick_Config(SystemCoreClock / (1000)))
	{
      /* Capture error */
      while (1);
  }
  
  //�����趨�δ�ʱ���ж����ȼ�Ϊ���
  NVIC_SetPriority (SysTick_IRQn, 0);  /* set Priority for Cortex-M0 System Interrupts */
}


/**********************************************
*�������ƣ�us����ʱ����
*�������ܣ�����us����ʱ�ȴ�
***********************************************/
void delay_us(uint32_t us)  
{
    register uint32_t ticks;
    register uint32_t told;
    register uint32_t tnow;
    register uint32_t tcnt = 0;

    ticks = us * (SystemCoreClock / 1000000);	 /* ��Ҫ�Ľ����� */

    tcnt = 0;
    told = SysTick->VAL;             /* �ս���ʱ�ļ�����ֵ */

    while (1)
    {
        tnow = SysTick->VAL;
        if (tnow != told)
        {
            /* SYSTICK��һ���ݼ��ļ����� */
            if (tnow < told)
            {
                tcnt += told - tnow;
            }
            /* ����װ�صݼ� */
            else
            {
                tcnt += SysTick->LOAD - tnow + told;
            }
            told = tnow;

            /* ʱ�䳬��/����Ҫ�ӳٵ�ʱ��,���˳� */
            if (tcnt >= ticks)
            {
            	break;
            }
        }
    }
}

/**********************************************
*�������ƣ�ms����ʱ����
*�������ܣ�����ms����ʱ�ȴ�
***********************************************/
void delay_ms(uint32_t ms) 
{
	sysTickDowncnt = ms;	
  while (sysTickDowncnt);
}

/**********************************************
*�������ƣ�s����ʱ����
*�������ܣ�����s����ʱ�ȴ�
***********************************************/
void delay_s(uint32_t s) 
{
  while (s--)
  {
		delay_ms(1000);
  }
}
