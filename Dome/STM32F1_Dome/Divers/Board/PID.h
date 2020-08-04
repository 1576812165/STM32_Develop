#ifndef __PID_H
#define __PID_H

#include "mystruct.h"

void PIDInit(PID *p,float4Byte *P,float4Byte *PP);
float PIDCal(PID *pp);

#endif
