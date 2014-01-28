#ifndef CW_SOCKETSERVER_H
#define CW_SOCKETSERVER_H
#include "cw_commondefine.h"
#include "cw_socketdef.h"
#include "cw_singleton.h"
class CConnection;
typedef void (*ConnCallBack)(CConnection* pConn);
void ProcessInput(CConnection* pConn);
void OnDelConn(CConnection* pConn);
class CSocketServer: public Singleton<CSocketServer>
{
public:

	void				Init(short port);

	void				SetProcessInputFunc(ConnCallBack func){ m_FuncProcessInput = func; }

	ConnCallBack		GetProcessInputFunc(){ return m_FuncProcessInput; }

	void				SetDelConnFunc(ConnCallBack func){ m_FuncDelConn = func; }

	ConnCallBack		GetDelConnFunc(){ return m_FuncDelConn; }

	void				AcceptConn();

	void				ProcessNetData();
	bool				Listen();
	void				Work();
protected:
private:
	short		m_Port;	//¶Ë¿ÚºÅ
	ConnCallBack	m_FuncProcessInput;
	ConnCallBack	m_FuncDelConn;
	int			m_CurrentID;
	SOCKET		m_ListenSocket;
	SOCKADDR_IN m_LocalAddr;	
	FD_SET		m_fdRead;
};
#endif
