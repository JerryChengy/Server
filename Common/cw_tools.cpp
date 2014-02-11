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
