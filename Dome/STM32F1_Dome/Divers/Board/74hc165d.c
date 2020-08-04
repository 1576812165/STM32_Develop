
/* Includes ------------------------------------------------------------------*/
#include "74hc165d.h"
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

IODATA_Type	IODATA = {0};
IODATA_Type laterRead = {0};

uint32_t read_74165(void)
{
	unsigned int val = 0;
	unsigned int count = 24;        //三片74hc165,需要读24次
	unsigned int i;
	IODATA_Type tmp;

//加载并行数据并锁存
    SH_LD=1;
    delay_us(1);
    SH_LD=0;
    delay_us(1);
    SH_LD=1;
    delay_us(1);
    CLK_74=1;
    delay_us(1);
	
	//gpio引脚与芯片数据脚直接相连，所以第一次不需要时钟就能读取到第一位数据。
  //下一个时钟将会得到第二位数据	
    if(DATAHC==1)
       val += 1;
   for(i=0;i<count-1;i++)
		{
		  CLK_74=0;
		  delay_us(1);
			CLK_74=1;
			delay_us(1);
			val=val<<1;//等于val<<=1
		if(DATAHC==1)
			val += 1;
		}
		CLK_74=1;
		SH_LD=1;
		
	//根据硬件调整数据的位置
   tmp.all = ((val & 0xff0000) >> 16) | (val & 0xff00) | ((val & 0xff) << 16);	
		
	 return tmp.all;	
}


