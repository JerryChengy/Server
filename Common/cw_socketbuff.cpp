#include "cw_socketbuff.h"
#include "cw_log.h"

CSocketBuff::CSocketBuff( int iBuffLen ): m_BuffLen(iBuffLen)
{
	m_Buff = new char[iBuffLen];
	memset(m_Buff, 0, iBuffLen);
	m_iHead = -1;//m_iHead: 指向第一个数据	
	m_iTail = -1;//m_iTail: 指向最后一个数据
	m_iOldHead = -1;
	m_iOldTail = -1;
	m_Socket = -1;
}

CSocketBuff::~CSocketBuff()
{
	delete[] m_Buff;
}

bool CSocketBuff::PeekBuff(char* pBuff, int iBuffLen)
{
	if (m_iHead == -1)
	{
		return false;
	}
	if (m_iTail >= m_iHead)
	{
		int iDataLen = m_iTail - m_iHead + 1;
		if (iBuffLen > iDataLen)
		{
			return false;
		}
		memcpy(pBuff, m_Buff+m_iHead, iBuffLen);
		m_iHead += iBuffLen;
		if (m_iHead > m_iTail)
		{
			m_iHead = m_iTail = -1;
		}
		return true;
	}
	else
	{
		int iDataLen = m_BuffLen - m_iHead + m_iTail + 1;
		if (iBuffLen > iDataLen)
		{
			return false;
		}
		if (iBuffLen < m_BuffLen - m_iHead)
		{
			memcpy(pBuff, m_Buff+m_iHead, iBuffLen);
			m_iHead += iBuffLen;
			return true;
		}
		else
		{
			memcpy(pBuff, m_Buff+m_iHead, m_BuffLen - m_iHead);			
			memcpy(pBuff + m_BuffLen - m_iHead, m_Buff, iBuffLen-(m_BuffLen - m_iHead));
			m_iHead = iBuffLen-(m_BuffLen - m_iHead);
			if (iBuffLen == iDataLen)
			{
				m_iHead = -1;
				m_iTail = -1;
			}
			return true;
		}
	}
	return true;
}
char* CSocketBuff::ResizeBuff(char* buff, int& curMaxLen, int& iHead, int& iTail, int minLen)
{
	minLen += 1;
	int iLen = 0;
	int iOldLen = curMaxLen;
	while (curMaxLen < minLen)
	{
		curMaxLen *= 2;
	}
	char * pNewBuff = new char[curMaxLen];
	memset(pNewBuff, 0, curMaxLen);
	memcpy(pNewBuff, buff+iHead, iOldLen-iHead);
	memcpy(pNewBuff+iOldLen-iHead, buff, iHead);
	if (iTail > iHead)
	{
		iTail = iTail - iHead;
		iHead = 0;
	}
	else if (iTail < iHead)
	{
		iTail = iOldLen - iHead + iTail;
		iHead = 0;
	}
	else
	{
		if (iHead >= 0)
		{
			iHead = 0;
			iTail = 0;
		}
	}
	delete[] buff;	
	return pNewBuff;
}

