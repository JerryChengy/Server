#include "cw_commondefine.h"
#include "cw_tools.h"
#include "cw_assert.h"

void CTools::Strcpy( char* pDes, const char* pSrc, int iLen )
{
	if (!pDes || !pSrc)
	{
		return ;
	}
	strncpy(pDes, pSrc, iLen);
}

bool CTools::StringToInt( const char* pBuf, int &nRes )
{
	if (!pBuf)
	{
		return false;
	}
	const char* pTmpBuf = pBuf;
	while(*pTmpBuf != '\0')
	{
		if (*pTmpBuf<'0' || *pTmpBuf>'9')
		{
			Assert(false);
			return false;
		}
		pTmpBuf++;
	}
	if (strlen(pBuf)>0)
	{
		nRes = atoi(pBuf);
		return true;
	}
	return false;
}

bool CTools::StringToFloat( const char* pBuf, float &fRes )
{
	if (!pBuf)
	{
		return false;
	}
	const char* pTmpBuf = pBuf;
	if (*pTmpBuf<'0' || *pTmpBuf>'9')
	{
		Assert(false);
		return false;
	}
	while(*pTmpBuf != '\0')
	{
		if ((*pTmpBuf<'0' || *pTmpBuf>'9') && *pTmpBuf != '.')
		{
			Assert(false);
			return false;
		}
		pTmpBuf++;
	}
	if (strlen(pBuf)>0)
	{
		fRes = static_cast<float>(atof(pBuf));
		return true;
	}
	return false;
}

int CTools::Strlen( const char* pStr )
{
	if (!pStr)
	{
		Assert(false);
		return -1;
	}
	return strlen(pStr);
}

bool CTools::SplitString( const char* pSrc, MUL_STRING& vecRes, char splitChar )
{
	if (!pSrc)
	{
		return false;
	}
	char TmpStr[256] = {};
	int iSrcIndex = 0;
	while (pSrc[iSrcIndex] != '\0')
	{
		int iDesIndex = 0;
		while (pSrc[iSrcIndex] != splitChar && pSrc[iSrcIndex] != '\0')
		{
			if (iDesIndex >= sizeof(TmpStr)/sizeof(char))
			{
				Assert(false);
				return false;
			}
			TmpStr[iDesIndex]=pSrc[iSrcIndex];
			iDesIndex++;
			iSrcIndex++;
		}
		vecRes.push_back(TmpStr);
		memset(TmpStr, 0, sizeof(TmpStr));
		if (pSrc[iSrcIndex] == '\0')
		{
			break;
		}
		if (pSrc[iSrcIndex] == splitChar)
		{
			iSrcIndex++;
		}
	}	
	return true;
}

bool CTools::SplitString( const char* pSrc, MUL_INT& vecRes, char splitChar )
{
	if (!pSrc)
	{
		return false;
	}
	char TmpStr[256] = {};
	int iSrcIndex = 0;
	while (pSrc[iSrcIndex] != '\0')
	{
		int iDesIndex = 0;
		while (pSrc[iSrcIndex] != splitChar && pSrc[iSrcIndex] != '\0')
		{
			if (iDesIndex >= sizeof(TmpStr)/sizeof(char))
			{
				vecRes.clear();
				Assert(false);
				return false;
			}
			TmpStr[iDesIndex]=pSrc[iSrcIndex];
			iDesIndex++;
			iSrcIndex++;
		}
		int nRes = 0;
		bool bRes = CTools::StringToInt(TmpStr, nRes);
		if (!bRes)
		{
			vecRes.clear();
			Assert(false);
			return false;
		}
		vecRes.push_back(nRes);
		if (pSrc[iSrcIndex] == '\0')
		{
			break;
		}
		if (pSrc[iSrcIndex] == splitChar)
		{
			iSrcIndex++;
		}
	}	
	return true;
}

bool CTools::IsEqualString( const char* pStr1, const char* pStr2 )
{
	if (!pStr1 || !pStr2)
	{
		Assert(false);
		return false;
	}
	int iRet = strcmp(pStr1, pStr2);
	if (iRet == 0)
	{
		return true;
	}
	return false;
}


size_t CTools::ToPrimeForHashList( const int Value )
{
	static size_t Primes[] = {
		127, 251, 509, 1021, 2039, 4093, 8191, 16381, 32749, 65521, 131071,
		262139, 524287, 1048573, 2097143, 4194301, 8388593, 16777213, 33554393,
		67108859, 134217689, 268435399, 536870909, 1073741789, 2147483647
	};
	for (int i = 0; i < sizeof(Primes)/sizeof(size_t); i++) {
		size_t Result = Primes[i];
		if (Value <= Result) return Result;
	}
	return (Value + Value / 2) | 1;
}

float CTools::CarmSqrt(float x)
{
	union{
		int intPart;
		float floatPart;
	} convertor;
	union{
		int intPart;
		float floatPart;
	} convertor2;
	convertor.floatPart = x;
	convertor2.floatPart = x;
	convertor.intPart = 0x1FBCF800 + (convertor.intPart >> 1);
	convertor2.intPart = 0x5f3759df - (convertor2.intPart >> 1);
	return 0.5f*(convertor.floatPart + (x * convertor2.floatPart));
}

unsigned long CTools::hash(const char *name,size_t len)
{
	unsigned long h=(unsigned long)len;
	size_t step = (len>>5)+1;
	for (size_t i=len; i>=step; i-=step)
		h = h ^ ((h<<5)+(h>>2)+(unsigned long)name[i-1]);
	return h;
}

int int2fb (unsigned int x) {
	int e = 0;  /* expoent */
	while (x >= 16) {
		x = (x+1) >> 1;
		e++;
	}
	if (x < 8) return x;
	else return ((e+1) << 3) | ((int)x - 8);
}

int fb2int (int x) {
	int e = (x >> 3) & 31;
	if (e == 0) return x;
	else return ((x & 7)+8) << (e - 1);
}

int log2 (unsigned int x) {
	static const unsigned char log_3[256] = {
		0,1,2,2,3,3,3,3,4,4,4,4,4,4,4,4,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
		6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,
		7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
		7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
		8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
		8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
		8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
		8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8
	};
	int l = -1;
	while (x >= 256) { l += 8; x >>= 8; }
	return l + log_3[x];

}
void chunkid (char *out, const char *source, size_t bufflen) {
	if (*source == '=') {
		strncpy(out, source+1, bufflen);  /* remove first char */
		out[bufflen-1] = '\0';  /* ensures null termination */
	}
	else {  /* out = "source", or "...source" */
		if (*source == '@') {
			size_t l;
			source++;  /* skip the `@' */
			bufflen -= sizeof(" '...' ");
			l = strlen(source);
			strcpy(out, "");
			if (l > bufflen) {
				source += (l-bufflen);  /* get last part of file name */
				strcat(out, "...");
			}
			strcat(out, source);
		}
		else {  /* out = [string "string"] */
			size_t len = strcspn(source, "\n\r");  /* stop at first newline */
			bufflen -= sizeof(" [string \"...\"] ");
			if (len > bufflen) len = bufflen;
			strcpy(out, "[string \"");
			if (source[len] != '\0') {  /* must truncate? */
				strncat(out, source, len);
				strcat(out, "...");
			}
			else
				strcat(out, source);
			strcat(out, "\"]");
		}
	}
}