#include "cw_memoryio.h"

bool CMemoryIO::Init( char* pSrcData, int iDataLen )
{
	if (!pSrcData || iDataLen <= 0)
	{
		return false;
	}
	m_pData = pSrcData;
	m_MaxLen = iDataLen;
	return true;
}



bool CMemoryWriter::Write( char* pSrcData, int iDataLen )
{
	if (!pSrcData || iDataLen <= 0)
	{
		return false;
	}
	if (m_CurLen + iDataLen > m_MaxLen)
	{
		return false;
	}
	memcpy(m_pData+m_CurLen, pSrcData, iDataLen);
	m_CurLen = iDataLen;
	return true;
}

bool CMemoryReader::Read( char* pDesData, int iDataLen )
{
	if (!pDesData || iDataLen <= 0)
	{
		return false;
	}
	if (m_CurLen + iDataLen > m_MaxLen)
	{
		return false;
	}
	memcpy(pDesData, m_pData+m_CurLen, iDataLen);
	m_CurLen += iDataLen;
	return true;
}
