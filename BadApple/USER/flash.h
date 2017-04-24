#ifndef _FLASH_H_
#define _FLASH_H_

#include "include.h"
			 
u32 Readflash(char i);
void Writeflash(void);
void WriteFlashSerMid(void);
void PowerOnReadFlashPara(void);
void WriteflashOn(int writeOffsetAddress,u32 writeData);

#define FlashOffSetAddr0 0 
#define FlashOffSetAddr1 4
#define FlashOffSetAddr2 8 
#define FlashOffSetAddr3 12 
#define FlashOffSetAddr4 16 
#define FlashOffSetAddr5 20 
#define FlashOffSetAddr6 24 
#define FlashOffSetAddr7 28 
#define FlashOffSetAddr8 32 

#endif
