#ifndef _VCAN_LCD_H_
#define _VCAN_LCD_H_

//delay.h and GPIOLIKE51根据STM32的型号选择
#include "delay.h"
#include "GPIOLIKE51.h"

#include "Color.h"
#include "VcanLcdKey.h"

#include "SystemCore.h"
#include "CString.h"
#include "stdio.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

#include "HZK16.h"
#include "Image_BMP.h"

typedef   char int8;
typedef   signed short     int int16;
typedef   signed           int int32;

typedef unsigned          char uint8;
typedef unsigned short     int uint16;
typedef unsigned           int uint32;

#define VCAN_LCD_P0_GPIO  GPIOA
#define VCAN_LCD_CTL_GPIO GPIOB
// five Ctl pin define
#define	VCAN_LCD_WR_PIN  8   
#define VCAN_LCD_RD_PIN  9 
#define VCAN_LCD_CS_PIN  10     
#define VCAN_LCD_RS_PIN  6      
#define VCAN_LCD_RST_PIN 7  

#define	VCAN_LCD_WR_OUT  PBout(VCAN_LCD_WR_PIN)   
#define VCAN_LCD_RD_OUT  PBout(VCAN_LCD_RD_PIN)   
#define VCAN_LCD_CS_OUT  PBout(VCAN_LCD_CS_PIN)    
#define VCAN_LCD_RS_OUT  PBout(VCAN_LCD_RS_PIN)     
#define VCAN_LCD_RST_OUT PBout(VCAN_LCD_RST_PIN)    

#define	VCAN_LCD_P0_0_PIN  0  
#define VCAN_LCD_P0_1_PIN  1   
#define VCAN_LCD_P0_2_PIN  2    
#define VCAN_LCD_P0_3_PIN  3    
#define VCAN_LCD_P0_4_PIN  4    
#define VCAN_LCD_P0_5_PIN  5   
#define VCAN_LCD_P0_6_PIN  6     
#define VCAN_LCD_P0_7_PIN  7 

#define VCAN_LCD_P0_OUTt(DATA) (VCAN_LCD_P0_GPIO->ODR &= 0X0000,\
															  BIT_SETval(VCAN_LCD_P0_GPIO->ODR,VCAN_LCD_P0_0_PIN,BIT_GET(DATA,0)),\
																BIT_SETval(VCAN_LCD_P0_GPIO->ODR,VCAN_LCD_P0_1_PIN,BIT_GET(DATA,1)),\
																BIT_SETval(VCAN_LCD_P0_GPIO->ODR,VCAN_LCD_P0_2_PIN,BIT_GET(DATA,2)),\
																BIT_SETval(VCAN_LCD_P0_GPIO->ODR,VCAN_LCD_P0_3_PIN,BIT_GET(DATA,3)),\
																BIT_SETval(VCAN_LCD_P0_GPIO->ODR,VCAN_LCD_P0_4_PIN,BIT_GET(DATA,4)),\
																BIT_SETval(VCAN_LCD_P0_GPIO->ODR,VCAN_LCD_P0_5_PIN,BIT_GET(DATA,5)),\
																BIT_SETval(VCAN_LCD_P0_GPIO->ODR,VCAN_LCD_P0_6_PIN,BIT_GET(DATA,6)),\
																BIT_SETval(VCAN_LCD_P0_GPIO->ODR,VCAN_LCD_P0_7_PIN,BIT_GET(DATA,7)),\
																)

#define VCAN_LCD_P0_OUT(DATA) (VCAN_LCD_P0_GPIO->ODR&=0XF0F0,\
															 VCAN_LCD_P0_GPIO->ODR|= (unsigned int)(DATA & 0x0F),\
															 VCAN_LCD_P0_GPIO->ODR|= (unsigned int)((DATA & 0xF0) <<4)\
															 )

#define VCAN_LCD_DELAY()         do{;;;;;;;;}while(0)
#define VCAN_LCD_DELAY_MS(ms)    delay_ms(ms)

#define VCAN_LCD_WR_8CMD(cmd)    do\
                            {\
                                VCAN_LCD_RD_OUT=1;;\
                                VCAN_LCD_RS_OUT=0;;\
                                VCAN_LCD_CS_OUT=0;;\
                                VCAN_LCD_P0_OUT(cmd);\
                                VCAN_LCD_WR_OUT=0;;\
                                VCAN_LCD_WR_OUT=1;;\
                                VCAN_LCD_CS_OUT=1;;\
                            }while(0)   

#define VCAN_LCD_WR_8DATA(data)  do\
                            {\
                                VCAN_LCD_RD_OUT=1;;\
                                VCAN_LCD_RS_OUT=1;;\
                                VCAN_LCD_CS_OUT=0;;\
                                VCAN_LCD_P0_OUT(data);\
                                VCAN_LCD_WR_OUT=0;;\
                                VCAN_LCD_WR_OUT=1;;\
                                VCAN_LCD_CS_OUT=1;;\
                            }while(0)   