void CSocketBuff::Fill(const char* pBuff, int iBuffLen)
{
	//m_iHead: 指向第一个数据
	//m_iTail: 指向最后一个数据
	if (m_iTail == -1 && m_iHead == -1) //一个数据都没有
	{
		if (iBuffLen > m_BuffLen)//空间不够，扩充
		{
			int iOldBuffLen = m_BuffLen;
			m_Buff = ResizeBuff(m_Buff, m_BuffLen, m_iHead, m_iTail, iBuffLen);
			LOG_DEBUG("Resize recv buff, old buff len: %d, new buff len: %d", iOldBuffLen, m_BuffLen);
		}
		memcpy(m_Buff, pBuff, iBuffLen);
		m_iHead = 0;
		m_iTail = iBuffLen - 1;
	}
	else //缓冲里已经有一部分数据了
	{
		if (m_iTail >= m_iHead)
		{
			int iTailBuffLen = m_BuffLen - m_iTail - 1;
			if (iTailBuffLen >= iBuffLen)//缓冲区尾部空间足够容纳下接收到的数据
			{
				memcpy(m_Buff+m_iTail+1, pBuff, iBuffLen);
				m_iTail += iBuffLen;
			}
			else //缓冲区的头尾部空间各装一部分数据
			{
				memcpy(m_Buff+m_iTail+1, pBuff, iTailBuffLen);
				m_iTail += iTailBuffLen;
				int iLeftDataLen = iBuffLen - iTailBuffLen;
				if (iLeftDataLen > m_iHead)
				{
					int iOldBuffLen = m_BuffLen;
					m_Buff = ResizeBuff(m_Buff, m_BuffLen, m_iHead, m_iTail, m_BuffLen+iLeftDataLen);
					LOG_DEBUG("Resize recv buff, old buff len: %d, new buff len: %d", iOldBuffLen, m_BuffLen);
					memcpy(m_Buff+m_iTail+1, pBuff+iTailBuffLen, iLeftDataLen);
					m_iTail += iLeftDataLen;
				}
				else
				{
					memcpy(m_Buff, pBuff+iTailBuffLen, iLeftDataLen);
					m_iTail = iLeftDataLen-1;
				}
			}
		}
		else
		{
			int iLeftBuffLen = m_iHead - m_iTail - 1;
			if (iLeftBuffLen < iBuffLen)
			{
				int iOldBuffLen = m_BuffLen;
				m_Buff = ResizeBuff(m_Buff, m_BuffLen, m_iHead, m_iTail, m_BuffLen+iBuffLen);
				LOG_DEBUG("Resize recv buff, old buff len: %d, new buff len: %d", iOldBuffLen, m_BuffLen);
				memcpy(m_Buff+m_iTail+1, pBuff, iBuffLen);
				m_iHead = 0;
				m_iTail += iBuffLen;
			}
			else
			{
				memcpy(m_Buff+m_iTail+1, pBuff, iBuffLen);
				m_iTail += iBuffLen;
			}
		}
	}
}

void CSocketBuff::BeginParse()
{
	m_iOldHead = m_iHead;
	m_iOldTail = m_iTail;
}

void CSocketBuff::EndParse()
{
	m_iOldHead = -1;
	m_iOldTail = -1;
}

bool CSocketBuff::Flush()
{
	if (m_iHead == -1)
	{
		return true;
	}
	int iFlag = 0;
	if (m_iHead <= m_iTail)
	{
		int iSend = send(m_Socket, m_Buff+m_iHead, m_iTail-m_iHead+1, iFlag);
		if (iSend == -1)
		{
			if (errno == WSAEWOULDBLOCK || errno == WSAENOBUFS)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else if (iSend == 0)
		{
			return true;
		}
		else
		{
			m_iHead += iSend;
		}
		if (m_iHead > m_iTail)
		{
			m_iHead = -1;
			m_iTail = -1;
			return true;
		}
	}
	else
	{
		//先发送前半部分
		int iSend = send(m_Socket, m_Buff+m_iHead, m_BuffLen-m_iHead, iFlag);
		if (iSend == -1)
		{
			if (errno == WSAEWOULDBLOCK || errno == WSAENOBUFS)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else if (iSend == 0)
		{
			return true;
		}
		else
		{
			m_iHead = 0;
			iSend = send(m_Socket, m_Buff+m_iHead, m_iTail-m_iHead+1, iFlag);
			if (iSend == -1)
			{
				if (errno == WSAEWOULDBLOCK || errno == WSAENOBUFS)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			else if (iSend == 0)
			{
				return true;
			}
			else
			{
				m_iHead += iSend;
			}
			if (m_iHead > m_iTail)
			{
				m_iHead = -1;
				m_iTail = -1;
				return true;
			}
		}
	}
	return true;
}

void CSocketBuff::FillString( const char* pStr, short iStrLen )
{
	if (!pStr)
	{
		return ;
	}
	Fill((char*)(void *)&iStrLen, sizeof(iStrLen));
	Fill(pStr, iStrLen);
}
