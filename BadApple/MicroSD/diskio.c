/****************************************Copyright (c)****************************************************
**
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               diskio.c
** Descriptions:            The FATFS Diskio
**
**--------------------------------------------------------------------------------------------------------
** Created by:              AVRman
** Created date:            2010-11-4
** Version:                 v1.0
** Descriptions:            The original version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Version:
** Descriptions:
**
*********************************************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "diskio.h"


/* Private variables ---------------------------------------------------------*/
extern MSD_CARDINFO CardInfo;


DSTATUS disk_initialize (
	BYTE drv				/* Physical drive nmuber (0..) */
)
{
 int Status;

 switch (drv)
 {
	case 0 :

    Status = MSD_Init();
    if(Status == 0)
	  return 0;
    else
	  return STA_NOINIT;

	case 1 :
		return STA_NOINIT;

	case 2 :
		return STA_NOINIT;
  }
	return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Return Disk Status                                                    */

DSTATUS disk_status (
	BYTE drv		/* Physical drive nmuber (0..) */
)
{
    switch (drv)
	{
	  case 0 :

	  /* translate the reslut code here	*/

	    return 0;

	  case 1 :

	  /* translate the reslut code here	*/

	    return 0;

	  case 2 :

	  /* translate the reslut code here	*/

	    return 0;

	  default:

        break;
	}
	return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */

DRESULT disk_read (
	BYTE drv,		/* Physical drive number (0..) */
	BYTE *buff,		/* Data buffer to store read data */
	DWORD sector,	/* Sector address (LBA) */
	BYTE count		/* Number of sectors to read (1..255) */
)
{
  int Status;
  if( !count )
  {
    return RES_PARERR;  /* countä¸�èƒ½ç­‰äºŽ0ï¼Œå�¦åˆ™è¿”å›žå�‚æ•°é”™è¯¯ */
  }

  switch (drv)
  {

    case 0:
    if(count==1)            /* 1ä¸ªsectorçš„è¯»æ“�ä½œ */
    {
	  Status =  MSD_ReadSingleBlock( sector ,buff );
    }
    else                    /* å¤šä¸ªsectorçš„è¯»æ“�ä½œ */
    {
      Status = MSD_ReadMultiBlock( sector , buff ,count);
    }
    if(Status == 0)
    {
      return RES_OK;
    }
    else
    {
      return RES_ERROR;
    }

	case 1:
	  break;

    case 2:
	  break;

    default:
      break;

  }

  return RES_ERROR;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */

#if _READONLY == 0
DRESULT disk_write (
	BYTE drv,			/* Physical drive nmuber (0..) */
	const BYTE *buff,	        /* Data to be written */
	DWORD sector,		/* Sector address (LBA) */
	BYTE count			/* Number of sectors to write (1..255) */
)
{
  int Status;
  if( !count )
  {
    return RES_PARERR;  /* countä¸�èƒ½ç­‰äºŽ0ï¼Œå�¦åˆ™è¿”å›žå�‚æ•°é”™è¯¯ */
  }

  switch (drv)
  {
    case 0:
    if(count==1)            /* 1ä¸ªsectorçš„å†™æ“�ä½œ */
    {
       Status = MSD_WriteSingleBlock( sector , (uint8_t *)(&buff[0]) );
    }
    else                    /* å¤šä¸ªsectorçš„å†™æ“�ä½œ */
    {
       Status = MSD_WriteMultiBlock( sector , (uint8_t *)(&buff[0]) , count );
    }
    if(Status == 0)
    {
       return RES_OK;
    }
    else
    {
       return RES_ERROR;
    }
    case 2:
	   break;
    default :
       break;
  }
 return RES_ERROR;
}
#endif /* _READONLY */



/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */

DRESULT disk_ioctl (
	BYTE drv,		/* Physical drive nmuber (0..) */
	BYTE ctrl,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
    if (drv)
    {
        return RES_PARERR;  /* ä»…æ”¯æŒ�å�•ç£�ç›˜æ“�ä½œï¼Œå�¦åˆ™è¿”å›žå�‚æ•°é”™è¯¯ */
    }

	MSD_GetCardInfo(&CardInfo);

	switch (ctrl)
	{
	  case CTRL_SYNC :

		return RES_OK;

	  case GET_SECTOR_COUNT :
	    *(DWORD*)buff = CardInfo.Capacity/CardInfo.BlockSize;
	    return RES_OK;

	  case GET_BLOCK_SIZE :
	    *(WORD*)buff = CardInfo.BlockSize;
	    return RES_OK;

	  case CTRL_POWER :
		break;

	  case CTRL_LOCK :
		break;

	  case CTRL_EJECT :
		break;

      /* MMC/SDC command */
	  case MMC_GET_TYPE :
		break;

	  case MMC_GET_CSD :
		break;

	  case MMC_GET_CID :
		break;

	  case MMC_GET_OCR :
		break;

	  case MMC_GET_SDSTAT :
		break;
	}
	return RES_PARERR;
}

/* å¾—åˆ°æ–‡ä»¶Calendaræ ¼å¼�çš„å»ºç«‹æ—¥æœŸ,æ˜¯DWORD get_fattime (void) é€†å�˜æ�¢ */
/*-----------------------------------------------------------------------*/
/* User defined function to give a current time to fatfs module          */
/* 31-25: Year(0-127 org.1980), 24-21: Month(1-12), 20-16: Day(1-31) */
/* 15-11: Hour(0-23), 10-5: Minute(0-59), 4-0: Second(0-29 *2) */
DWORD get_fattime (void)
{

    return 0;
}



/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
