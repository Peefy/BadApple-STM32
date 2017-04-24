/*******************************************************************************
 * File				:	stm32f10x_ina219.c
 * Description		:	STM32F10x library for INA219 sensor which reads
 * 						shunt, current and power ratings
 * Datum			:	2015.03.06
 * Version			:	1.0
 * Author			:	Aytac Dilek
 * email			:	aytacdilek@gmail.com
 * Web				:
 * Platform			:	OPEN103Z-B
 * CPU				:	STM32F103ZET6
 * IDE				:	CooCox CoIDE 1.7.7
 * GCC				:	4.8 2014q2
 * Module			:	INA219
 * Function			:	Read shunt, current and power readings
 * Pin Definitions	:	PB6 => SCL
 * 						PB7 => SDA
*******************************************************************************/


/* Includes *******************************************************************/
#include "stm32f10x_fatfs.h"


/* Global Variables ***********************************************************/
static FATFS FileSystemObject;


/*******************************************************************************
* Function Name		:	fatfs_init
* Description		:	Initialize FATFS library and peripheral
* Input				:	None
* Output			:	None
* Return			:	None
* Attention			:	None
*******************************************************************************/
void fatfs_init(void){
	/* init hardware for the SD card functions */
	MSD_Init();
	/* init the hardware for the USB functions */
//	USBDisk_Init();
	/* init hardware for ATA features */
//	ATADrive_Init();
}



/*******************************************************************************
* Function Name		:	fatfs_checkMedia
* Description		:	Query state of the medium
* Input				:	media
* 						- MMC_0
* Output			:	None
* Return			:	FATFS_OK			=>	No Error
* 						FATFS_NO_MEDIA 	=>	No Media Inserted
* Attention			:	None
*******************************************************************************/
FATFSError_TypeDef fatfs_checkMedia(MEDIA_TypeDef media){
	
		FATFSError_TypeDef ret_value = FATFS_MOUNT_ERR;
	FRESULT check = FR_INVALID_OBJECT;

	return (ret_value);
	
}



/*******************************************************************************
* Function Name		:	fatfs_mount
* Description		:	Mount media
* Input				:	media
* 						- MMC_0
* Output			:	None
* Return			:	FATFS_OK    	=>	Media Inserted
* 						FATFS_MOUNT_ERR		=>	Error
* 						FATFS_GETFREE_ERR	=> Error
* Attention			:	None
*******************************************************************************/
FATFSError_TypeDef fatfs_mount(MEDIA_TypeDef media){
	FATFSError_TypeDef ret_value = FATFS_MOUNT_ERR;
	FRESULT check = FR_INVALID_OBJECT;
	DWORD fre_clust;

	FATFS	*fs;

	/* Initialize filesystem */
	if(media == MMC_0)
		check = f_mount(0, &FileSystemObject);

	if(check == FR_OK){
		if(media == MMC_0)
			check = f_getfree("0:", &fre_clust, &fs);
		if(check == FR_OK)
			ret_value = FATFS_OK;
		else
			ret_value = FATFS_GETFREE_ERR;
	}
	else {
		ret_value = FATFS_MOUNT_ERR;
	}

	return(ret_value);
}



/*******************************************************************************
* Function Name		:	fatfs_unmount
* Description		:	Unmount media
* Input				:	media
* 						- MMC_0
* Output			:	None
* Return			:	FATFS_OK    	=>	Media Inserted
* 						FATFS_MOUNT_ERR => 	Error
* Attention			:	None
*******************************************************************************/
FATFSError_TypeDef fatfs_unmount(MEDIA_TypeDef media){
	FATFSError_TypeDef ret_value = FATFS_MOUNT_ERR;
	FRESULT check = FR_INVALID_OBJECT;

	/* Initialize filesystem */
	if(media == MMC_0)
		check = f_mount(0, &FileSystemObject);

	if(check == FR_OK)
		ret_value = FATFS_OK;
	else
		ret_value = FATFS_MOUNT_ERR;

	return(ret_value);
}



/*******************************************************************************
* Function Name		:	fatfs_openFile
* Description		:	Open the file (for reading or writing)
* Input				:	fp - Passed by File & operator
* 						filename - Name is the complete path, for example, "0: /Test.txt"
* 						mode - [F_RD, F_WR, F_WR_NEW, F_WR_CLEAR]
* Output			:	None
* Return			:	FATFS_OK    	=>	No Error
* 						FATFS_OPEN_ERR 	=> 	Error
* 						FATFS_SEEK_ERR 	=> 	Error WR and WR_NEW
* Attention			:	None
*******************************************************************************/
FATFSError_TypeDef fatfs_openFile(FIL* fp, const char* filename, FILEOpen_TypeDef mode){
	FATFSError_TypeDef ret_value = FATFS_MOUNT_ERR;
	FRESULT check = FR_INVALID_OBJECT;

	if(mode == FILE_READ)
		check = f_open(fp, filename, FA_OPEN_EXISTING | FA_READ);
	if (mode == FILE_WRITE)
		check = f_open(fp, filename, FA_OPEN_EXISTING | FA_WRITE);
	if(mode == FILE_WRITE_NEW)
		check = f_open(fp, filename, FA_OPEN_ALWAYS | FA_WRITE);
	if(mode == FILE_WRITE_CLEAR)
		check = f_open(fp, filename, FA_CREATE_ALWAYS | FA_WRITE);

	if(check == FR_OK){
		ret_value = FATFS_OK;

		if(mode == FILE_WRITE || mode == FILE_WRITE_NEW){
			/* Provide pointers to the end of file */
			check = f_lseek(fp, f_size(fp));
			if (check != FR_OK)
				ret_value = FATFS_SEEK_ERR;
		}
	}
	else{
		ret_value = FATFS_OPEN_ERR;
	
	}
	
	return (ret_value);
	
}



/*******************************************************************************
* Function Name		:	fatfs_closeFile
* Description		:	Close the file
* Input				:	fp - Passed by File & operator
* Output			:	None
* Return			:	FATFS_OK    	=>	No Error
* 						FATFS_CLOSE_ERR => 	Error
* Attention			:	None
*******************************************************************************/
FATFSError_TypeDef fatfs_closeFile(FIL* fp){
	FATFSError_TypeDef ret_value = FATFS_MOUNT_ERR;
	FRESULT check = FR_INVALID_OBJECT;

	check = f_close(fp);

	if(check == FR_OK)
		ret_value = FATFS_OK;
	else
		ret_value = FATFS_CLOSE_ERR;

	return (ret_value);
	
}



/*******************************************************************************
* Function Name		:	fatfs_writeString
* Description		:	Write string to file
* Input				:	fp - Passed by File & operator
* Output			:	None
* Return			:	FATFS_OK    	=>	No Error
* 						FATFS_PUTS_ERR 	=> Error
* Attention			:	File must be open
* 						Line end identifier ('\ n') is automatically appended
*******************************************************************************/
FATFSError_TypeDef fatfs_writeString(FIL* fp, const char* text){
	
	FATFSError_TypeDef ret_value = FATFS_MOUNT_ERR;
	FRESULT check = FR_INVALID_OBJECT;

	return (ret_value);
	
}
