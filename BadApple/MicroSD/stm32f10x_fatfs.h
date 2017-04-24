/*******************************************************************************
* File  		:	stm32f10x_fatfs.h
* Description	: 	STM32F10x library for FATFS library
* Author		: 	Aytac Dilek
* Note			: 	GNU General Public License, version 3 (GPL-3.0)
*******************************************************************************/
#ifndef __STM32F10X_FATFS_H
#define __STM32F10X_FATFS_H



/* Includes *******************************************************************/
#include "stm32f10x.h"
#include "ff.h"
#include "stm32f10x_microsd.h"


/* Defines ********************************************************************/



/* Enumerations ***************************************************************/
typedef enum{
	/* Media types (in this LIB only MMC) */
	MMC_0 = 0,					//	in this LIB is only "MMC" supported
}MEDIA_TypeDef;

typedef enum{
	/* Error Codes */
	FATFS_OK =0,
	FATFS_NO_MEDIA,
	FATFS_MOUNT_ERR,
	FATFS_GETFREE_ERR,
	FATFS_UNLINK_ERR,
	FATFS_OPEN_ERR,
	FATFS_CLOSE_ERR,
	FATFS_PUTS_ERR,
	FATFS_SEEK_ERR,
	FATFS_RD_STRING_ERR,
	FATFS_RD_BLOCK_ERR,
	FATFS_WR_BLOCK_ERR,
	FATFS_EOF,
	FATFS_DISK_FULL
}FATFSError_TypeDef;

typedef enum{
	/* Modes for File Open */
	FILE_READ = 0,				// Open for reading (only if file exists)
	FILE_WRITE,					// open it for writing (only if file exists) and append data
	FILE_WRITE_NEW,				// open it for writing (and event. edit) and append data
	FILE_WRITE_CLEAR			// open for writing (Delete old files)
}FILEOpen_TypeDef;


/* Global Functions ***********************************************************/
void fatfs_init(void);
FATFSError_TypeDef fatfs_checkMedia(MEDIA_TypeDef media);
FATFSError_TypeDef fatfs_mount(MEDIA_TypeDef media);
FATFSError_TypeDef fatfs_unmount(MEDIA_TypeDef media);
FATFSError_TypeDef fatfs_openFile(FIL* fp, const char* filename, FILEOpen_TypeDef mode);
FATFSError_TypeDef fatfs_closeFile(FIL* fp);
FATFSError_TypeDef fatfs_writeString(FIL* fp, const char* text);









#endif // __STM32F10X_FATFS_H
