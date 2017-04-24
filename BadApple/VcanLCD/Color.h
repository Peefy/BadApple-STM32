#ifndef _COLOR_H_
#define _COLOR_H_

/**
  ******************************************************************************
  * @file    Color.c
  * @author  DuGu
  * @version V1.1.5
  * @date    10/14/2016
  * @brief   Some Function About Color
						 The following functions on a 32-bit machine
  ******************************************************************************
**/

#define RGB565_R(rgb565)                ((uint8)(((uint16)(rgb565)>>11) &0x1F))
#define RGB565_G(rgb565)                ((uint8)(((uint16)(rgb565)>> 5) &0x3F))
#define RGB565_B(rgb565)                ((uint8)( (uint16)(rgb565)      &0x1F))

#define Gray2RGB565(gray)               ((uint16)((((uint8)(gray)>>3)<<11)|(((uint8)(gray)>>2)<<5)|((uint8)(gray)>>3)))

#define RGB565_2_GRAY(rgb565)           ((uint8)(((RGB565_R(rgb565)*235+RGB565_G(rgb565)*613+RGB565_B(rgb565)*625)+1)>>8))  //  31*235+63*613+31*625+1  = 255*256

#define RGB565_H(rgb565)                ((uint8)(((uint16)(rgb565))>>8))
#define RGB565_L(rgb565)                (uint8)(rgb565))

#define RGB24_RGB565(R,G,B)             ((uint16)((((uint8)(R)>>3)<<11)|(((uint8)(G)>>2)<<5)|((uint8)(B)>>3)))
#define RGB555_RGB565(rgb555)           (((((uint16)(rgb555)) & (uint16)(~0x1F)) << 1) |  (((uint16)(rgb555)) & 0x1F))
#define BGR555_RGB565(bgr555)           ((((uint16)(bgr555)<<11) & (uint16)(0x1F<<11)) | (((uint16)(bgr555)) & (uint16)(0x1F<<5)) | (((uint16)(bgr555)>>10) & (uint16)(0x1F)))

#define	Color_Red     0XF800
#define Color_Green   0X07E0
#define	Color_Blue    0X001F
#define	Color_Bred    0XF81F
#define	Color_Gred    0XFFE0
#define	Color_Gblue   0X07FF
#define	Color_Black   0X0000
#define	Color_White   0XFFFF
#define	Color_Yellow  0XFFE0

__packed typedef
struct
{
	unsigned char R;
	unsigned char B;
	unsigned char G;
	unsigned char Alpha;	
	unsigned char GrayValue;
	unsigned short int RBG565Value;

}Color_t;

typedef
struct
{
	Color_t Red;
	Color_t Green;
	Color_t Blue;
	Color_t Bred;
	Color_t Gred;
	Color_t Gblue;
	Color_t Black;
	Color_t White;
	Color_t Yellow;
	Color_t Purple;
	Color_t LightBlue;
	Color_t Gray;
	Color_t (*FromARGB)(unsigned char R,unsigned char G,unsigned char B);
	Color_t (*FromRGB24Value)(unsigned int rgb24);
	Color_t (*FromRBG565Value)(unsigned short int rgb565);
	Color_t (*FromGrayValue)(unsigned char gray);
}ColorInit_t;

extern ColorInit_t Color;

void ColorInit(void);


#endif

