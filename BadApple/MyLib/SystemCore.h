#ifndef __SYSCORE_H
#define __SYSCORE_H 			   

/**
  ******************************************************************************
  * @file    SystemCore.c
  * @author  DuGu
  * @version V1.2.7
  * @date    10/09/2016
  * @brief   Some Function
						 The following functions on a 32-bit machine
  ******************************************************************************
**/

//#include "include.h"                     //My Include
//#include "arm_math.h"                    //CMSIS library
#include "math.h"                          //C Math Lib
#include "stdbool.h"                       //C bool Lib
#include "string.h"
    /* exact-width signed integer types */
typedef   char int8;
typedef   signed short     int int16;
typedef   signed           int int32;
//typedef   signed       __int64 int64;

    /* exact-width unsigned integer types */
typedef unsigned          char uint8;
typedef unsigned short     int uint16;
typedef unsigned           int uint32;
//typedef unsigned       __int64 uint64;

typedef volatile int8       vint8;  /*  8 bits */
typedef volatile int16      vint16; /* 16 bits */
typedef volatile int32      vint32; /* 32 bits */
//typedef volatile int64      vint64; /* 64 bits */

typedef volatile uint8      vuint8;  /*  8 bits */
typedef volatile uint16     vuint16; /* 16 bits */
typedef volatile uint32     vuint32; /* 32 bits */
//typedef volatile uint64     vuint64; /* 64 bits */

/* Sample usage:
BIT_CLEAN(0xff,0) = 0xfe 
BIT_SET(0x00,1) = 0x02
BIT_GET(0x55,0) = 1
BIT_GET(0x55,1) = 0
*/
#define BIT_CLEAN(var,n)        (var) &= ~(1<<(n))   
#define BIT_SET(var,n)          (var) |=  (1<<(n))   
#define BIT_GET(var,n)          (((var)>>(n))&0x01)  
#define BIT_SETval(var,n,val)   ( ((val) == (1)) ? BIT_SET(var,n) : BIT_CLEAN(var,n) )

/* Sample usage:
B8(01010101) = 85
B16(10101010,01010101) = 43605
B32(10000000,11111111,10101010,01010101) = 2164238933
*/
#define  HEX__(n)   0x##n##UL
#define  B8__(x)   ( (x & 0x0000000FUL) ? 1:0 )\
    +( (x & 0x000000F0UL) ? 2:0 )\
    +( (x & 0x00000F00UL) ? 4:0 )\
    +( (x & 0x0000F000UL) ? 8:0 )\
    +( (x & 0x000F0000UL) ? 16:0 )\
    +( (x & 0x00F00000UL) ? 32:0 )\
    +( (x & 0x0F000000UL) ? 64:0 )\
    +( (x & 0xF0000000UL) ? 128:0 )
#define  B8(x)                                     ((unsigned char)B8__(HEX__(x)))
#define  B16(x_msb,x_lsb)                (((unsigned int)B8(x_msb)<<8) + B8(x_lsb))
#define  B32(x_msb,x_2,x_3,x_lsb)   (((unsigned long)B8(x_msb)<<24) + ((unsigned long)B8(x_2)<<16) + ((unsigned long)B8(x_3)<<8) + B8(x_lsb))

/* Sample usage:
MAX( 1, 2 ) = 2
MIN( 1.1, 2.2 ) = 1.1
*/
#define MAX( x, y ) ( ((x) > (y)) ? (x) : (y) )
#define MIN( x, y ) ( ((x) < (y)) ? (x) : (y) )

/* Sample usage:
int a[4] = {0}; ARR_SIZE( a ) == 4;
*/
#define ARR_SIZE( a ) ( sizeof( (a) ) / sizeof( ((a)[0]) ) )

/* Sample usage:
ABS(-1.1) = 1.1
*/
#define ABS(x) (((x) > 0) ? (x) : (-x))

/* Sample usage:
OFFSET(PID_Type, HMI_D) 
*/
#define OFFSET(type, member)    (uint32)(&(((type *)0)->member))

/* Sample usage:
RANGE(23,-100,100) = 23
RANGE(112,-100,100) = 100
RANGE(-112,-100,100) = -100
UP_RANGE(101,100) = 100
DOWM_RANGE(-2,-1) = -1
*/
#define RANGE(x,min,max)        ((int16)((x)<(min) ? (min) : ( (x)>(max) ? (max):(x) )))
#define UP_RANGE(x,max)         ( (int16)( (x)>(max) ? (max):(x) ) ) 
#define DOWM_RANGE(x,min)				( (int16)( (x)<(min) ? (min):(x) ) )

