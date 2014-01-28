#ifndef CW_SERVERINISET_H
#define CW_SERVERINISET_H
#include "cw_serverstructini.h"
#include "cw_singleton.h"

class CServerIniSet: public Singleton<CServerIniSet>
{
public:
	bool Init();

	
protected:
private:

public:
	INI_TEST m_Test;
	INI_SERVERNET m_ServerNet;
	
};

#define g_ServerIni (CServerIniSet::GetSingleton())
#endif