#define VCAN_LCD_WR_DATA(data)       do{VCAN_LCD_WR_8DATA((unsigned char)((data)>>8) );\
																			VCAN_LCD_WR_8DATA( (unsigned char)(data) );}while(0)       //写数据

#define VCAN_LCD_RAMWR()             VCAN_LCD_WR_8CMD(0x2C)                //写模式


typedef
enum
{
		VcanLcdDirection_Default   = 0,
		VcanLcdDirection_Rotate90  = 1,
		VcanLcdDirection_Rotate180 = 2,
		VcanLcdDirection_Rotate270 = 3,
}VcanLcdDirection_t;

typedef
enum
{
		VcanLcdAround_Right   = 0,
		VcanLcdAround_Down    = 1,
		VcanLcdAround_Left    = 2,
		VcanLcdAround_Up      = 3,
}VcanLcdAround_t;

typedef
enum
{
		TextAlign_Right   = 0,
		TextAlign_Left    = 1,
}TextAlign_t;

typedef 
struct
{
		int ShowWidth;
		int ShowHeight;
		VcanLcdDirection_t ShowDirection;
}VcanLcdInfo_t;	

#define USE_VCANLCD_STRUCT

#ifdef USE_VCANLCD_STRUCT
typedef
struct
{
		void (*Init)(void);
		void (*ShowStr)(int x,int y,char * str);
		void (*ShowInt)(unsigned char x,unsigned char y,int val,TextAlign_t align);
		void (*ShowFloat)(unsigned char x,unsigned char y,float val,TextAlign_t align);
		
		void (*Clear)(uint16 rgb565);
	
		void (*DrawPoint)(Point site, uint16 rgb565);
		void (*DrawLine)(Point site,unsigned char lenth, Color_t Color_t,VcanLcdAround_t around);
		void (*DrawHollowRectangle)(Point site,Size size,Color_t Color_t);
		void (*DrawSolidRectangle)(Point  site, Size size, Color_t Color_t);
		void (*DrawHollowCircle)(uint16 x0,uint16 y0,uint8 r,Color_t Color_t);
	
		void (*DrawBinaryImage)(Point site, Size size, uint8 *img);
		void (*Draw24BitBMP)(unsigned short int x, unsigned short int y,unsigned char *pic_name);
		
		VcanLcdInfo_t Info;
}VcanLCD_t;

extern VcanLCD_t VcanLCD;

#endif

#define BackColor Color.Blue
#define StringColor Color.Black
#define NumTextShowBit 6

#define UP_RANGE(x,max)         ( (int16)( (x)>(max) ? (max):(x) ) ) 
#define DOWM_RANGE(x,min)				( (int16)( (x)<(min) ? (min):(x) ) )

extern unsigned char vcan_str[160];

Point NewPoint(int x,int y);
Size NewSize(int width,int height);

void VcanLCD_Ptlon(Point site, Size size);
void VcanLCD_SetShowDirection(VcanLcdDirection_t);

void VcanLCD_Init(void);
void VcanLCD_ShowString(unsigned char x,unsigned char y,char * str);
void VcanLCD_ShowChineseString(int x,int y, int8 *Str);
void VcanLCD_ShowInt(unsigned char x,unsigned char y,int val,TextAlign_t align);
void VcanLCD_ShowFloat(unsigned char x,unsigned char y,float val,TextAlign_t align);
void VcanLCD_num_BC(Point site, uint32 num, uint8 max_num_bit, uint16 Color_t, uint16 bkColor_t);

void VcanLCD_Clear(uint16 rgb565);   
void VcanLCD_ShowChar(Point site, uint8 ascii, uint16 Color_t, uint16 bkColor_t);
void VcanLCD_DrawString(Point site, int8 *Str, Color_t strColor_t, Color_t bkColor_t);
void VcanLCD_DrawPoint(Point site, uint16 rgb565);
void VcanLCD_DrawLine(Point site,unsigned char lenth, Color_t Color_t,VcanLcdAround_t around);
void VcanLCD_DrawPenRectangle(Point site,Size size,Color_t Color_t);
void VcanLCD_DrawRectangle(Point site, Size size, uint16 rgb565);
void VcanLCD_DrawRectangleWithColor_t(Point  site, Size size, Color_t Color_t);
void VcanLCD_DrawCircle(uint16 x0,uint16 y0,uint8 r,Color_t Color_t);
void VcanLCD_DrawBinaryImage(Point site, Size size, uint8 *img);
void VcanLCD_DrawBinaryImageWithColor_t(Point site, Size size, uint8 *img,uint16 OneColor_tVal,uint16 ZeroColor_tVal);
void MyRowDrawBMP(Point site, Size size, uint8 *img);

#endif
