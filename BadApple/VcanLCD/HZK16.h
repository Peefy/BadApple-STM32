#ifndef _HZK16_H_
#define _HZK16_H_


#include "ff.h"
#include "diskio.h"
#include "VcanLCDforSTM32.h"
#include "SystemCore.h"

#define HZ_WIDTH   16
#define HZ_HEIGHT  16
#define HZ_BUFF_SIZE 32

extern FIL myfsrc;					/* File objects */
extern FATFS myFatfs;				/* File system specific */
extern FRESULT myres;				/* FatFs function common result code */
extern UINT mybr, mybw;				/* File read/write count */

int GetGBKCodeFromSD(unsigned char* pBuffer,const unsigned char * c);
void VcanLCD_DrawMuxString(Point site, int8 *Str, uint16 strColor_t, uint16 bkColor_t);
void VcanLCD_ShowMuxString(int x,int y, int8 *Str);

#endif


