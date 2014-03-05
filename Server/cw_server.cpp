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

CPlayer* g_Player = 0;


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

	CTimeManager::GetSingleton().Init();
	CLogManager::GetSingleton().Init();	

	if (!SCRIPTMANAGER.Init())
	{
		LOG_DEBUG("Lua Init Failed!");
		return 0;
	}
	/*if (!CLuaInterface::GetSingleton().Load("./Lua/test.lua"))
	{
	LOG_DEBUG("Lua Script Load Failed!");
	return 0;
	}
	if (!CLuaInterface::GetSingleton().Load("./Lua/test1.lua"))
	{
	LOG_DEBUG("Lua Script Load Failed!");
	return 0;
	}*/
	

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

	if (!SCRIPTMANAGER.Load())
	{
		return false;
	}
	g_Player = new CPlayer;
	g_Player->SetLevel(88);
	int iRet = SCRIPTMANAGER.CallScript(2, "Test", 34, 0);
	LOG_DEBUG("iRet: %d", iRet);
	//iRet = SCRIPTMANAGER.CallScript(2, "mul", 4, 3);
	//LOG_DEBUG("iRet: %d", iRet);
	

	bRet = CSocketServer::GetSingleton().Listen();
	if (!bRet)
	{
		return false;
	}
	/*LOG_DEBUG("port: %d, recvbuflen: %d, sendbuflen: %d", g_ServerIni.m_ServerNet.m_Port,
	g_ServerIni.m_ServerNet.m_ReceiveSocketBuffLen,
	g_ServerIni.m_ServerNet.m_SendSocketBuffLen);*/
	TABLE_TEST* pTestTable = Tables.m_Test.Row(1);
	if (pTestTable)
	{
		LOG_DEBUG("table test, nam: , level: %d, hp: %d, mp: %f, title: %d", /*pTestTable->m_Name,*/
			pTestTable->m_Level, pTestTable->m_Hp, 
			pTestTable->m_Mp, pTestTable->m_Title[0]);

	}
	
	return true;
}

void Work()
{
	while (1)
	{
		CSocketServer::GetSingleton().Work();
		::Sleep(10);
	}
}
int main()
{
	if (!Init())
	{
		return 0;
	}
	Work();	
	return 0;
};
