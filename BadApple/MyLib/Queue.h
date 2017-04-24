#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "include.h"

/**
  ******************************************************************************
  * @file    Queue.c
  * @author  DuGu
  * @version V1.0.5
  * @date    10/06/2016
  * @brief   C Queue -- malloc from RAM/Flash;
						 The following functions on a 32-bit machine
  ******************************************************************************
**/

#include <stdio.h>
#include <stdlib.h>

#define QueueType unsigned char  

#define HaveBool 1

typedef struct
{
    QueueType buffer;
    char data[];
}MyType;  

typedef struct
{
   MyType* qBase;   
   QueueType FrontData; //队头元素
   int Rear;            //队尾指针
   unsigned int Size;   //队列空间大小
   unsigned int Count;  //队列元素个数
}Queue;    

extern Queue* Queue_Byte;

#ifdef HaveBool

#include <stdbool.h>

bool CreateQueue(Queue *pQueue,unsigned int size);
bool InitQueue(Queue *pQueue);
bool IsEmpty(Queue *pQueue);
bool Peek(Queue *pQueue,QueueType *pe);

#else

#define BOOL int
#define TRUE 1
#define FALSE 0

BOOL CreateQueue(Queue *pQueue,unsigned int size);
BOOL InitQueue(Queue *pQueue);
BOOL IsEmpty(Queue *pQueue);
BOOL Peek(Queue *pQueue,QueueType *pe);

#endif

void ClearQueue( Queue *pQueue );
unsigned int GetCount( Queue *pQueue );
unsigned int GetSize(Queue *pQueue);
int IndexOf(Queue *pQueue,QueueType value);
QueueType ValueAt(Queue *pQueue,unsigned int index);
int GetHead(Queue *pQueue);
int EnQueue(Queue *pQueue , QueueType value);
int DeQueue( Queue *pQueue, QueueType *pe );
QueueType GetInQueue(Queue *pQueue);
void Queue_ForEach( Queue *pQueue, void (*func)(QueueType *pe) );

#endif
