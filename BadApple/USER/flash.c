#include "include.h"

uint32 StartAddress = 0x0800f000;
volatile FLASH_Status FLASHStatus = FLASH_COMPLETE;

u32 Readflash(char i)
{
	uint32_t data;
	uint32_t *p = (uint32_t*)(StartAddress+i);
	data = *p;
	return data;
}

void Writeflash(void)
{
	FLASH_Unlock();
	FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR); 
    FLASHStatus = FLASH_ErasePage(StartAddress);
	if(FLASHStatus == FLASH_COMPLETE)
	{
		//FLASHStatus = FLASH_ProgramWord(StartAddress+ FlashOffSetAddr0, SerPD.Kp);
		//FLASHStatus = FLASH_ProgramWord(StartAddress+ FlashOffSetAddr1, SerPD.Kd);
		//FLASHStatus = FLASH_ProgramWord(StartAddress+ FlashOffSetAddr2, 0xE234567F);
		//FLASHStatus = FLASH_ProgramWord(StartAddress+ FlashOffSetAddr3, MotorPara.SpeedSelectConut);
	}
	//up_fmq();
}

void WriteFlashSerMid(void)
{
		FLASH_Unlock();
	FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR); 
    FLASHStatus = FLASH_ErasePage(StartAddress);
	if(FLASHStatus == FLASH_COMPLETE)
	{
		//FLASHStatus = FLASH_ProgramWord(StartAddress+ FlashOffSetAddr5, ChangeSerMidSeccessFlag);
		//FLASHStatus = FLASH_ProgramWord(StartAddress+ FlashOffSetAddr6, SerMid);
	
	}
	//up_fmq();
}

void WriteflashOn(int writeOffsetAddress,u32 writeData)
{
	FLASH_Unlock();
	FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR); 
    FLASHStatus = FLASH_ErasePage(StartAddress);
	if(FLASHStatus == FLASH_COMPLETE)
	{
		FLASHStatus = FLASH_ProgramWord(StartAddress+writeOffsetAddress, writeData);
	}
	//up_fmq();
}

void Read(void)
{
  //  SerPD.Kp = (uint16)Readflash(0);
	//SerPD.Kd = (uint16)Readflash(4);
	//MotorPara.SpeedSelectConut = (byte)Readflash(8);
	//MotorPara.SpeedSelectConut = (byte)Readflash(12);
	//up_fmq();
}


