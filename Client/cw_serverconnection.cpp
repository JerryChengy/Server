#include "cw_serverconnection.h"
#include "cw_packetfactorymanager.h"
#include "cw_log.h"
#include "cw_packet.h"
#include "cw_commonhandler.h"
#include "cw_handlerset.h"

SINGLETONG_IMPLEMENTION(CServerConnection)

	void CServerConnection::SendPacket( CPacket* pPacket )
{
	m_ServerConn.SendPacket(pPacket);
}

bool CServerConnection::Init()
{
	CPacketHandlerSet::GetSingleton().Init();
	CPacketFactoryManager::GetSingleton().Init();
	WORD version(0);
	WSADATA wsadata;
	int socket_return(0);
	version = MAKEWORD(2,0);
	socket_return = WSAStartup(version,&wsadata);
	SOCKADDR_IN sockAddr;
	int nSockAddrLen = sizeof(sockAddr);
	SOCKET sockFd;
	sockFd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockFd < 0)
	{
		LOG_DEBUG("socket error!");
		return false;
	}
	sockAddr.sin_family =  AF_INET;
	sockAddr.sin_port = htons(PORT);
	sockAddr.sin_addr.s_addr = ::inet_addr("127.0.0.1");

	int nRet = connect(sockFd, (sockaddr*)&sockAddr, nSockAddrLen);
	if (nRet < 0)
	{
		LOG_DEBUG("connect error: %d", nRet);
		return false;
	}
	else
	{
		LOG_DEBUG("connect success!");
	}	
	m_ServerConn.Init(sockFd);
	m_FuncProcessInput = CServerConnection::ProcessInput;	

	return true;
}


void CServerConnection::ProcessInput(CConnection* pConn)
{
#define IN_PEEK_BUFF(buffData, len) pSocketBuff->PeekBuff(static_cast<char*>(static_cast<void*>(&buffData)), len);
	if (!pConn)
	{
		return ;
	}
	CSocketBuff* pSocketBuff = pConn->GetRecvBuff();
	while (1) //正常情况下一次循环一个包
	{	
		pSocketBuff->BeginParse();
		//包头
		int iPacketHead;
		bool bRet = IN_PEEK_BUFF(iPacketHead, sizeof(iPacketHead));
		if (!bRet)
		{
			pSocketBuff->Recover();
			pSocketBuff->EndParse();			
			break;
		}
		if (iPacketHead != PACKET_HEAD)	//异常，断开连接
		{
			LOG_DEBUG("Packet head is invalid!");
			pConn->Close();
			break;
		}
		short iPacketID;
		bRet = IN_PEEK_BUFF(iPacketID, sizeof(iPacketID));
		if (!bRet)
		{
			pSocketBuff->Recover();
			pSocketBuff->EndParse();
			break;
		}
		if (iPacketID < 0 || iPacketID >= EM_PACKET_TYPE_NUMBER)	//异常，断开连接
		{
			LOG_DEBUG("Invalid Packet id: %d", iPacketID);
			pConn->Close();
			break;
		}

		CPacket* pPacket = CPacketFactoryManager::GetSingleton().GeneratePacket(iPacketID);
		if (!pPacket)
		{
			LOG_DEBUG("Not SCPacket id: %d", iPacketID);
			pConn->Close();
			break;
		}
		pPacket->SetIsSend(false);
		pPacket->SetBuff(pSocketBuff);
		bRet = pPacket->MapData();
		if (!bRet)
		{
			pSocketBuff->Recover();
			pSocketBuff->EndParse();
			break;
		}
		pSocketBuff->EndParse();	
		FuncHandler pHandler = CPacketHandlerSet::GetSingleton().GetHandler(iPacketID);
		if (pHandler)
		{
			int nRet = (*pHandler)(pPacket, pConn);
		}
		else
		{
			LOG_DEBUG("Packet has no handler, id: %d", iPacketID);
			break;
		}
	}

}
void CServerConnection::SetProcessInputFunc(ConnCallBack func)
{
	m_FuncProcessInput = func;
}

void CServerConnection::ProcessNetData()
{
	FD_SET Fdread, Fdwrite;
	FD_ZERO(&Fdread);  
	FD_ZERO(&Fdwrite);
	FD_SET(m_ServerConn.GetSocket(), &Fdread);
	FD_SET(m_ServerConn.GetSocket(), &Fdwrite);
	struct timeval tv = {0, 0};   
	int nRet = select(0, &Fdread, &Fdwrite, NULL, &tv);  
	if (nRet > 0)    
	{
		SOCKET sServer = m_ServerConn.GetSocket();
		if (FD_ISSET(sServer, &Fdread))
		{
			bool bRet = m_ServerConn.Recv();
			if (bRet == false)
			{
				LOG_DEBUG("Disconnect Server.");
			}
			else
			{
				if (m_FuncProcessInput)
				{
					(*m_FuncProcessInput)(&m_ServerConn);
				}
			}
		}
		if (FD_ISSET(sServer, &Fdwrite))
		{
			bool bRet = m_ServerConn.FlushSendBuff();
			if (bRet == false)
			{
				LOG_DEBUG("Disconnect Server.");
			}
		}
	}
	else
	{
		LOG_DEBUG("select error, %d.", WSAGetLastError());
		/*LPVOID lpMsgBuf; 
		FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | 
			FORMAT_MESSAGE_FROM_SYSTEM | 
			FORMAT_MESSAGE_IGNORE_INSERTS, 
			NULL, 
			GetLastError(), 
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), 
			(LPTSTR) &lpMsgBuf, 
			0, 
			NULL 
			); 
		MessageBox( NULL, (LPCTSTR)lpMsgBuf, "Error", MB_OK | MB_ICONINFORMATION ); 
		LocalFree( lpMsgBuf ); */
	}
}

void SendPacket( CPacket* pPacket )
{
	CServerConnection::GetSingleton().SendPacket(pPacket);
}
