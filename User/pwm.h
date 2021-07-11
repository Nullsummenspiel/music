#ifndef __PWM_H
#define __PWM_H
#include "sys.h"


unsigned char TIM1_PWM_setFrequency(int fre);
void TIM1_PWM_Init(u16 arr,u16 psc);
void ADVANCE_TIM_NVIC_Config(void);

#endif
