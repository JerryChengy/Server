#include "cw_commondefine.h"
#include "cw_connection.h"
#include "cw_socketdef.h"
#include "cw_socketapi.h"
#include "cw_packet.h"

CConnection::CConnection()
{
	m_Socket = -1;	
	m_ID = -1;
	m_RecvBuff = new CSocketBuff(ReceiveSocketBuffLen);
	m_SendBuff = new CSocketBuff(SendSocketBuffLen);
}

bool CConnection::Init( SOCKET socket )
{
	if (socket == -1)
	{
		return false;
	}
	m_Socket = socket;

	m_RecvBuff->SetSocket(m_Socket);
	m_SendBuff->SetSocket(m_Socket);
	CSocketAPI::SetIOMode(m_Socket, true);
	return true;
}
void CConnection::Reset()
{
	m_Socket = -1;	
	m_ID = -1;
	m_RecvBuff->Clear();	
	m_SendBuff->Clear();		
}

bool CConnection::IsValid()
{
	return m_Socket!=-1;
}


bool CConnection::FlushSendBuff()
{
	return m_SendBuff->Flush();
}

bool CConnection::SendPacket(CPacket* pPacket)
{
	if (!pPacket)
	{
		return false;
	}
	pPacket->SetIsSend(true);
	pPacket->SetBuff(m_SendBuff);
	pPacket->MapData();
	return true;
}
bool CConnection::Recv()
{
	while (1)
	{
		unsigned int nLen = CSocketAPI::GetLeftRecvDataLen(m_Socket);
		if (nLen == 0)
		{
			return true;
		}
		else if (nLen < 0)
		{
			return false;
		}
		char szTempBuff[1024] = {};
		int nDataLen = recv(m_Socket, szTempBuff, sizeof(szTempBuff), 0);
		if (nDataLen == -1)
		{
			if (errno == WSAEWOULDBLOCK)
			{
				continue;
			}
			return false;
		}
		if (nDataLen == 0)
		{
			return false;
		}
		m_RecvBuff->Fill(szTempBuff, nDataLen);		
	}
	return true;
}

void CConnection::Close()
{
	closesocket(m_Socket);
	m_ID = -1;
	m_Socket = -1;
	m_RecvBuff->Clear();
	m_SendBuff->Clear();
}

