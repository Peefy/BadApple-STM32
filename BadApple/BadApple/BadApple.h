#ifndef _BADAPPLE_H_
#define _BADAPPLE_H_

#include "stdbool.h"
#include "ff.h"
#include "diskio.h"

#include "delay.h"
#include "CString.h"
#include "SystemCore.h"

#include "VcanLCDforSTM32.h"
#include "Image_BMP.h"
#include "stm32f10x_tim.h"
#include "led.h"

#define PerFrameDelayUs 4277
#define PerFrameDelay() delay_us(PerFrameDelayUs)

typedef 
struct BadApple
{
	void (*Init)(void);
	void (*Start)(void);
}BadAppleInit_Typedef;

typedef 
struct BadAppleinfo
{
	bool Enable;
}BadAppleInfo_t;

extern char BadAppleBMP[512];
extern BadAppleInit_Typedef BadApple;

extern BadAppleInfo_t BadAppleInfo;
BadAppleInit_Typedef NewBadApple(void);

#endif


