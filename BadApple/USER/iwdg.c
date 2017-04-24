
#include "stm32f10x_iwdg.h" 

void IWDG_Init(void)
{
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);

/* IWDG counter clock: 40KHz(LSI) / 32 = 1.25 KHz */

	IWDG_SetPrescaler(IWDG_Prescaler_32);
	IWDG_SetReload(899);
	IWDG_ReloadCounter();
	IWDG_Enable();
    
}

void FeedDog(void)
{
		#ifdef IWDG_EN			
		_FeedDog;             //Œπ∂¿¡¢ø¥√≈π∑
		#endif		
}

void IWDG_Reset(void)
{
		while(1);
}



