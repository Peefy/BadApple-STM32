#include "include.h"


void All_Init(void)
{
	  delay_init(72);	    		//延时函数初始化			
		VcanLcdKeyInit();
	  LED_Init();         		//板子上的灯初始化	
		TIM2_Init();       			//10ms定时器
}

