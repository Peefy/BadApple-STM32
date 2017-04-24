#ifndef _IWDG_H_
#define _IWDG_H_

//#define IWDG_EN 1

void IWDG_Init(void);
void IWDG_Reset(void);
void FeedDog(void);

#define _FeedDog IWDG_ReloadCounter()		
									  
#endif
