
#include "PID.h"

#define PID_Mode_Select 1  //为0时为增量式，为1时为位置式

#define FILTER_VALUE 0.0625           //0.03125    0.015625


//PID变量初始化函数，这个函数的功能是初始化PID变量中各个变量的值。
//设定值、比例常数、积分常数、微分常数应该在这个函数中进行修改设定
void PIDInit(PID *p,float4Byte *P,float4Byte *PP)
{
	p->Proportion = P[0].f + PP[0].f;     //给定KP
	p->Integral   = P[1].f + PP[1].f;     //给定KI
	p->Derivative = P[2].f + PP[2].f;     //给定KD	
}

//PID 计算函数，它有两个形式参数，PID 指针pp 和当前误差ThisError（当前值与设定值的差）。
//这个PID 计算函数的功能主要有两个：
//1、根据理论公式，计算得出控制修正量作为函数返回值
//2、更新总误差、上一次偏差量和上上次偏差量。
float PIDCal(PID *pp)
{
  float pError,dError,iError;
  float templ;

#if (PID_Mode_Select == 0)
	
  pError = pp->Error[0] - pp->Error[1];
  iError = pp->Error[0];
  dError = pp->Error[0] - 2*(pp->Error[1]) + pp->Error[2];
	
  // 增量计算
  templ = pp->Proportion * pError + pp->Integral * iError 
	        + pp->Derivative * dError; //增量
  
	// 存储误差用于下次运算
  pp->Error[2] = pp->Error[1];
  pp->Error[1] = pp->Error[0];
	
#else
	
//	if((pp->Error[0] - pp->Error[1]) > FILTER_VALUE)			    pp->Error[0] = pp->Error[1] + FILTER_VALUE;
//	else if((pp->Error[0] - pp->Error[1]) < -FILTER_VALUE)		pp->Error[0] = pp->Error[1] - FILTER_VALUE;
  	
  pError = pp->Error[0];
  iError = pp->Error[0] + pp->Error[1] + pp->Error[2] + pp->Error[3] + pp->Error[4];
  dError = pp->Error[0] - pp->Error[1];
	
  // 位置上输出计算
  templ = pp->Proportion * pError + pp->Integral * iError 
	        + pp->Derivative * dError; 
  
	// 存储误差用于下次运算	
  pp->Error[4] = pp->Error[3];
  pp->Error[3] = pp->Error[2];	
  pp->Error[2] = pp->Error[1];
  pp->Error[1] = pp->Error[0];
	
#endif
	
 return templ;
}

