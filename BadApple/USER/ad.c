#include "ad.h"

#define ADC1_DR_Address (u32)(0x40012400+0x4c)     
u16 ADCConvertedValue[MAX_AD]={0};
u16 AD_Value[MAX_AD] = {0};

void DMA_ADC1_Init(void)
{
		ADC_InitTypeDef ADC_InitStructure;
	  DMA_InitTypeDef DMA_InitStructure;
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	  DMA_DeInit(DMA1_Channel1);
	  DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address;
	  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&ADCConvertedValue;
	  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	  DMA_InitStructure.DMA_BufferSize = 1;         
	  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable ;
	  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	  DMA_Init(DMA1_Channel1, &DMA_InitStructure);
	  DMA_Cmd(DMA1_Channel1, ENABLE);
	  ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	  ADC_InitStructure.ADC_ScanConvMode = ENABLE;
	  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	  ADC_InitStructure.ADC_NbrOfChannel = 1;
	  ADC_Init(ADC1, &ADC_InitStructure);
	  ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_239Cycles5);   //A0
	   //ADC_RegularChannelConfig(ADC1,ADC_Channel_2, 2, ADC_SampleTime_239Cycles5);   //A2
	  ADC_DMACmd(ADC1, ENABLE);              
	  ADC_Cmd(ADC1, ENABLE);            
	  ADC_ResetCalibration(ADC1);
	  while(ADC_GetResetCalibrationStatus(ADC1));
	  ADC_StartCalibration(ADC1);
	  while(ADC_GetCalibrationStatus(ADC1));
	  ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}


void ADCdeal(void)  
{
		static MovingAverageFilter_Type OLEDKeyADFilter = {MyMAFilter,8};
		AD_Value[0] = OLEDKeyADFilter.Filter(&OLEDKeyADFilter,ADCConvertedValue[0]) >> 2;
		//����ƽ���˲� ��12λAD���10λ
   
}

