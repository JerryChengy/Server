#include "cw_serializer.h"


bool CLineDataDisposer::Init(const char* pLine, char cSplitChar)
{		
	if (!pLine)
	{
		return false;
	}
	memset(m_LineData, 0, sizeof(m_LineData));
	strncpy(m_LineData, pLine, sizeof(m_LineData)-1);
	m_pCurLineChar = m_LineData;	
	m_pCurBlockChar = m_BlockData;
	m_SplitChar = cSplitChar;
	return true;
}	
int  CLineDataDisposer::MoveBlock()
{
	memset(m_BlockData, 0, sizeof(m_BlockData));
	int nBlockLen = 0;
	m_pCurBlockChar = m_BlockData;
	while (*m_pCurLineChar!=m_SplitChar && *m_pCurLineChar!='\0')
	{
		*m_pCurBlockChar++ = *m_pCurLineChar++;
		nBlockLen++;
	}
	if (*m_pCurLineChar == m_SplitChar)
	{
		m_pCurLineChar++;
	}
	return nBlockLen;
}

const char* CLineDataDisposer::NextBlock()
{
	int nBlockLen = MoveBlock();
	if (nBlockLen <= 0)
	{
		return 0;
	}
	return m_BlockData;
}