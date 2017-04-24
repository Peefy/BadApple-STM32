#ifndef _UART_H_
#define _UART_H_

#include <stdio.h>

#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_usart.h" 
#include "misc.h" 


#define UART1_Tx GPIO_Pin_9
#define UART1_Rx GPIO_Pin_10
#define UART1_GPIO GPIOA

#define UART2_Tx GPIO_Pin_2
#define UART2_Rx GPIO_Pin_3
#define UART2_GPIO GPIOA

void Pose_UARTSendbyte(unsigned char );
void SC_UARTSendbyte(unsigned char );
void USART1_Init(void);
void USART2_Init(void);
void NVIC_Configuration(void);
int fputc(int ch, FILE *f);
int fgetc(FILE *f);
void ClearRecieveCount(void);

#endif
