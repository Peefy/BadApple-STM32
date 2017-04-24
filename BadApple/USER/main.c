
#include "include.h"     //�������е�ͷ�ļ�

#define GrayShowWidth 8
#define GrayShowHeight 4

int main(void)
{		
		SystemInit(); 			 //ϵͳʱ�ӳ�ʼ��Ϊ72M	  SYSCLK_FREQ_72MHz
		All_Init();	         // HardWare Init
		BadApple.Init();
		while (1)
		{
				int i,j;
				static int k = 0;
				if(BadAppleInfo.Enable == false)
				{
					for(j = 0;j<256/(128/GrayShowWidth) + 3;j++)
					{
						for(i = 0;i<128/GrayShowWidth;++i)
						{	
								VcanLCD.DrawSolidRectangle(\
									NewPoint(GrayShowWidth * i ,GrayShowHeight*j), \
									NewSize(GrayShowWidth,GrayShowHeight),\
									Color.FromGrayValue(k++) );
						}
					}
					VcanLCD.ShowStr(0,5,"�밴���ҷ��򰴼�");
					VcanLCD.ShowStr(0,6,"��ʼ����BadApple");
					VcanLCD.ShowStr(0,7,\
							Str.Add3("MicroSD_Cap:",\
								Str.Int2Str(MSD_RealCapacity),\
								"MB" \
						));
				}
				else
				{
					BadApple.Start();					
				}
				
		}
}






