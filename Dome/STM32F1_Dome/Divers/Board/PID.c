
#include "PID.h"

#define PID_Mode_Select 1  //Ϊ0ʱΪ����ʽ��Ϊ1ʱΪλ��ʽ

#define FILTER_VALUE 0.0625           //0.03125    0.015625


//PID������ʼ����������������Ĺ����ǳ�ʼ��PID�����и���������ֵ��
//�趨ֵ���������������ֳ�����΢�ֳ���Ӧ������������н����޸��趨
void PIDInit(PID *p,float4Byte *P,float4Byte *PP)
{
	p->Proportion = P[0].f + PP[0].f;     //����KP
	p->Integral   = P[1].f + PP[1].f;     //����KI
	p->Derivative = P[2].f + PP[2].f;     //����KD	
}

//PID ���㺯��������������ʽ������PID ָ��pp �͵�ǰ���ThisError����ǰֵ���趨ֵ�Ĳ��
//���PID ���㺯���Ĺ�����Ҫ��������
//1���������۹�ʽ������ó�������������Ϊ��������ֵ
//2������������һ��ƫ���������ϴ�ƫ������
float PIDCal(PID *pp)
{
  float pError,dError,iError;
  float templ;

#if (PID_Mode_Select == 0)
	
  pError = pp->Error[0] - pp->Error[1];
  iError = pp->Error[0];
  dError = pp->Error[0] - 2*(pp->Error[1]) + pp->Error[2];
	
  // ��������
  templ = pp->Proportion * pError + pp->Integral * iError 
	        + pp->Derivative * dError; //����
  
	// �洢��������´�����
  pp->Error[2] = pp->Error[1];
  pp->Error[1] = pp->Error[0];
	
#else
	
//	if((pp->Error[0] - pp->Error[1]) > FILTER_VALUE)			    pp->Error[0] = pp->Error[1] + FILTER_VALUE;
//	else if((pp->Error[0] - pp->Error[1]) < -FILTER_VALUE)		pp->Error[0] = pp->Error[1] - FILTER_VALUE;
  	
  pError = pp->Error[0];
  iError = pp->Error[0] + pp->Error[1] + pp->Error[2] + pp->Error[3] + pp->Error[4];
  dError = pp->Error[0] - pp->Error[1];
	
  // λ�����������
  templ = pp->Proportion * pError + pp->Integral * iError 
	        + pp->Derivative * dError; 
  
	// �洢��������´�����	
  pp->Error[4] = pp->Error[3];
  pp->Error[3] = pp->Error[2];	
  pp->Error[2] = pp->Error[1];
  pp->Error[1] = pp->Error[0];
	
#endif
	
 return templ;
}

