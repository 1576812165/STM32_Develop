#ifndef __MEMORY_MANAGEMENT_H
#define __MEMORY_MANAGEMENT_H

#include "mystruct.h"
#include "24cxx.h"

#define MEMORY_BACKUPHEADADDR 0

#define MEMORY_BACKUPENDADDR 100

#define MEMORY_SPEED1PIDADDR 101

#define MEMORY_SPEED2PIDADDR 301

#define MEMORY_SPEED3PIDADDR 501

#define MEMORY_SPEED4PIDADDR 701

#define MEMORY_SPEED5PIDADDR 901

#define MEMORY_SPEED6PIDADDR 1101

#define MEMORY_SPEED1CPIDADDR 1301

#define MEMORY_SPEED2CPIDADDR 1501

#define MEMORY_SPEED3CPIDADDR 1701

#define MEMORY_SPEED4CPIDADDR 1901

#define MEMORY_SPEED5CPIDADDR 2101

#define MEMORY_SPEED6CPIDADDR 2301

#define MEMORY_DISPLAYMSGADDR 2501

#define MEMORY_SYSTEMSETADDR 2601

#define MEMORY_CONTROLMSGADDR 2701

#define MEMORY_LINESUMNUMADDR 2900

#define MEMORY_MAPMANAGEADDR 2901

#define MEMORY_MAPSTATIONADDR 5001

#define MEMORY_MAPLINENUMADDR 5251

#define MEMORY_GOODSACTIONADDR 6501



extern Speed_Data_type Speed_Data[6];
extern Speed_Data_type Speed_Correction_Data[6];
//extern Control_Data_type Control_Data;
extern Line_Data_type Line_Data;
extern uint16_t Record_Speed_Correction_Data_Adress;

void Base_Data_Load(void);
void Car_Move_Parametr_Init(void);

#endif
