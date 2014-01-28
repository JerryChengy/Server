#ifndef CW_CONNECTION_H
#define CW_CONNECTION_H
#include "cw_commondefine.h"
#include "cw_socketbuff.h"

class CPacket;
class CConnection
{
public:
	CConnection();

	void		Reset();

	bool		IsValid();

	bool        Init(SOCKET socket);

	SOCKET		GetSocket(){ return m_Socket; }

	bool		Recv();

	int			GetID(){ return m_ID; }
	void		SetID(int id){ m_ID = id; }

	CSocketBuff*		GetRecvBuff(){ return m_RecvBuff; }

	CSocketBuff*		GetSendBuff(){ return m_SendBuff; }

	void		CopyBuff(char* pBuff, int iBuffLen);

	bool		FlushSendBuff();

	bool		SendPacket(CPacket* pPacket);

	void		Close();


protected:
private:
	SOCKET		m_Socket;

	int			m_ID;

	CSocketBuff*	m_RecvBuff;

	CSocketBuff*    m_SendBuff;

};
#endif
