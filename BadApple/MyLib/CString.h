#ifndef _C_STRING_H_
#define _C_STRING_H_

#include <stdio.h>
#include <stdlib.h>
#include "stdbool.h"
#include "string.h"
/**
  ******************************************************************************
  * @file    CString.c
  * @author  DuGu
  * @version V1.7.6
  * @date    10/12/2016
  * @brief   Some Function About String
						 The following functions on a 32-bit machine	
  ******************************************************************************
**/

#define IS_UPPER(c)	    (((c)>='A')&&((c)<='Z'))
#define IS_LOWER(c)	    (((c)>='a')&&((c)<='z'))
#define IS_DIGITNUM(c)	(((c)>='0')&&((c)<='9'))

#define StrAdd      CStringConnact
#define StrAdd3     CStringConnact3
#define ItoA        IntToString
#define FtoA        FloatToString
#define StrLenth    CStringLenth
#define StrIndexOf  CStringLetterFirstIndexOf
#define StrIndexOfs CStringSubStringIndex

#define STRING_TABLE_NUM 5 //也是各个库函数可以互相嵌套的层数
#define STRING_WIDTH 16  	 //字符串的最大长度,包括'\0'

#define USE_STRING_STRUCT

#ifdef USE_STRING_STRUCT
typedef
struct
{
		char* (*Int2Str)(int); 
		char* (*Int2HexStr)(unsigned char);
		char* (*Float2Str)(float val);
		char* (*Bool2Str)(bool val);
		int (*Lenth)(char*);
		char* (*Add)(char *,char * );
		char* (*Add3)(char *,char *,char*);
		char* (*AddInt)(char *,int val);
		int (*CharCount)(const char* ,char);
		int (*IndexOf)( char *s1, char *s2);
		int (*LastIndexOf)(char *,char* );
		char* (*Insert)(char *,int index,char*);
		char* (*Remove)(char *str,int start,int end);
		char* (*Reserse)(char *);
		char* (*Replace)(char *, char * subs, char * news);
		bool (*Contain)(char *s1,char *s2);
		char* (*ToUpper)(char *); 
		char* (*ToLower)(char *); 
}CString_t;

extern CString_t Str;

#endif

void Int16ToString(char *oringin, int val);  //〇
char* IntToString(int val);                   //〇
char* IntToHexString(unsigned char val);   //〇
void FloatToString2(char * origin , float val);//〇
char * FloatToString(float val);//〇
char* BoolToString(bool val);
void StringToint(char * str,int *out);//〇
int StringToInt(char * str);//〇
bool StringTofloat(float * out,char * str);//〇
float StringToFloat(char * str);//〇

int CStringLenth(char * string);//〇
void CStringAlignToLeft(char * str);//〇

char *CStringCatInt(char *target,int val);
char *CStringConnact(char *target,char * source);//〇
char *CStringConnact3(char *target,char * source,char* three);//〇
void CStringAppend(char *target,char * source);//〇

int CStringLetterFirstIndexOf( char*string, char letter);//〇
int CStringLetterLastIndexOf(char *string,char letter);//〇
int CStringSubStringIndex( char *s1, char *s2);//〇
int CStringSubStringLastIndex( char *s1, char *s2);//〇

char *CStringAfterLetterFisrt(char *string, char letter);//〇
char *CStringAfterLetterLast( char *string, char letter);//〇

int CStringLetterCount(const char *string,char letter);//〇

bool CStringContainsLetter( char *string,char letter);//〇
bool CStringContainsSubString(char *s1,char *s2);//〇

char * CStringRemoveAt(char *str,int index); //〇
char * CStringInsert(char *str,int index,char letter);//〇
char * CStringInsertRange(char *str,int index,char* letters);//〇
char * CStringRemoveRange(char *str,int startindex,int endindex);//〇

char * CStringSubString( char *s1, char *s2);//〇

char* CStringReserse(char *string);//〇
int CStringCompare(const char *s1, const char *s2);//〇

char * CStringRemoveSubString(char *string, char *substring);//〇
char *CStringReplaceSubString(char *source, char *old , char *news);//〇

char *CStringToUpper(char *string); //〇
char *CStringToLower(char *string); //〇

#endif

