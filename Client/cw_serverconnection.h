#ifndef CW_SERVERCONNECTION_H
#define CW_SERVERCONNECTION_H
#include "cw_connection.h"
#include "cw_singleton.h"

#define PORT 5050
typedef void (*ConnCallBack)(CConnection* pConn);
class CPacket;
class CServerConnection: public Singleton<CServerConnection>
{
public:
	bool					Init();
	void					SendPacket(CPacket* pPacket);
	void					ProcessNetData();
	static void					ProcessInput(CConnection* pConn);
	void					SetProcessInputFunc(ConnCallBack func);
	CSocketBuff*			GetSendBuff(){ return m_ServerConn.GetSendBuff(); }		
	CSocketBuff*			GetRecvBuff(){ return m_ServerConn.GetRecvBuff(); }
	void					CloseConn(){ m_ServerConn.Close(); }
	int						GetSocket(){ return m_ServerConn.GetSocket(); }
protected:
private:
	CConnection				m_ServerConn;
	ConnCallBack			m_FuncProcessInput;
};


void	SendLuaPacket();
void	SendPacket(CPacket* pPacket);
#endif