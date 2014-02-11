#ifndef CW_TOOLS_H
#define CW_TOOLS_H
#include "cw_commondefine.h"

class CTools
{
public:
	static void Strcpy(char* pDes, const char* pSrc, int iLen);

	static int  Strlen(const char* pStr);

	static bool StringToInt(const char*  pBuf, int &nRes);

	static bool StringToFloat(const char* pBuf, float &fRes);

	static bool SplitString(const char* pSrc, MUL_STRING& vecRes, char splitChar);

	static bool SplitString(const char* pSrc, MUL_INT& vecRes, char splitChar);

	static bool IsEqualString(const char* pStr1, const char* pStr2);
protected:
private:
};


#endif