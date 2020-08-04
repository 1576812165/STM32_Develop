
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
	                       ENABLE);	 //ʹ�ܶ˿�ʱ��	

	
	/*  LED - PE1 
   */	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;	    		 //
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;   //IO���ٶ�Ϊ50MHz
  GPIO_Init(GPIOE, &GPIO_InitStructure);	  				 
  GPIO_ResetBits(GPIOE,GPIO_Pin_1); 						 //����� 

 	/*  wifi
	 *  PB3-nReady ģ������Ϻ������0��(�������ź�)�����������1��
   *  PB4-nLink	WIFI ������ʱ�������0�������������1�� 
	 *  PD7-RESET �͵�ƽ��λ����λʱ��>300ms    
	 *  PD6-nReload ����͵�ƽ��0������3�������,ģ��ָ��������ú�����
	 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4;	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 //��������
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�����������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;   //IO���ٶ�Ϊ50MHz
  GPIO_Init(GPIOD, &GPIO_InitStructure);
  GPIO_SetBits(GPIOD,GPIO_Pin_7); 						   //�����	
	GPIO_ResetBits(GPIOD,GPIO_Pin_6); 						 //�����,���ڼ����������������߼��෴
	
	
	 /*  485_DE/RE -- PE11
	  */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;        //
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	 //�����������
  GPIO_Init(GPIOE, &GPIO_InitStructure);           //��ʼ��
  GPIO_ResetBits(GPIOE,GPIO_Pin_11); 						 //�����,Ĭ�ϳ�ʼ������	

  /*  USART1  -- ����485�ӿ�
	 */
	GPIO_PinRemapConfig(GPIO_Remap_USART1 ,ENABLE );    //����1�ܽ���ӳ��
	//USART1_TX   
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;        //
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	 //�����������
  GPIO_Init(GPIOB, &GPIO_InitStructure);           //��ʼ��
   
  //USART1_RX	  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;       //
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;   //��������
  GPIO_Init(GPIOB, &GPIO_InitStructure);          //��ʼ��   


  /*  USART2 -- laser1_mcu 
	 */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 		 //�����������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;   //IO���ٶ�Ϊ50MHz
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 //��������
  GPIO_Init(GPIOA, &GPIO_InitStructure);


  /*  USART3 -- laser2_mcu
	 */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 		 //�����������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;   //IO���ٶ�Ϊ50MHz
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 //��������
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	/*  UART4 --  wifi
	 */	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 		 //�����������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;   //IO���ٶ�Ϊ50MHz
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 //��������
  GPIO_Init(GPIOC, &GPIO_InitStructure);	
	
	
  /*  UART5 --  main_mcu
	 */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 		 //�����������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;   //IO���ٶ�Ϊ50MHz
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 //��������
  GPIO_Init(GPIOD, &GPIO_InitStructure);	
} 



