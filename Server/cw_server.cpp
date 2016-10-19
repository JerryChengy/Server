#include "cw_socketserver.h"
#include "cw_connection.h"
#include "cw_packetdefine.h"
#include "cw_serverhandler.h"
#include "cw_connectionmanager.h"
#include "cw_packetfactorymanager.h"
#include "cw_packet.h"
#include "cw_handlerset.h"
#include "cw_time.h"
#include "cw_log.h"
#include "cw_serveriniset.h"
#include "cw_tableset.h"
#include "cw_scriptinterface.h"
#include "cw_tools.h"
#include "cw_player.h"
#include "cw_testdata.h"
#include "cw_shmmanager.h"
#include "cw_shmplayer.h"
#include "cw_dbmanager.h"

bool Init()
{
	new CTimeManager;
	new CLogManager;
	new CServerIniSet;
	new CTableSet;

	new CScriptInterface;

	new CPacketFactoryManager;
	new CPacketHandlerSet;
	new CConnectionManager;
	new CSocketServer;	
	new SHMManager;

	CTimeManager::GetSingleton().Init();
	CLogManager::GetSingleton().Init();	

	if (!SCRIPTMANAGER.Init())
	{
		LOG_DEBUG("Lua Init Failed!");
		return 0;
	}
	bool bRet = CServerIniSet::GetSingleton().Init();
	if (!bRet)
	{
		return false;
	}
	bRet = CTableSet::GetSingleton().Init();
	if (!bRet)
	{
		return false;
	}

	CSocketServer::GetSingleton().Init(g_ServerIni.m_ServerNet.m_Port);

	if (!SHMManager::GetSingleton().Init())
	{
		return false;
	}
	
	bRet = CSocketServer::GetSingleton().Listen();
	if (!bRet)
	{
		return false;
	}
	int iRet = SCRIPTMANAGER.CallScript(2, "Test", 34, 0);
	LOG_DEBUG("iRet: %d", iRet);
	/*while (1)
	{
		static int iii = 111;
		HumanData data;
		data.m_ID = iii++;
		data.m_Sex = 1;
		SHMPlayer::GetSingleton().SetPlayerData(data, 0);
		SLEEP(1000);
	}*/

	LOG_DEBUG("Init OK!");
	LOG_DEBUG("Listen...");
	return true;
}

void Work()
{
	while (1)
	{
		CSocketServer::GetSingleton().Work();
		SLEEP(10);
	}
}
void Exit()
{
	SHMManager::GetSingleton().Exit();
}
int main()
{
	if (!Init())
	{
		return 0;
	}
	Work();	
	Exit();
	return 0;
};

