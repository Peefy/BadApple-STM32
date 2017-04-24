
#include "BadApple.h"

#define BUFFERSIZE      1024
#define TEST_FILENAME    "test.txt"

#define BadApple_FILENAME "badapple.bin"

FIL fsrc;					/* File objects */
FATFS Fatfs;				/* File system specific */
FRESULT res;				/* FatFs function common result code */
UINT br, bw;				/* File read/write count */
DSTATUS resCard;			/* SDcard status */
uint8_t ramBufferWrite[BUFFERSIZE];	/* Temporary buffer for write file */
uint8_t ramBufferRead[BUFFERSIZE];	/* Temporary buffer for read file */
int8_t StringBuffer[] = "TestText is hello world!!!";



void initMicroSD(void);
void initVcanLcd(void);
void BadApple_Init(void);
void BadApple_Start(void);

BadAppleInit_Typedef BadApple = {BadApple_Init,BadApple_Start};
BadAppleInfo_t BadAppleInfo = {false};

BadAppleInit_Typedef NewBadApple(void)
{
	BadAppleInit_Typedef badapple;
	badapple.Init = BadApple_Init;
	badapple.Start = BadApple_Start;
	return badapple;
}

void initMicroSD(void)
{
		int16_t i;
		int16_t filecounter = sizeof(StringBuffer);
		for(i = 0; i < filecounter ; i++)
			ramBufferWrite[i] = StringBuffer[i];		
		VcanLCD_ShowChineseString(3,7,"Error:NoCard  ");
		MSD_SPI_Configuration();
		while (1)
		{
				//		MSD_Init();                     /*Initialize MicroSD driver */
				VcanLCD_ShowChineseString(3,7,"Error:MSDInit ");
				resCard = disk_initialize(0);       /*Check micro-SD card status */

				switch(resCard){
				case STA_NOINIT:                    /* Drive not initialized */
					break;
				case STA_NODISK:                    /* No medium in the drive */
					break;
				case STA_PROTECT:                   /* Write protected */
					break;
				default:
					break;
			}

			if (!resCard) break;                /* Drive initialized. */
			systick_delayMs(1);
    }
		/*Step3*/
	/* Initialize filesystem */
	if (f_mount(0, &Fatfs) != FR_OK)
	{
		/* Error.No micro-SD with FAT32 is present */
		VcanLCD_ShowChineseString(3,7,"Error:FAT32SD ");
		while(1);
	}

	/*Step4*/
	/* Open  the file for write */
	res = f_open(&fsrc, TEST_FILENAME,  FA_WRITE);
	if (res != FR_OK)
	{
		/*  If file does not exist create it*/
		res = f_open(&fsrc, TEST_FILENAME, FA_CREATE_ALWAYS | FA_WRITE );
		if (res != FR_OK)
		{
			VcanLCD_ShowChineseString(3,7,"Error:FileOut ");
			while(1);
		}
	}

	/*Step5*/
	/*Set the file write pointer to first location */
	res = f_lseek(&fsrc, 0);
	if (res != FR_OK)
	{
		/* Error. Cannot set the file write pointer */
		VcanLCD_ShowChineseString(3,7,"Error:FileSet ");
		while(1);
	}

	/*Step6*/
	/*Write a buffer to file*/
	res = f_write(&fsrc, ramBufferWrite, filecounter, &bw);
	if ((res != FR_OK) || (filecounter != bw))
	{
		/* Error. Cannot write the file */
		VcanLCD_ShowChineseString(3,7,"Error:FileWrte");
		while(1);
	}

	/*Step7*/
	/* Close the file */
	f_close(&fsrc);
	if (res != FR_OK)
	{
		/* Error. Cannot close the file */
		VcanLCD_ShowChineseString(3,7,"Error:FileClos");
		while(1);
	}

	/*Step8*/
	/* Open the file for read */
	res = f_open(&fsrc, TEST_FILENAME,  FA_READ);
	if (res != FR_OK)
	{
		/* Error. Cannot create the file */
		VcanLCD_ShowChineseString(3,7,"Error:FileOut ");
		while(1);
	}

	/*Step9*/
	/*Set the file read pointer to first location */
	res = f_lseek(&fsrc, 0);
	if (res != FR_OK)
	{
		/* Error. Cannot set the file pointer */
		VcanLCD_ShowChineseString(3,7,"Error:FileSet ");
		while(1);
	}

	/*Step10*/
	/* Read some data from file */
	res = f_read(&fsrc, ramBufferRead, filecounter, &br);
	if ((res != FR_OK) || (filecounter != br))
	{
		/* Error. Cannot read the file */
		VcanLCD_ShowChineseString(3,7,"Error:FileRead");
		while(1);
	}

	/*Step11*/
	/* Close the file */
	res = f_close(&fsrc);
	if (res != FR_OK)
	{
		/* Error. Cannot close the file */
		VcanLCD_ShowChineseString(3,7,"Error:FileClos");
		while(1);
	}

	/*Step12*/
	/*Compare ramBufferWrite and ramBufferRead */
	for(i = 0; i < filecounter ; i++)
	{
		if ((ramBufferWrite[i]) != (ramBufferRead[i]))
		{
			/* Error compare buffers*/
			VcanLCD_ShowChineseString(3,7,"Error:FileTest");
			while(1);
		}
	}
	
	VcanLCD.Clear(BackColor.RBG565Value);
}

void initVcanLcd(void)
{
		VcanLCD_Init();
}

void BadApple_Init(void)
{
		VcanLCD.Init();
		initMicroSD();
}

void BadApple_BeforeEvents(void)
{
	VcanLCD_Clear(BackColor.RBG565Value);	
	//VcanLCD_DrawRectangleWithColor(NewPoint(70,39),NewSize(50,50),ColorRed);
	//VcanLCD_ShowString(68,0,"Bad");
	//VcanLCD_ShowString(68,1,"<----");
	//VcanLCD_ShowString(68,6,"<----");
	//VcanLCD_ShowString(68,7,"Apple");
	VcanLcd_ShowBMP(64,0,"lcdshow2.bmp");
}

void BadApple_AfterEvents(void)
{
	VcanLCD_Clear(BackColor.RBG565Value);	 
	TIM_Cmd(TIM2,ENABLE);
	BadAppleInfo.Enable = false;
	
}

void BadApple_Start(void)
{
	int i;
	
	BadApple_BeforeEvents();
	
	res = f_open(&fsrc, BadApple_FILENAME,  FA_READ);
	if (res != FR_OK)
	{
		VcanLCD_ShowChineseString(3,7,"Error:FileOut ");
		while(1);
	}

	res = f_lseek(&fsrc, 0);
	if (res != FR_OK)
	{
		VcanLCD_ShowChineseString(3,7,"Error:FileSet ");
		while(1);
	}
	for(i=0;i<6566;i++)
	{
		res = f_read(&fsrc, ramBufferRead,1024, &br);
		if ((res != FR_OK) || (1024 != br))
		{
			VcanLCD_ShowChineseString(3,7,"Error:FileRead");
			while(1);
		}
		MyRowDrawBMP(NewPoint(0,0),NewSize(128,64),ramBufferRead);	
		PerFrameDelay();
	}
	res = f_close(&fsrc);
	if (res != FR_OK)
	{
		/* Error. Cannot close the file */
		VcanLCD_ShowChineseString(3,7,"Error:FileClos");
		while(1);
	}
	BadApple_AfterEvents();
}

