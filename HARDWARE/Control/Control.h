#ifndef __CONTROL_H
#define __CONTROL_H

#include "sys.h"
#include "TIM4_PWM.h"
#include "MyVariable.h"
#include "UART4.h"
#include "Menu.h"
#include "PID.h"

#define BEEP PCout(2)

extern int L;
extern int Angle;
extern int Pos;
void Get_Pos(void);
int RangeM1(int pwm);
void X_Control(void);
void Get_Distance(void);
void Beep_Init(void);
void Sound(u16 frq);
void Sound2(u16 time);
void play_music(void);




#endif

