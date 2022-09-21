#ifndef __TIM4_PWM_H
#define __TIM4_PWM_H

#include "sys.h"

void TIM4_PWM_Init(u16 arr,u16 psc);
void SetPWM1(int pwm1);
void SetPWM2(int pwm2);

#endif

