#ifndef CW_ASSERT_H
#define CW_ASSERT_H
#include "cw_commondefine.h"

void AssertShowEx(char* file, int line, char* func, char* expr, char* format, ...);
void AssertShow(char* file, int line, char* func, char* expr);


#define Assert(expr) {if(!(expr)) AssertShow(__FILE__, __LINE__, __FUNCTION__, #expr);}
#define AssertEx(expr, szFormat, ...) {if (!(expr)) AssertShowEx(__FILE__, __LINE__, __FUNCTION__, #expr, szFormat, __VA_ARGS__);}

#endif
