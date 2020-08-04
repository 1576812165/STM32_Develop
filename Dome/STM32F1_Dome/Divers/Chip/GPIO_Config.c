
/* Includes ------------------------------------------------------------------*/
#include "GPIO_Config.h"
#include "stm32f10x.h"
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


void GPIO_AllInit(void)
{ 
  GPIO_InitTypeDef  GPIO_InitStructure;
 	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC
	                       |RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOE|RCC_APB2Periph_AFIO, 
	                       ENABLE);	 //使能端口时钟	

	
	/*  LED - PE1 
   */	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;	    		 //
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;   //IO口速度为50MHz
  GPIO_Init(GPIOE, &GPIO_InitStructure);	  				 
  GPIO_ResetBits(GPIOE,GPIO_Pin_1); 						 //输出高 

 	/*  wifi
	 *  PB3-nReady 模块起动完毕后，输出“0”(或心跳信号)，否则输出“1”
   *  PB4-nLink	WIFI 有连接时，输出“0”，否则输出“1” 
	 *  PD7-RESET 低电平复位，复位时间>300ms    
	 *  PD6-nReload 输入低电平“0”大于3秒后拉高,模块恢复出厂设置后重起
	 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4;	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 //上拉输入
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //复用推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;   //IO口速度为50MHz
  GPIO_Init(GPIOD, &GPIO_InitStructure);
  GPIO_SetBits(GPIOD,GPIO_Pin_7); 						   //输出高	
	GPIO_ResetBits(GPIOD,GPIO_Pin_6); 						 //输出低,由于加了三极管驱动，逻辑相反
	
	
	 /*  485_DE/RE -- PE11
	  */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;        //
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	 //复用推挽输出
  GPIO_Init(GPIOE, &GPIO_InitStructure);           //初始化
  GPIO_ResetBits(GPIOE,GPIO_Pin_11); 						 //输出低,默认初始化接收	

  /*  USART1  -- 备份485接口
	 */
	GPIO_PinRemapConfig(GPIO_Remap_USART1 ,ENABLE );    //串口1管脚重映射
	//USART1_TX   
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;        //
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	 //复用推挽输出
  GPIO_Init(GPIOB, &GPIO_InitStructure);           //初始化
   
  //USART1_RX	  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;       //
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;   //上拉输入
  GPIO_Init(GPIOB, &GPIO_InitStructure);          //初始化   


  /*  USART2 -- laser1_mcu 
	 */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 		 //复用推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;   //IO口速度为50MHz
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 //上拉输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);


  /*  USART3 -- laser2_mcu
	 */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 		 //复用推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;   //IO口速度为50MHz
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 //上拉输入
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	/*  UART4 --  wifi
	 */	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 		 //复用推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;   //IO口速度为50MHz
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 //上拉输入
  GPIO_Init(GPIOC, &GPIO_InitStructure);	
	
	
  /*  UART5 --  main_mcu
	 */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 		 //复用推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;   //IO口速度为50MHz
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 //上拉输入
  GPIO_Init(GPIOD, &GPIO_InitStructure);	
} 



