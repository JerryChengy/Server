#include "cw_commondefine.h"
#include "cw_connectionmanager.h"
#include "cw_socketserver.h"
#include "cw_connection.h"
#include "cw_log.h"

SINGLETONG_IMPLEMENTION(CConnectionManager)
	CConnectionManager::CConnectionManager(  )
{
	m_MaxConns = FD_SETSIZE;
	m_ConnectionSet = new CConnection[m_MaxConns];
	m_ConnCount = 0;
}

bool CConnectionManager::Init( )
{
	return true;
}


CConnection* CConnectionManager::AddConn( SOCKET socket )
{
	//m_Lock.Lock();
	if (m_ConnCount < 0 || m_ConnCount >= m_MaxConns)
	{
	//	m_Lock.Unlock();
		return 0;
	}
	bool bRet = m_ConnectionSet[m_ConnCount].Init(socket);
	if (bRet)
	{
		return &m_ConnectionSet[m_ConnCount++];
	}
	return 0;
//	m_Lock.Unlock();

}

void CConnectionManager::DelConn( SOCKET socket )
{
	//m_Lock.Lock();
	for (int i = 0; i < m_ConnCount; ++i)
	{
		if (m_ConnectionSet[i].GetSocket() == socket)
		{
			CConnection TempConn = m_ConnectionSet[i];
			m_ConnectionSet[i] = m_ConnectionSet[m_ConnCount - 1];
			m_ConnectionSet[m_ConnCount - 1] = TempConn;
			m_ConnectionSet[m_ConnCount - 1].Reset();
			m_ConnCount--;
			//m_Lock.Unlock();
			return ;
		}
	}
	//m_Lock.Unlock();
}


void CConnectionManager::ProcessNetData()
{
	fd_set fdread;
	fd_set fdwrite;
	struct timeval tv = {0, 0};     
	FD_ZERO(&fdread);  
	FD_ZERO(&fdwrite);
	for (int i = 0; i < m_ConnCount; i++)      
	{     
		FD_SET(m_ConnectionSet[i].GetSocket(), &fdread);   
		FD_SET(m_ConnectionSet[i].GetSocket(), &fdwrite);   
	}     	
	int nRet = select(0, &fdread, &fdwrite, NULL, &tv);  
	if (nRet > 0)      
	{     
		for (int i = 0; i < m_ConnCount; i++)      
		{     
			SOCKET sClient = m_ConnectionSet[i].GetSocket();
			if (FD_ISSET(sClient, &fdread)) //接收数据
			{     
				bool bRet = m_ConnectionSet[i].Recv();     
				if (bRet == false)      
				{     
					LOG_DEBUG("Client socket %d closed.", sClient);     
					closesocket(sClient);   
					ConnCallBack pFuncDelConn = CSocketServer::GetSingleton().GetDelConnFunc();
					if (!pFuncDelConn)
					{
						continue;
					}
					(*pFuncDelConn)(&m_ConnectionSet[i]);
					DelConn(sClient);
					i--;
					continue;
				}      
				else
				{
					ConnCallBack pFuncProcessInput = CSocketServer::GetSingleton().GetProcessInputFunc();
					if (!pFuncProcessInput)
					{
						continue;
					}
					(*pFuncProcessInput)(&m_ConnectionSet[i]);
				}
			} 
			if (FD_ISSET(sClient, &fdwrite))	//发送数据
			{
				bool bRet = m_ConnectionSet[i].FlushSendBuff();     
				if (bRet == false)      
				{     
					LOG_DEBUG("Client socket %d closed.", sClient);     
					closesocket(sClient);   
					ConnCallBack pFuncDelConn = CSocketServer::GetSingleton().GetDelConnFunc();
					if (!pFuncDelConn)
					{
						continue;
					}
					(*pFuncDelConn)(&m_ConnectionSet[i]);
					DelConn(sClient);
					i--;
					continue;
				}      
			}
		}    
	}     
}

CConnection* CConnectionManager::GetConn( SOCKET socket )
{
	for (int i = 0; i < m_ConnCount; ++i)
	{
		if (m_ConnectionSet[i].GetSocket() == socket)
		{
			return &m_ConnectionSet[i];
		}
	}
	return 0;
}

