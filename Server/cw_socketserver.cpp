#include "cw_commondefine.h"
#include "cw_socketserver.h"
#include "cw_connectionmanager.h"
#include "cw_connection.h"
#include "cw_log.h"
#include "cw_packetfactorymanager.h"
#include "cw_handlerset.h"
#include "cw_packet.h"
#include "cw_scriptinterface.h"
#include "cw_time.h"

SINGLETONG_IMPLEMENTION(CSocketServer)

	void OnDelConn(CConnection* pConn)
{
	LOG_DEBUG("Conn is Deled, %d", pConn->GetID());
}

void ProcessInput(CConnection* pConn)
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
		//bool bRet = pSocketBuff->PeekBuff(static_cast<char*>(static_cast<void*>(&iPacketHead)), sizeof(iPacketHead));
		bool bRet = IN_PEEK_BUFF(iPacketHead, sizeof(iPacketHead));
		if (!bRet)
		{
			LOG_DEBUG("Head Recover!");
			pSocketBuff->Recover();
			pSocketBuff->EndParse();			
			break;
		}
		if (iPacketHead != PACKET_HEAD)	//异常，断开连接
		{
			CConnectionManager::GetSingleton().DelConn(pConn->GetSocket());
			LOG_DEBUG("Packet head is invalid!");
			break;
		}
		short iPacketID;
		bRet = IN_PEEK_BUFF(iPacketID, sizeof(iPacketID));
		if (!bRet)
		{
			LOG_DEBUG("iPacketID Recover!");
			pSocketBuff->Recover();
			pSocketBuff->EndParse();
			break;
		}
		if (iPacketID < 0 || iPacketID >= EM_PACKET_TYPE_NUMBER)	//异常，断开连接
		{
			CConnectionManager::GetSingleton().DelConn(pConn->GetSocket());
			LOG_DEBUG("Invalid Packet id: %d", iPacketID);
			break;
		}
		if (iPacketID < EM_PACKET_TYPE_START)
		{
			int nRet = SCRIPTMANAGER.CallScript(3, "ProcessPacket", pConn->GetSocket(), iPacketID);
			if (nRet == 0)
			{
				break;
			}
			continue;
		}
		CPacket* pPacket = CPacketFactoryManager::GetSingleton().GeneratePacket(iPacketID);
		if (!pPacket)
		{
			CConnectionManager::GetSingleton().DelConn(pConn->GetSocket());
			LOG_DEBUG("Not CSPacket id: %d", iPacketID);
			break;
		}
		pPacket->SetIsSend(false);
		pPacket->SetBuff(pSocketBuff);
		bRet = pPacket->MapData();
		if (!bRet)
		{
			LOG_DEBUG("pPacket Recover!");
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
void CSocketServer::Init( short port )
{
	m_Port = port;
	CConnectionManager::GetSingleton().Init();	
	CPacketHandlerSet::GetSingleton().Init();
	CPacketFactoryManager::GetSingleton().Init();
	m_FuncProcessInput = 0;
	m_FuncDelConn = 0;
	m_CurrentID = 0;
	SetProcessInputFunc(ProcessInput);
	SetDelConnFunc(OnDelConn);
}

bool CSocketServer::Listen()
{
	WORD version(0);
	WSADATA wsadata;
	int socket_return(0);
	version = MAKEWORD(2,0);
	socket_return = WSAStartup(version,&wsadata);
	int nAddrlen = sizeof(SOCKADDR_IN);
	m_ListenSocket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_ListenSocket == INVALID_SOCKET)
	{
		LOG_DEBUG("create socket error: %d", WSAGetLastError());
		return false;
	}
	m_LocalAddr.sin_family = AF_INET;
	m_LocalAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	m_LocalAddr.sin_port = htons(m_Port);
	int nRet = bind(m_ListenSocket, (sockaddr*)&m_LocalAddr, nAddrlen);
	if (nRet < 0)
	{
		LOG_DEBUG("bind error: %d", errno);
		return false;
	}
	nRet = listen(m_ListenSocket, BACK_LOG);
	if (nRet < 0)
	{
		LOG_DEBUG("listen error: %d", errno);
		return false;
	}	
	return true;
}
void CSocketServer::Work()
{
	CTimeManager::GetSingleton().Tick();
	AcceptConn();
	ProcessNetData();
}
void CSocketServer::AcceptConn()
{	
	FD_ZERO(&m_fdRead);
	FD_SET(m_ListenSocket, &m_fdRead);
	struct timeval tv = {0, 0};     
	int nRet = select(0, &m_fdRead, 0, 0, &tv); 
	if (nRet > 0)
	{
		if (FD_ISSET(m_ListenSocket, &m_fdRead))
		{
			int nAddrlen = sizeof(SOCKADDR_IN);
			SOCKADDR_IN client;
			SOCKET sClient = accept(m_ListenSocket, (sockaddr*)&m_LocalAddr, &nAddrlen);
			if (sClient < 0)
			{
				LOG_DEBUG("accept error: %d", errno);
				return ;
			}
			::getpeername(sClient, (sockaddr*)&client, &nAddrlen);
			LOG_DEBUG("client connected: %d, IP: %s, Port: %d", sClient, inet_ntoa(client.sin_addr), client.sin_port);
			CConnection* pNewConn = CConnectionManager::GetSingleton().AddConn(sClient);
			if (!pNewConn)
			{
				closesocket(sClient);
				LOG_DEBUG("Connection pool is full! Max connection count is %d", CConnectionManager::GetSingleton().GetMaxConns());
				return ;
			}
			else
			{
				pNewConn->SetID(m_CurrentID++);
			}
		}
	}
	
}

void CSocketServer::ProcessNetData()
{
	CConnectionManager::GetSingleton().ProcessNetData();
}
