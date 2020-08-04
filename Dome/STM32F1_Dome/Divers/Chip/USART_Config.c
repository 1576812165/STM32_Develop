
/* Includes ------------------------------------------------------------------*/
#include "USART_Config.h"
#include <stdio.h>
/* Private macro -------------------------------------------------------------*/
#define DEBUG_USARTx USART1
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

static void USART1_NVICInit(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
  //USART1 
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		//子优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器

  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启串口接受中断		
}

static void USART2_NVICInit(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
  //USART2 
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		//子优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器

  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启串口接受中断		
}

static void USART3_NVICInit(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
  //USART3 
  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		//子优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器

  USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//开启串口接受中断		
}

#ifdef STM32F10X_HD

static void UART4_NVICInit(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
  //UART4 
  NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		//子优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器

  USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);//开启串口接受中断		
}

static void UART5_NVICInit(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
  //UART5 
  NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		//子优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器

  USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);//开启串口接受中断		
}

#endif /* STM32F10X_HD */

void USART_AllInit(uint32_t baud1,uint32_t baud2,uint32_t baud3,uint32_t baud4,uint32_t baud5)
{
	USART_InitTypeDef USART_InitStructure;
	
  //使能USART时钟	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2|RCC_APB1Periph_USART3|RCC_APB1Periph_UART4|RCC_APB1Periph_UART5, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);	

  //USART1 
	USART_InitStructure.USART_BaudRate = baud1;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

  USART_Init(USART1, &USART_InitStructure); //初始化串口2
  USART_Cmd(USART1, ENABLE);                    //使能串口2 
  USART1_NVICInit();	

  //USART2 
	USART_InitStructure.USART_BaudRate = baud2;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

  USART_Init(USART2, &USART_InitStructure); //初始化串口2
  USART_Cmd(USART2, ENABLE);                    //使能串口2 
  USART2_NVICInit();
	
  //USART3 
	USART_InitStructure.USART_BaudRate = baud3;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

  USART_Init(USART3, &USART_InitStructure);      //初始化串口1
  USART_Cmd(USART3, ENABLE);                     //使能串口 
  USART3_NVICInit();

#ifdef STM32F10X_HD

  //UART4 
	USART_InitStructure.USART_BaudRate = baud4;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

  USART_Init(UART4, &USART_InitStructure); //初始化串口
  USART_Cmd(UART4, ENABLE);                    //使能串口
  UART4_NVICInit();


  //UART5 
	USART_InitStructure.USART_BaudRate = baud5;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

  USART_Init(UART5, &USART_InitStructure); //初始化串口
  USART_Cmd(UART5, ENABLE);                    //使能串口
  UART5_NVICInit();

#endif /* STM32F10X_HD */
}

//加入以下代码,支持printf函数,而不需要选择use MicroLIB	  
//#if 1
#ifdef DEBUG_USARTx
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
_sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{      
	while((DEBUG_USARTx->SR&0X40)==0);//循环发送,直到发送完毕   
    USART1->DR = (u8) ch;      
	return ch;
}
#endif 

/*使用microLib的方法*/
 /* 
int fputc(int ch, FILE *f)
{
	USART_SendData(USART1, (uint8_t) ch);

	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET) {}	
   
    return ch;
}
int GetKey (void)  { 

    while (!(USART1->SR & USART_FLAG_RXNE));

    return ((int)(USART1->DR & 0x1FF));
}
*/


void USART_SendChar(USART_TypeDef *pUSARTx,uint8_t c)
{
	/* 先读一次,防止首字符丢失 */
  USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE);
  /* 发送一个字节数据到USART */
  USART_SendData(pUSARTx,c);
  /* 等待发送数据寄存器为空 */
  while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}

void USART_SendString(USART_TypeDef *pUSARTx,uint8_t *s)
{
	/* 先读一次,防止首字符丢失 */
  USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE);	
	while (*s)
	{
		/* 发送一个字节数据到USART */
    USART_SendData(pUSARTx,*s);
		s++;
    /* 等待发送数据寄存器为空 */
    while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
	}		
}

void USART_SendnData(USART_TypeDef *pUSARTx,uint8_t *data,uint8_t length)
{
	/* 先读一次,防止首字符丢失 */
  USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE);
	while (length--)
	{
		/* 发送一个字节数据到USART */
    USART_SendData(pUSARTx,*data);
    /* 等待发送数据寄存器为空 */
    while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
		data++;

	}	
}

///**
//  * @brief  Retargets the C library printf function to the USART.
//  * @param  None
//  * @retval None
//  */
//PUTCHAR_PROTOTYPE
//{
//  /* Place your implementation of fputc here */
//  /* e.g. write a character to the USART */
//  USART_SendData(EVAL_COM1, (uint8_t) ch);

//  /* Loop until the end of transmission */
//  while (USART_GetFlagStatus(EVAL_COM1, USART_FLAG_TC) == RESET)
//  {}

//  return ch;
//}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif




