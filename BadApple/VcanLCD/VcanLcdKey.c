
#include "VcanLcdKey.h"

#include "stm32f10x_tim.h"
#include "BadApple.h"

void VcanLcdKeyInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC |RCC_APB2Periph_GPIOB|
		RCC_APB2Periph_GPIOA, ENABLE);  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  
#ifdef KeyUpEnable	
  GPIO_InitStructure.GPIO_Pin = (1 << KeyUp_PIN);
	GPIO_Init(KeyUp_GPIO, &GPIO_InitStructure);
#endif
#ifdef KeyDownEnable	
	GPIO_InitStructure.GPIO_Pin = (1 << KeyDown_PIN);
	GPIO_Init(KeyDown_GPIO, &GPIO_InitStructure);
#endif
	#ifdef KeyLeftEnable	
  GPIO_InitStructure.GPIO_Pin = (1 << KeyLeft_PIN);
	GPIO_Init(KeyLeft_GPIO, &GPIO_InitStructure);
#endif
#ifdef KeyRightEnable	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_Init(KeyRight_GPIO, &GPIO_InitStructure);
#endif
#ifdef KeyMiddleEnable	
	GPIO_InitStructure.GPIO_Pin = (1 << KeyMiddle_PIN);
	GPIO_Init(KeyMiddle_GPIO, &GPIO_InitStructure);
#endif
}

unsigned char KeyScanToKeyValue(void)
{
		#ifdef KeyUpEnable
		if (JudgeKeyStatus(KeyUp_GPIO,KeyUp_PIN)         == KeyStatus_Down)
			return KeyValue_Up;
		#endif
		#ifdef KeyDownEnable
		if (JudgeKeyStatus(KeyDown_GPIO,KeyDown_PIN)     == KeyStatus_Down)
			return KeyValue_Down;
		#endif
		#ifdef KeyLeftEnable
		if (JudgeKeyStatus(KeyLeft_GPIO,KeyLeft_PIN)     == KeyStatus_Down)
			return KeyValue_Left;
		#endif
		#ifdef KeyRightEnable
		if (JudgeKeyStatus(KeyRight_GPIO,KeyRight_PIN)   == KeyStatus_Down)
			return KeyValue_Right;
		#endif
		#ifdef KeyMiddleEnable
		if (JudgeKeyStatus(KeyMiddle_GPIO,KeyMiddle_PIN) == KeyStatus_Down)
			return KeyValue_Middle;
		#endif
		return KeyValue_None;
}

void VcanKeyIRQHandler(void)
{
		if (JudgeKeyStatus(GPIOB,GPIO_Pin_13)   == 0)
		{
			BadAppleInfo.Enable = true;
			TIM_Cmd(TIM2,DISABLE);   //使能定时器
		}
			
}


