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
