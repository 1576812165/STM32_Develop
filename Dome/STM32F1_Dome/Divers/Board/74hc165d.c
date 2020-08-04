
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
	unsigned int count = 24;        //��Ƭ74hc165,��Ҫ��24��
	unsigned int i;
	IODATA_Type tmp;

//���ز������ݲ�����
    SH_LD=1;
    delay_us(1);
    SH_LD=0;
    delay_us(1);
    SH_LD=1;
    delay_us(1);
    CLK_74=1;
    delay_us(1);
	
	//gpio������оƬ���ݽ�ֱ�����������Ե�һ�β���Ҫʱ�Ӿ��ܶ�ȡ����һλ���ݡ�
  //��һ��ʱ�ӽ���õ��ڶ�λ����	
    if(DATAHC==1)
       val += 1;
   for(i=0;i<count-1;i++)
		{
		  CLK_74=0;
		  delay_us(1);
			CLK_74=1;
			delay_us(1);
			val=val<<1;//����val<<=1
		if(DATAHC==1)
			val += 1;
		}
		CLK_74=1;
		SH_LD=1;
		
	//����Ӳ���������ݵ�λ��
   tmp.all = ((val & 0xff0000) >> 16) | (val & 0xff00) | ((val & 0xff) << 16);	
		
	 return tmp.all;	
}


