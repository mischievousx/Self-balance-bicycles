#ifndef __PWM_H 
#define __PWM_H 
#include "sys.h" 

void PWM_Init_TIM3(u16 arr,u16 psc);
void PWM_Init_TIM2(u16 arr,u16 psc);
void Init_TIM1(u16 arr,u16 psc);
#endif 