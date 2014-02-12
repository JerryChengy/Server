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

	static size_t ToPrime(const int Value);
	static float CarmSqrt(float x); //结果有误差，谨慎使用
	//一个方便的 hash 函数应该散列的比较开，计算速度跟字符串长度关系不大，又不能只计算字符串的开头或末尾。
	//这里的算法是从 Lua 中看来的。
	static unsigned long hash(const char *name,size_t len);
protected:
private:
};


#endif