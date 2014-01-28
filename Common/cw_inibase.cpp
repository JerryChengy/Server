#include "cw_commondefine.h"
#include "cw_inibase.h"
#include "cw_tools.h"
#include "cw_inireader.h"
#include "cw_assert.h"
#include "cw_inireader.h"

bool INI_BASE::Init(const char* pFileName, const char* pKeyStr)
{
	if (!pFileName || !pKeyStr)
	{
		Assert(false);
		return false;
	}
	bool bRet = CIniReader::GetSingleton().Init(pFileName, pKeyStr);	
	return bRet;
}

bool INI_BASE::Load(const char* pFileName, const char* pKeyStr)
{
	if (!Init(pFileName, pKeyStr))
	{
		Release();
		return false;
	}
	ReadData();
	Release();
	return true;
}

void INI_BASE::Release()
{
	CIniReader::GetSingleton().Release();
}

void INI_BASE::GetVarValStr(const char* pVarName)
{
	CIniReader::GetSingleton().ClearVarBuf();
	if (!pVarName)
	{
		Assert(false);
		return ;
	}
	const char* pBuf = CIniReader::GetSingleton().GetLine();
	if (!pBuf)
	{
		Assert(false);
		return ;
	}
	bool bFind = false;
	while (pBuf && !IsKeyLine(pBuf))
	{
		if (NULL != strstr(pBuf, pVarName))
		{
			char szBuf[BUFF_LEN_1024] = {};
			DelSpaceAndTab(pBuf, szBuf, sizeof(szBuf)-1);
			const char* pChar = strstr(szBuf, pVarName);
			if (pChar == szBuf)
			{
				pChar = &szBuf[strlen(pVarName)];
				if (*pChar == '=')
				{
					++pChar;					
					CIniReader::GetSingleton().SetVarBuf(pChar, CTools::Strlen(pChar));
					bFind = true;
					break;
				}	
			}			
		}
		pBuf = CIniReader::GetSingleton().GetLine();
	}
	Assert(bFind);
}
void INI_BASE::Read(const char* pVarName, int& VarValue)
{
	if (!pVarName)
	{
		Assert(false);
		return ;
	}
	GetVarValStr(pVarName);
	CTools::StringToInt(CIniReader::GetSingleton().GetVarBuf(), VarValue);
}

void INI_BASE::Read(const char* pVarName, float& VarValue)
{
	if (!pVarName)
	{
		Assert(false);
		return ;
	}
	GetVarValStr(pVarName);
	CTools::StringToFloat(CIniReader::GetSingleton().GetVarBuf(), VarValue);
}

void INI_BASE::Read(const char* pVarName, char*& pVarValue)
{
	if (!pVarName)
	{
		Assert(false);
		return ;
	}
	GetVarValStr(pVarName);
	const char* pVarBuf = CIniReader::GetSingleton().GetVarBuf();
	int nLen = CTools::Strlen(pVarBuf);
	pVarValue = new char[nLen+1];
	CTools::Strcpy(pVarValue, pVarBuf, nLen);
	pVarValue[nLen] = '\0';
}

void INI_BASE::DelSpaceAndTab(const char* pSrcBuf, char* pDestBuf, int nDestLen)
{
	if (!pSrcBuf || !pDestBuf)
	{
		return ;
	}
	int nLen = CTools::Strlen(pSrcBuf);
	int nDestBufIndex = 0;
	for (int i=0;i<nLen;i++)
	{
		if (pSrcBuf[i] == ' ' || pSrcBuf[i] == '\t')
		{
			continue;
		}
		if (nDestBufIndex >= nDestLen)
		{
			return ;
		}
		pDestBuf[nDestBufIndex++] = pSrcBuf[i];
	}
}
bool INI_BASE::IsKeyLine(const char* pLine)
{
	if (!pLine)
	{
		Assert(false);
		return false;
	}
	bool bHaveLeftBorder = false;
	bool bHaveRightBorder = false;
	int nLen = CTools::Strlen(pLine);
	for (int i=0;i<nLen;i++)
	{
		if (pLine[i] == '[')
		{
			bHaveLeftBorder = true;
		}
		if (pLine[i] == ']')
		{
			bHaveRightBorder = true;
		}
	}
	if (bHaveLeftBorder&&bHaveRightBorder)
	{
		return true;
	}
	return false;
}


