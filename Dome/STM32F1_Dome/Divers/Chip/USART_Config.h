#ifndef USART_CONFIG_H
#define USART_CONFIG_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
/* Private macro -------------------------------------------------------------*/
//#define USATR1
#define USATR1baud 9600
//#define USATR2
#define USATR2baud 9600
//#define USATR3
#define USATR3baud 9600
//#define USATR1
#define UATR4baud 9600
//#define UATR5
#define UATR5baud 9600

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
#ifdef __GNUC__
/* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
   set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

/* Private functions ---------------------------------------------------------*/
void USART_AllInit(uint32_t baud1,uint32_t baud2,uint32_t baud3,uint32_t baud4,uint32_t baud5);
void USART_SendChar(USART_TypeDef *pUSARTx,uint8_t c);
void USART_SendString(USART_TypeDef *pUSARTx,uint8_t *s);
void USART_SendnData(USART_TypeDef *pUSARTx,uint8_t *data,uint8_t length);

#endif
