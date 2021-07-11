#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"

unsigned char TIM1_PWM_setFrequency(int fre);
void TIM1_PWM_Init(u16 arr,u16 psc);
#endif

