
#include "HZK16.h"

FIL myfsrc;					/* File objects */
FATFS myFatfs;				/* File system specific */
FRESULT myres;				/* FatFs function common result code */
UINT mybr, mybw;				/* File read/write count */

#define HZLIB_FILENAME "hzlib.bin"

//注意汉字的取模方式为行列式
int GetGBKCodeFromSD(unsigned char* pBuffer,const unsigned char * c)
{ 
    unsigned char High8bit,Low8bit;
    unsigned int pos;
    High8bit=*c;     /* 取高8位数据 */
    Low8bit=*(c+1);  /* 取低8位数据 */
    pos = ((High8bit-0xa0-16)*94+Low8bit-0xa0-1)*2*16 ;	
		myres = f_open(&myfsrc, HZLIB_FILENAME,  FA_READ);
		if (myres != FR_OK)
		{
			VcanLCD_ShowString(3,7,"Error:FileOut ");
			while(1);
		}
    f_lseek (&myfsrc, pos);		//指针偏移
		f_read( &myfsrc, pBuffer, 32, &mybr );		        
    f_close(&myfsrc);
        
    return 1;  
}    

void VcanLCD_DrawMuxString(Point site, int8 *Str, uint16 strColor_t, uint16 bkColor_t)
{
#define MAX_CHAR_POSX (VcanLCD.Info.ShowWidth-8)
#define MAX_CHAR_POSY (VcanLCD.Info.ShowHeight-16)				 
//    Size size = {8, 16};
		Size HZsize = {16, 16};
		int index = 0;
    while(*Str != '\0')
    {
        if(site.X > MAX_CHAR_POSX )
        {
            //换行
            site.X = 0;
            site.Y += 16;
        }
        if(site.Y > MAX_CHAR_POSY )
        {
            //一屏
            site.Y = 0;
            site.X = 0;
        }
				if(*Str > 127)  //汉字
				{	
					uint8_t page , column;
					uint8_t buffer[32];		
					uint16_t tmp_char=0;
					if(site.X > MAX_CHAR_POSX || site.Y > MAX_CHAR_POSY)
					{
						return;
					}
					GetGBKCodeFromSD(buffer,(const unsigned char *)Str);
					VcanLCD_Ptlon(site, HZsize);
					VCAN_LCD_RAMWR(); 
					for(page=0; page< 16; page++)
					{
						tmp_char=buffer[page*2];
						tmp_char=(tmp_char<<8);
						tmp_char|=buffer[2*page+1];
		
						for (column=0; column< 16; column++)
						{			
							if ( tmp_char & (0x01<<15) )
							{				
									VCAN_LCD_WR_DATA(strColor_t);
							}
							else
							{			
									VCAN_LCD_WR_DATA(bkColor_t);
							}
							tmp_char <<= 1;
						}
					}	
					index ++;
					site.X += 8;
					Str ++ ;
				}
				else
					VcanLCD_ShowChar(site, *Str, strColor_t, bkColor_t);
        site.X += 8;
        Str ++ ;
	
    }
#undef MAX_CHAR_POSX
#undef MAX_CHAR_POSY
}

void VcanLCD_ShowMuxString(int x,int y, int8 *Str)
{
			VcanLCD_DrawMuxString(NewPoint(x,y*16),Str,\
					StringColor.RBG565Value,BackColor.RBG565Value);
}
