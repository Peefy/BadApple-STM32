#ifndef _VCANLCDKEY_H_
#define _VCANLCDKEY_H_

#include "stdbool.h"

#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

#define KeyUp_GPIO GPIOB
#define KeyUp_PIN 14
#define KeyDown_GPIO GPIOB
#define KeyDown_PIN 15
#define KeyLeft_GPIO GPIOA
#define KeyLeft_PIN 9
#define KeyRight_GPIO GPIOB
#define KeyRight_PIN 13
#define KeyMiddle_GPIO GPIOC
#define KeyMiddle_PIN 15

#define JudgeKeyStatus GPIO_ReadInputDataBit


//#define KeyUpEnable 1
//#define KeyDownEnable 1
//#define KeyLeftEnable 1
#define KeyRightEnable 1
//#define KeyMiddleEnable 1

typedef
enum
{
	KeyValue_Up     = 4,
	KeyValue_Down   = 2,
	KeyValue_Left   = 3,
	KeyValue_Right  = 1,
	KeyValue_Middle = 5,
	KeyValue_None   = 0,
}KeyValue_t;

typedef
enum
{
	KeyStatus_Down   = 0,
	KeyStatus_Up     = 1,
}KeyStatus_t;

void VcanLcdKeyInit(void);
void VcanKeyIRQHandler(void);

#endif

