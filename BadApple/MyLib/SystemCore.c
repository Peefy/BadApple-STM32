
#include "SystemCore.h"
            
uint16 MyLocationPID(PID_Type *This ,uint16 now , uint16 set)
{ 
    This->Real_P = This->HMI_P * This->ReductionFactor_P;
    This->Real_I = This->HMI_I * This->ReductionFactor_I;
    This->Real_D = This->HMI_D * This->ReductionFactor_D;
    This->Now = now;				  
		This->Set = set;
    This->Error = This->Set - This->Now;
		This->ErrorSum += This->Error;
		if(This->ErrorSum >= This->ErrorIMax) This->ErrorSum = This->ErrorIMax;
		if(This->ErrorSum <= This->ErrorIMin) This->ErrorSum = This->ErrorIMin;
    This->Out = This->Real_P * This->Error 
              + This->Real_I * This->ErrorSum
              + This->Real_D * (This->Error - This->LastError);
    This->PrevError = This->LastError;
    This->LastError = This->Error;
    This->Delta = This->Out;
		if(This->Delta >= This->DeltaMax) This->Delta = This->DeltaMax;
		if(This->Delta <= This->DeltaMin) This->Delta = This->DeltaMin;
		return This->Delta;
}

uint16 MyDeltaPID(PID_Type *This ,uint16 now , uint16 set)
{ 
    This->Real_P = This->HMI_P * This->ReductionFactor_P;
    This->Real_I = This->HMI_I * This->ReductionFactor_I;
    This->Real_D = This->HMI_D * This->ReductionFactor_D;
    This->Now = now;				  
		This->Set = set;
    This->Error = This->Set - This->Now;
    This->Out = This->Real_P * (This->Error - This->LastError)
              + This->Real_I * This->Error
              + This->Real_D * (This->Error - 2 * This->LastError + This->PrevError);
    This->PrevError = This->LastError;
    This->LastError = This->Error;
    This->Delta += This->Out;
		if(This->Delta >= This->DeltaMax) This->Delta = This->DeltaMax;
		if(This->Delta <= This->DeltaMin) This->Delta = This->DeltaMin;
		return This->Delta;
}

MovingAverageFilter_Type NewMAFilter(unsigned char filterLevel)
{
		MovingAverageFilter_Type maFilter;
		maFilter.Filter = MyMAFilter ;
		maFilter.FilterLevel = filterLevel;
		memset(maFilter.DataHistory, 0, DataNum * sizeof(float));
		maFilter.DataTotal = 0;
		maFilter.Now = 0;
		maFilter.Rear = 0;
		return maFilter;
}

uint16 MyMAFilter(MovingAverageFilter_Type* This,uint16 InputData)
{
		uint8 Index_Temp = 0;
		This->FilterLevel = (unsigned char)RANGE(This->FilterLevel,1,DataNum);  
		This->DataTotal = 0;
		This->Now = InputData;
		This->DataHistory[This->Rear] = This->Now;
		if(++This->Rear >= This->FilterLevel) This->Rear = 0;
		for(Index_Temp = 0;Index_Temp < This->FilterLevel ; ++Index_Temp)	
		{
				This->DataTotal += This->DataHistory[Index_Temp];
		}
		return This->DataTotal / This->FilterLevel;
		
}

float MySISOKalmanFilter(SISOKalmanFilter_Type* This,float Measure)
{
    float Temp1,Temp2;   
    //arm_sqrt_f32(1.0/(This->EstimateCovariance*This->EstimateCovariance
    //                  +This->MeasureCovariance*This->MeasureCovariance),&Temp1);
	  Temp1 = sqrtf(1.0/(This->EstimateCovariance*This->EstimateCovariance
                      +This->MeasureCovariance*This->MeasureCovariance));
    This->KalmanGain=Temp1*This->EstimateCovariance;
    if (This->KalmanGain <This->Kalman_MIN)
        This->KalmanGain =This->Kalman_MIN;
    This->EstimateValue=This->EstimateValue+
                            This->KalmanGain*(Measure-This->EstimateValue);
    //arm_sqrt_f32(1-This->KalmanGain,&Temp2);
		Temp2 = sqrtf(1-This->KalmanGain);
    This->EstimateCovariance=Temp2*This->EstimateCovariance;
    if (This->EstimateCovariance<This->Kalman_MIN)
        This->EstimateCovariance =This->Kalman_MIN;
    This->MeasureCovariance=Temp2*This->MeasureCovariance;
    if(This->MeasureCovariance<This->Kalman_MIN)
       This->MeasureCovariance=This->Kalman_MIN;
    return This->EstimateValue; 
}

unsigned char ByteFindMax(unsigned char num1,unsigned char num2,unsigned char num3,unsigned char num4)
{
	unsigned char max;
	unsigned char temp;
	temp = num1>num2?num1:num2;
	temp = temp>num3?temp:num3;
	max  = temp>num4?temp:num4;
	return max;
}

