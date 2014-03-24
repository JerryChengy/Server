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

	static size_t ToPrimeForHashList(const int Value);//רΪhashlist���ã������ط�����
	static float CarmSqrt(float x); //�����������ʹ��
	//һ������� hash ����Ӧ��ɢ�еıȽϿ��������ٶȸ��ַ������ȹ�ϵ�����ֲ���ֻ�����ַ����Ŀ�ͷ��ĩβ��
	//������㷨�Ǵ� Lua �п����ġ�
	static unsigned long hash(const char *name,size_t len);
	static int Strcmp(const char* pStr1, const char* pStr2);
	static int Stricmp(const char* pStr1, const char* pStr2);
	static int Snprintf(char* pBuffer, int maxlen, const char* pFormat,...);
	static char* Strcat(char* pDes, char* pSrc, int iLen);
	static int Chdir(const char* pPath);
	static bool LoadAllFileNameInDir(const char* pDir, const char* pPattern, std::vector<std::string>& vecFiles);
protected:
private:
};
	int int2fb (unsigned int x);
	int fb2int (int x);
	int log2 (unsigned int x);
	void chunkid (char *out, const char *source, size_t bufflen);
#endif