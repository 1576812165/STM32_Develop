#ifndef __CONTROL_H
#define __CONTROL_H

#include "stm32f10x_conf.h"

#define MOTOR_DISABLE  RMotor_stop = 1;\
                       LMotor_stop = 1;\
											 Set_Motor_Out(0,0); //防止使能后，突然启动

#define MOTOR_ENABLE  RMotor_stop = 0;\
                      LMotor_stop = 0;

extern PID PIDcontrol;
extern automatic_para automatic_control;

void Get_Magneticsensor_Information(void);
void Get_Action_Commend(uint8_t number);
void Car_Move_control(void);
void Roller_With_Screen(uint8_t before_status,uint8_t rear_status,uint8_t roller_direction);
void Nav_Station_test(void);

#endif
