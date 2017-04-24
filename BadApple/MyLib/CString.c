#include "CString.h"

#ifdef USE_STRING_STRUCT

CString_t Str = {
	IntToString,
	IntToHexString,
	FloatToString,
	BoolToString,
	CStringLenth,
	CStringConnact,
	CStringConnact3,
	CStringCatInt,
	CStringLetterCount,
	CStringSubStringIndex,
	CStringSubStringLastIndex,
	CStringInsertRange,
	CStringRemoveRange,
	CStringReserse,
	CStringReplaceSubString,
	CStringContainsSubString,
	CStringToUpper,
	CStringToLower,
};

#endif
	
char _STRtemp[STRING_WIDTH] = ""; 
//def Table
char _cstring[STRING_TABLE_NUM][STRING_WIDTH];
char ii = 0;

#define TableHeightRenew if( ii >= STRING_TABLE_NUM) ii = 0;

void Int16ToString(char *origin, int val)
{		
	char string[5] = "";
		int i;
		origin = "";
		sprintf(string,"%5d",val);
		for( i= 0;i<5;++i)
			*origin++ = string[i];
}

char* IntToString(int val)
{
		#define BIT_NUM 10
		char string[BIT_NUM] = "";
		int i ;
			TableHeightRenew;memset(_cstring[ii],'\0',STRING_WIDTH);
		sprintf(string,"%10d",val);
		for(i= 0;i<BIT_NUM ;++i)
			_cstring[ii][i] = string[i];
		CStringAlignToLeft(_cstring[ii]);
	#undef BIT_NUM
	
		return _cstring[ii++];
}

char* IntToHexString(unsigned char val)
{
		const char string[] = "0123456789ABCDEF";
		TableHeightRenew;memset(_cstring[ii],'\0',STRING_WIDTH);
		_cstring[ii][1] = string[(val & 0x0f)];
		_cstring[ii][0] = string[((val >> 4) & 0x0f)];
		CStringAlignToLeft(_cstring[ii]);

	
		return _cstring[ii++];
}

void FloatToString2(char * origin , float val)
{
		sprintf(origin,"%8.2f",val);
}

char * FloatToString(float val)
{
		#define FLOAT_BIT_NUM 8
		#define FLOAT_AfterPoint_NUM 2
		int i;
		char string[FLOAT_BIT_NUM] = "";
		TableHeightRenew;memset(_cstring[ii],'\0',STRING_WIDTH);
		sprintf(string,"%8.2f",val);
		for(i= 0;i<FLOAT_BIT_NUM;++i)
			_cstring[ii][i] = string[i];
		#undef FLOAT_BIT_NUM
		#undef FLOAT_AfterPoint_NUM
		
		CStringAlignToLeft(_cstring[ii]);
		return _cstring[ii++];
	
}

char* BoolToString(bool val)
{
		char i;
		const char TureOrFalseText[2][6] = {"false","true"};
		if(val <= 0 ) val = 0; if(val >= 1) val = 1;
		TableHeightRenew;memset(_cstring[ii],'\0',STRING_WIDTH);
		for(i= 0;i<6;++i)
			_cstring[ii][i] = TureOrFalseText[val][i];
		return _cstring[ii++];
}

void StringToint(char * str,int *out)  //可用atoi函数代替
{
		int i = 0;
		int temp = CStringLenth(str);		
		*out = 0;
		for(i = 0;i<temp;++i)
		{
			if(str[i] < '0' && str[i] > '9')
			{
					*out = -1;
					return;
			}
			*out += *out *9+(str[i] - '0');
		}
}

int StringToInt(char * str)
{
		int returnVal = 0;
		StringToint(str,&returnVal);
		return returnVal;
}

bool StringTofloat(float * out,char * str)//可用atof代替
{
		int i = 0;
		int lenth = CStringLenth(str);
	  int index = CStringLetterFirstIndexOf(str,'.');
		float PointAfter = 0;
		*out = 0;
	  if(index == -1)
		{
			for(i = 0;i<lenth;++i)
			{
				if(str[i] < '0' && str[i] > '9')
				{
					*out = -1;
					return false;
				}		
				*out += *out *9+(str[i] - '0');
			}
			return true;
		}
		else
		{
			for(i = 0;i<index;++i)
			{
				if(str[i] < '0' && str[i] > '9')
				{
					*out = -1;
					return false;
				}		
				*out += *out *9+(str[i] - '0');
			}
			for( i = 0;i < lenth - 1 - index;++i)
			{
				if(str[i] < '0' && str[i] > '9')
				{
					*out = -1;
					return false;
				}		
				PointAfter = PointAfter * 0.1 + (str[lenth  - 1- i] - '0') * 0.1;
			}				
			*out = (*out) + PointAfter ;
			return true;
		}
}

