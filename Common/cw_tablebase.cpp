#include "cw_tablebase.h"
#include "cw_const.h"
#include "cw_assert.h"
#include "cw_tools.h"

SINGLETONG_IMPLEMENTION(CLineDataDisposer);

bool CLineDataDisposer::Init(const char* pLine)
{		
	if (!pLine)
	{
		return false;
	}
	memset(m_LineData, 0, sizeof(m_LineData));
	strncpy(m_LineData, pLine, sizeof(m_LineData)-1);
	m_pCurLineChar = m_LineData;	
	m_pCurBlockChar = m_BlockData;
	return true;
}	
int  CLineDataDisposer::MoveBlock()
{
	memset(m_BlockData, 0, sizeof(m_BlockData));
	int nBlockLen = 0;
	m_pCurBlockChar = m_BlockData;
	while (*m_pCurLineChar!='\t' && *m_pCurLineChar!='\0')
	{
		*m_pCurBlockChar++ = *m_pCurLineChar++;
		nBlockLen++;
	}
	if (*m_pCurLineChar == '\t')
	{
		m_pCurLineChar++;
	}
	return nBlockLen;
}

bool TABLE_BASE::smTableGood = true;
bool TABLE_BASE::Init(const char* pLine)
{	
	if (!pLine)
	{
		return false;
	}
	g_pLineDataDisposer->Init(pLine);
	In(m_ID);
	return true;
}	

void TABLE_BASE::In(int& para)
{
	para = 0;
	int nBlockLen = g_pLineDataDisposer->MoveBlock();
	if (nBlockLen == 0)
	{
		smTableGood = false;
		Assert(false);				
		return ;
	}
	bool bRet = CTools::StringToInt(g_pLineDataDisposer->m_BlockData, para);
	if (!bRet)
	{
		smTableGood = false;
		return;
	}
}	
void TABLE_BASE::In(char*& para)
{
		para = NULL;
	int nBlockLen = g_pLineDataDisposer->MoveBlock();
	if (nBlockLen == 0)
	{
		smTableGood = false;
		Assert(false);
		return ;
	}
	para = new char[nBlockLen+1];
	memset(para, 0, nBlockLen+1);
	strncpy(para, g_pLineDataDisposer->m_BlockData, nBlockLen);	
}
void TABLE_BASE::In(IntArray& para)
{
		int nBlockLen = g_pLineDataDisposer->MoveBlock();
	if (nBlockLen == 0)
	{
		smTableGood = false;
		Assert(false);
		return ;
	}

	int nIntCount = 0;		
	for (int i=0;i<nBlockLen;++i)
	{
		if (g_pLineDataDisposer->m_BlockData[i] == '|')
		{
			nIntCount++;
		}
	}
	para.SetCount(nIntCount+1);
	para.Init();

	char pBuf[BUFF_LEN_32] = {};
	const char* pChar = g_pLineDataDisposer->m_BlockData;
	int iBufIndex = 0;
	int iIntIndex = 0;
	for (int i=0;i<nBlockLen;++i)
	{
		if (g_pLineDataDisposer->m_BlockData[i] != '|')
		{
			pBuf[iBufIndex] = g_pLineDataDisposer->m_BlockData[i];
			iBufIndex++;
		}
		else
		{
			bool bRet = CTools::StringToInt(pBuf, para[iIntIndex++]);
			if (!bRet)
			{
				smTableGood = false;
				return;
			}
			memset(pBuf, 0, sizeof(pBuf));
			iBufIndex = 0;
		}
	}
	bool bRet = CTools::StringToInt(pBuf, para[iIntIndex]);
	if (!bRet)
	{
		smTableGood = false;
		return;
	}
}
void TABLE_BASE::In(float &para)
{
		para = 0.0f;
	int nBlockLen = g_pLineDataDisposer->MoveBlock();
	if (nBlockLen == 0)
	{
		smTableGood = false;
		Assert(false);				
		return ;
	}
	bool bRet = CTools::StringToFloat(g_pLineDataDisposer->m_BlockData, para);
	if (!bRet)
	{
		smTableGood = false;
		return;
	}
}

