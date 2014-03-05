#ifndef CW_CONNECTIONMANAGER_H
#define CW_CONNECTIONMANAGER_H
#include "cw_commondefine.h"
#include "cw_singleton.h"
#include "cw_lock.h"
class CConnection;
class CConnectionManager: public Singleton<CConnectionManager>
{
public:
	CConnectionManager();

	bool				Init();

	CConnection*		AddConn(SOCKET socket);

	void				DelConn( SOCKET socket );

	CConnection*		GetConn(SOCKET socket);

	int					GetMaxConns(){ return m_MaxConns; }

	void				ProcessNetData();


protected:
private:
	CConnection*		m_ConnectionSet;
	int					m_ConnCount;
	int					m_MaxConns;
	CLock				m_Lock;
};

#endif