float StringToFloat(char * str) //可用atof代替
{
		float returnVal = 0;
		StringTofloat(&returnVal,str);
		return returnVal;
}

int CStringLenth(char * string)
{
	char * origin = string;
	while(*string)
    string++;
	return string - origin;
}

void CStringAlignToLeft(char * str)
{
		int i;		
		char * origin = str;
		int lenth = CStringLenth(str);
		int indexTemp = CStringLetterLastIndexOf(str,' ') + 1;

		if(indexTemp == 0) {str = origin ; return;}
		for(i = 0;*(str + i + indexTemp) != '\0';++i)
		{	
				*(str + i) = *(str + i + indexTemp);
		}
		for(;i < lenth;++i)
		{
				*(str + i) = '\0';
		}
}

char *CStringCatInt(char *target,int val)
{	
			char string[10] = "";	
	int lenth_t  = CStringLenth(target);
		int i ;
			TableHeightRenew;memset(_STRtemp,'\0',STRING_WIDTH);
		sprintf(string,"%10d",val);
		for(i= 0;i<10;++i)
			_STRtemp[i] = string[i];
		CStringAlignToLeft(_STRtemp);
		
	memset(_cstring[ii],'\0',STRING_WIDTH);	
	for(i = 0;i<lenth_t;++i)
		_cstring[ii][i] = target[i];
	strcat(_cstring[ii],_STRtemp);
	
	return _cstring[ii++];
}

char *CStringConnact(char *target,char * source)
{	
	int lenth_t  = CStringLenth(target);
	int lenth_s  = CStringLenth(source);
	int i ;
	TableHeightRenew;	memset(_STRtemp,'\0',STRING_WIDTH);
	for(i = 0;i<lenth_s;++i)
		_STRtemp[i] = source[i];
	
	memset(_cstring[ii],'\0',STRING_WIDTH);	
	for(i = 0;i<lenth_t;++i)
		_cstring[ii][i] = target[i];
	strcat(_cstring[ii],source);
	

	return _cstring[ii++];
}

char *CStringConnact3(char *target,char * source,char* three)
{	
	int lenth_t  = CStringLenth(target);
	int lenth_s  = CStringLenth(source);
	int i ;
	TableHeightRenew;	memset(_STRtemp,'\0',STRING_WIDTH);
	for(i = 0;i<lenth_s;++i)
		_STRtemp[i] = source[i];
	
	memset(_cstring[ii],'\0',STRING_WIDTH);	
	for(i = 0;i<lenth_t;++i)
		_cstring[ii][i] = target[i];
	strcat(_cstring[ii],source);
	strcat(_cstring[ii],three);
	return _cstring[ii++];
}

void CStringAppend(char *target,char * source)
{	
	strcat(target,source);
}

int CStringLetterFirstIndexOf( char*string, char letter)
{
   char *original=string;
	 int lenth = CStringLenth(string);
	 int returnVal;
   while((*string!=letter)&&(*string))
   string++;
	 returnVal = string-original;
	 if(returnVal >= lenth) returnVal = -1;
   return (returnVal);
}

int CStringLetterLastIndexOf(char *string,char letter)
{
   char *original=string;
   char *ptr=NULL;
	 int returnVal;
   while(*string)
   {
      if(*string==letter)
         ptr=string;
      string++;
   }
	 returnVal = ((ptr == NULL)?(-1):(ptr-original));
	 if(returnVal <= -1) returnVal = -1;
   return returnVal;
}

char *CStringAfterLetterFisrt(char *string, char letter)
{
	 int lenth = CStringLenth(string);
		unsigned char i=0;
	 int index = CStringLetterFirstIndexOf(string,letter);
		TableHeightRenew;	 memset(_cstring[ii],'\0',STRING_WIDTH);
	 for(;i<lenth;++i)
		_cstring[ii][i] = string[i];
		for(i= 0;i<index;++i)
			_cstring[ii][i] = ' ';
		CStringAlignToLeft(_cstring[ii]);
	

	 return _cstring[ii++];
}

