#ifndef __DELAY_H
#define __DELAY_H 			   
#include "stm32f10x.h"

////////////////////////////////////////////////////////////////////////////////// 
void delay_init(u8 SYSCLK);
void delay_ms(u16 nms);
void delay_us(u32 nus);

#define UiThreadDelay(ms) delay_ms(ms)
#define UiDelayMS 50

#define systick_delayMs(ms) delay_ms(ms)

#endif





