/* Sample usage:
DEAD_ZONE(4,-2,2,0) = 4
DEAD_ZONE(1,-2,2,0) = 0
*/
#define DEAD_ZONE(x,min,max,deadval)        ((int16)((x)<(min) ? (x) : ( (x)>(max) ? (x):(deadval) )))

/* Sample usage:
SWAP32(0xfe34ab21) = 0x21ab34fe 
SWAP16(0xabcd) = 0xcdab
int a = 2,b=1; SWAP(a,b);  //a=1,b=2     
*/
#define SWAP32(data)    (uint32)((((uint32)(data) & (0xFFu<<0 ))<<24)      \
                          | (((uint32)(data) & (0xFFu<<8 ))<<8)            \
                          | (((uint32)(data) & (0xFFu<<16))>>8)            \
                          | (((uint32)(data) & (0xFFu<<24))>>24)           \
                        )

#define SWAP16(data)    (uint32)((((uint16)(data) & (0xFF<<0 ))<<8)      \
                          | (((uint32)(data) & (0xFF<<8))>>8)            \
                        )

#define SWAP(x,y)           do{x^=y;y^=x;x^=y;}while(0)

typedef 
struct
{
		int X;
		int Y;
}Point;

typedef 
struct
{
		int Width;
		int Height;
}Size;	

/********PID*******/
/* Sample usage:
  PID_Type MyPID = {1,1,0,1,1,1,100,-100,1000,-1000}
	MyDeltaPID(&MyPID ,e,10);
*/
typedef 
struct
{    
	//public:
    uint16 HMI_P;   
    uint16 HMI_I;
    uint16 HMI_D;
		const float ReductionFactor_P; 
		const float ReductionFactor_I;
		const float ReductionFactor_D;
		uint16 DeltaMax;     
		uint16 DeltaMin;
		float ErrorIMax;		
		float ErrorIMin;
	//private:    		
    float LastError;
    float PrevError;
    float Error;
		float ErrorSum;
		float Delta;
    float Real_P;
    float Real_I;
    float Real_D;   
    float Out;
    uint16 Now;
		uint16 Set; 
}PID_Type; //��ͨλ��ʽ������ʽPID����

/*********MovingAverageFilter*************/
/* Sample usage:
  MovingAverageFilter_Type ADfilter = {8}
	ADvalAfter = MyMAFilter(&ADfilter,ADvalBefore);
*/
#define DataNum 64
typedef 
struct MovingAverageFilter_Type
{
	//public:
		uint16 (*Filter)(struct MovingAverageFilter_Type* This,uint16 InputData);
		unsigned char FilterLevel;	
	//private:					
		float DataHistory[DataNum];		
		uint32 DataTotal;			
		uint16 Now;
		unsigned char Rear;
}MovingAverageFilter_Type;

/*************SISOKalmanFilter**************/
typedef 
struct
{
	//public:
		float KalmanGain;                
		float EstimateCovariance;       
		float MeasureCovariance;         
		float EstimateValue;      
		const float	Kalman_MIN;         
}SISOKalmanFilter_Type;

typedef struct bitS 
{ 
unsigned bit0:1;  
unsigned bit1:1;  
unsigned bit2:1;  
unsigned bit3:1;  
unsigned bit4:1;  
unsigned bit5:1;  
unsigned bit6:1;  
unsigned bit7:1;   
}pbitS; 

typedef union byteB 
{ 
struct bitS b; 
unsigned char c; 
}uByteB; 

#define TRUE    1
#define FALSE   0

uint16 MyLocationPID(PID_Type *This ,uint16 now , uint16 set);
uint16 MyDeltaPID(PID_Type *This ,uint16 now , uint16 set);
MovingAverageFilter_Type NewMAFilter(unsigned char filterLevel);
uint16 MyMAFilter(MovingAverageFilter_Type* This,uint16 InputData);
float MySISOKalmanFilter(SISOKalmanFilter_Type* This,float Measure);

unsigned char ByteFindMax(unsigned char num1,unsigned char num2,unsigned char num3,unsigned char num4);

#endif