char *CStringAfterLetterLast( char *string, char letter)
{
	 int lenth = CStringLenth(string);
		unsigned char i=0;
	 int index = CStringLetterLastIndexOf(string,letter);
		TableHeightRenew;	 memset(_cstring[ii],'\0',STRING_WIDTH);
	 for(;i<lenth;++i)
		_cstring[ii][i] = string[i];
		for(i= 0;i<index;++i)
			_cstring[ii][i] = ' ';
		CStringAlignToLeft(_cstring[ii]);
	
	 return _cstring[ii++];

}

int CStringSubStringIndex( char *s1, char *s2)
{
    int  i,j,k;
    for(i=0; s1[i]; i++)
         for(j=i,k=0; s1[j]==s2[k]; j++,k++)
                 if(!s2[k+1])
                       return i;
    return(-1);
}

int CStringSubStringLastIndex( char *s1, char *s2)
{
		int lenth_str = CStringLenth(s1);
		int lenth_find = CStringLenth(s2);
    int  i,j,k;
		int returnIndex = -1;
    for(i = 0;i<= (lenth_str - lenth_find);++i)
		{
				 for(j=i,k=0; s1[j]==s2[k]; j++,k++)
				 {
              if(!s2[k+1])
							{
								returnIndex = i;
								break;
							}
				 }
		}
    return returnIndex;
}

int CStringLetterCount(const char *string,char letter)
{
    int count=0;
    while(*string)
    if(*string++ ==letter)
       count++;
    return(count);
}

bool CStringContainsLetter( char *string,char letter)
{
	  return CStringLetterCount(string,letter)>0?true:false;
}

char * CStringSubString( char *s1, char *s2)
{
    int  i,j,k;
    for(i=0; s1[i]; i++)
         for(j=i,k=0; s1[j]==s2[k]; j++,k++)
                 if(!s2[k+1])
                       return(s1+i);
    return(NULL);
}



bool CStringContainsSubString(char *s1,char *s2)
{
    return CStringSubString(s1,s2) == NULL?false:true;
}

char* CStringReserse(char *string)
{
		int lenth = CStringLenth(string);
		int i;
		TableHeightRenew;		memset(_cstring[ii],'\0',lenth);
		for(i = 0;i<lenth;++i)
			_cstring[ii][i] = string[lenth - i - 1];
	

		return _cstring[ii++];
}

int CStringCompare(const char *s1, const char *s2)
{
    return strcmp(s1,s2);

}

char * CStringRemoveAt(char *str,int index)
{
	  int  i;
		int lenth = CStringLenth(str);
		index = ((index)<(0) ? (0) : ( (index)>(lenth -1) ? (lenth - 1):(index) ));
			TableHeightRenew;memset(_cstring[ii],'\0',STRING_WIDTH);
		for(i=0;i<lenth;++i)
			_cstring[ii][i] = str[i];
		_cstring[ii][index] = '\0';
		memset(_STRtemp,'\0',STRING_WIDTH);
		for(i = index + 1;i<lenth;++i)
			_STRtemp[i - index - 1] = _cstring[ii][i];
		strcat(_cstring[ii],_STRtemp);
	

		return _cstring[ii++];
}

char * CStringInsert(char *str,int index,char letter)
{
		int  i;
		int lenth = CStringLenth(str);
		index = ((index)<(0) ? (0) : ( (index)>(lenth ) ? (lenth):(index) ));
		TableHeightRenew;memset(_cstring[ii],'\0',STRING_WIDTH);
		for(i=0;i<lenth;++i)
			_cstring[ii][i] = str[i];
		
		for(i = lenth;i > index;--i)
			_cstring[ii][i] = _cstring[ii][i - 1];
		_cstring[ii][index] = letter;
	
		return _cstring[ii++];
}

char * CStringInsertRange(char *str,int index,char* letters)
{
		int  i;
		int lenth = CStringLenth(str);
		int lenth_s =  CStringLenth(letters);
		index = ((index)<(0) ? (0) : ( (index)>(lenth ) ? (lenth):(index) ));
		TableHeightRenew;memset(_cstring[ii],'\0',STRING_WIDTH);
		for(i=0;i<lenth;++i)
			_cstring[ii][i] = str[i];	
		
		for(i = lenth + lenth_s -1;i >= index+lenth_s ;--i)
			_cstring[ii][i] = _cstring[ii][i - lenth_s - 1];
		
		for(i = 0 ;i< lenth_s;++i)
			_cstring[ii][index + i] = letters[i];
	
		return _cstring[ii++];
}

