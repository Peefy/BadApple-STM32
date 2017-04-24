
#include "Color.h"

Color_t ColorFromARGB(unsigned char R,unsigned char G,unsigned char B);
Color_t ColorFromRGB24Value(unsigned int rgb24);
Color_t ColorFromRBG565Value(unsigned short int rgb565);
Color_t ColorFromGrayValue(unsigned char gray);

ColorInit_t Color;

void ColorInit(void)
{
	Color.FromARGB = ColorFromARGB;
	Color.FromRGB24Value = ColorFromRGB24Value;
	Color.FromRBG565Value = ColorFromRBG565Value;
	Color.FromGrayValue = ColorFromGrayValue;
	Color.Red = ColorFromRBG565Value(0XF800);
  Color.Green = ColorFromRBG565Value(0X07E0);
	Color.Blue = ColorFromRBG565Value(0X001F);
	Color.Bred = ColorFromRBG565Value(0XF81F);
	Color.Gred = ColorFromRBG565Value(0XFFE0);
	Color.Gblue = ColorFromRBG565Value(0X07FF);
	Color.Black = ColorFromRBG565Value(0X0000);
	Color.White = ColorFromRBG565Value(0XFFFF);
	Color.Yellow = ColorFromRBG565Value(0XFFE0);
	Color.Purple = ColorFromARGB(0xCC,0x33,0xCC);
	Color.LightBlue = ColorFromRGB24Value(0x98F5FF);
	Color.Gray = ColorFromRGB24Value(0x808080);
}

Color_t ColorFromARGB(unsigned char R,unsigned char G,unsigned char B)
{
	Color_t color;
	color.RBG565Value =	(unsigned short int)((((unsigned char)(R)>>3)<<11)|\
			(((unsigned char)(G)>>2)<<5)|((unsigned char)(B)>>3));
	color.R = R;
	color.G = G;
	color.B = B;
	color.GrayValue = ((R*235+G*613+B*625)+1)>>8;
	return color;
}

Color_t ColorFromRGB24Value(unsigned int rgb24)
{
	unsigned char R = (unsigned char) (rgb24 >> 16);
	unsigned char G = (unsigned char) (rgb24 >>  8);
	unsigned char B = (unsigned char) (rgb24 >>  0);
	return ColorFromARGB(R,G,B);
}

Color_t ColorFromRBG565Value(unsigned short int rgb565)
{
	Color_t color;
	color.RBG565Value = rgb565;
	color.R = (unsigned char)(((rgb565)>>11) &0x1F);
  color.G = (unsigned char)(((rgb565)>> 5) &0x3F);
  color.B = (unsigned char)( (rgb565)      &0x1F);
	color.GrayValue = ((color.R*235+color.G*613+color.B*625)+1)>>8;
	return color;
}

Color_t ColorFromGrayValue(unsigned char gray)
{
	Color_t color;
	color.RBG565Value = (unsigned short int)((((unsigned char)(gray)>>3)<<11)|(((unsigned char )(gray)>>2)<<5)|\
	((unsigned char )(gray)>>3));
	color.R = (unsigned char)(((color.RBG565Value)>>11) &0x1F);
  color.G = (unsigned char)(((color.RBG565Value)>> 5) &0x3F);
  color.B = (unsigned char)( (color.RBG565Value)      &0x1F);

	return color;
}



