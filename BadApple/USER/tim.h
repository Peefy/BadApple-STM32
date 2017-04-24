#ifndef _TIM_H_
#define _TIM_H_

#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"

#include "SystemCore.h"

void TIM2_Init(void);
void TIM2_Init_ms(int16 ms);

#endif
