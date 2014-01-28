#ifndef CW_TOOLS_H
#define CW_TOOLS_H


class CTools
{
public:
	static void Strcpy(char* pDes, const char* pSrc, int iLen);

	static int  Strlen(const char* pStr);

	static bool StringToInt(const char*  pBuf, int &nRes);

	static bool StringToFloat(const char* pBuf, float &fRes);
protected:
private:
};


#endif