#include "cw_commondefine.h"
#include "cw_assert.h"
#include "cw_const.h"

void AssertShowEx(char* file, int line, char* func, char* expr, char* format, ...)
{
	va_list Args;
	va_start(Args, format);
	char szBuf1[BUFF_LEN_512]="";
	char szBuf2[BUFF_LEN_512]="";	
	_snprintf_s(szBuf1, BUFF_LEN_512, "[FILE:%s] [LINE:%d] [Func:%s] [expr:%s].\n", file, line, func, expr);
	_vsnprintf_s(szBuf2, BUFF_LEN_512, format, Args);
	char szBuf[BUFF_LEN_1024]="";
	_snprintf_s(szBuf, BUFF_LEN_1024, "%s%s", szBuf1, szBuf2);
	va_end(Args);
	::MessageBoxA(NULL, szBuf, "FileReader", MB_OK);
	throw 1;
}

void AssertShow(char* file, int line, char* func, char* expr)
{
	if (!file || !func || !expr)
	{
		return ;
	}
	char szBuf[BUFF_LEN_512]="";
	_snprintf_s(szBuf, BUFF_LEN_512, "[FILE:%s] [LINE:%d] [Func:%s] [expr:%s].\n", file, line, func, expr);	
	::MessageBoxA(NULL, szBuf, "FileReader", MB_OK);
	throw 1;
}