char * CStringRemoveRange(char *str,int startindex,int endindex)
{
	  int  i;
		int lenth = CStringLenth(str);
		startindex = ((startindex)<(0) ? (0) : ( (startindex)>(lenth -1) ? (lenth - 1):(startindex) ));
		endindex = ((endindex)<(0) ? (0) : ( (endindex)>(lenth -1) ? (lenth - 1):(endindex) ));
			TableHeightRenew;
	memset(_cstring[ii],'\0',STRING_WIDTH);
		for(i=0;i<lenth;++i)
			_cstring[ii][i] = str[i];
		if(startindex >endindex)
		{				
			return _cstring[ii++];
		}
		for(i = startindex;i<=endindex;++i)
			_cstring[ii][i] = '\0';
		memset(_STRtemp,'\0',STRING_WIDTH);
		for(i = endindex + 1;i<lenth;++i)
			_STRtemp[i - endindex - 1] = _cstring[ii][i];
		strcat(_cstring[ii],_STRtemp);
		

		return _cstring[ii++];
}


char * CStringRemoveSubString(char *str, char *substring)//
{
    int  i;
		int lenth = CStringLenth(str);
		int lenth_sub = CStringLenth(substring);
		TableHeightRenew;
		memset(_cstring[ii],'\0',STRING_WIDTH);	
		for(i=0;i<lenth;++i)
			_cstring[ii][i] = str[i];
		if(CStringContainsSubString(str,substring) == false)		
		{		
			return(_cstring[ii++]);
		}
		else
		{	
			while(CStringSubStringIndex(_cstring[ii],substring) != -1)
			{
				int index_ =CStringSubStringIndex(_cstring[ii],substring);
			for(i = 0;i<lenth_sub;++i)
				_cstring[ii][i + index_] = '\0';
			memset(_STRtemp,'\0',STRING_WIDTH);
			for(i = index_ + lenth_sub;i<lenth;++i)
				_STRtemp[i - index_ - lenth_sub] =_cstring[ii][i];
			strcat(_cstring[ii],_STRtemp);
			}
		}
		
		return _cstring[ii++];
}

char *CStringReplaceSubString(char *str, char *substring,char *news)//
{
    int  i;
		int count = 0;
		int lenth = CStringLenth(str);
		int lenth_sub = CStringLenth(substring);
		int lenth_new = CStringLenth(news);
		int index_sub;
		TableHeightRenew;
		memset(_cstring[ii],'\0',STRING_WIDTH);	
		for(i=0;i<lenth;++i)
			_cstring[ii][i] = str[i];
		if(CStringContainsSubString(str,substring) == false)		
		{			
			return(_cstring[ii++]);
		}
		else
		{	
			while(CStringSubStringIndex(_cstring[ii],substring) != -1)
			{
				++count;
				index_sub =CStringSubStringIndex(_cstring[ii],substring);
			for(i = 0;i<lenth_sub;++i)
				_cstring[ii][i + index_sub] = '\0';
			memset(_STRtemp,'\0',STRING_WIDTH);
			for(i = index_sub + lenth_sub;i<lenth + count;++i)
				_STRtemp[i - index_sub - lenth_sub] =_cstring[ii][i];
			strcat(_cstring[ii],_STRtemp);
				
			for(i = lenth -lenth_sub * count + count *lenth_new -1 ;i >= index_sub+lenth_new ;--i)
				_cstring[ii][i] = _cstring[ii][i - lenth_new];
		
			for(i = 0 ;i< lenth_new;++i)
				_cstring[ii][index_sub + i] = news[i];			
				
			}
		}
	
		return _cstring[ii++];
				
} 

char *CStringToUpper(char *string)//
{
		int  i;
	  int lenth = CStringLenth(string);	
	TableHeightRenew;
	
		memset(_cstring[ii],'\0',STRING_WIDTH);
    for(i=0; i<lenth; i++)
		{
				_cstring[ii][i] = string[i];
				if(_cstring[ii][i]>= 'a' && _cstring[ii][i]<= 'z')
					_cstring[ii][i] -= ('a'-'A');
		}
		
	
		return _cstring[ii++];
} 

char *CStringToLower(char *string) //
{
		int  i;
	  int lenth = CStringLenth(string);
	
		TableHeightRenew;
	
		memset(_cstring[ii],'\0',STRING_WIDTH);
    for(i=0; i<lenth; i++)
		{
						_cstring[ii][i] = string[i];
				if(_cstring[ii][i]>= 'A' && _cstring[ii][i]<= 'Z')
					_cstring[ii][i] += ('a'-'A');
		}
		
		
		return _cstring[ii++];
} 
