#include "cw_connection.h"
#include "cw_packetdefine.h"
#include "cw_commonhandler.h"
#include "cw_packetfactorymanager.h"
#include "cw_packet.h"
#include "cw_time.h"
#include "cw_log.h"
#include "cw_serverconnection.h"
#include "cw_handlerset.h"
#include "cw_tools.h"
#include "cw_scriptinterface.h"
#include "cw_tableset.h"
#include "cw_luapacket.h"
#include "cw_csmonster.h"
#include "cw_scmonster.h"
#include "cw_iniset.h"
#include "cw_shmmanager.h"
#include "cw_shmplayer.h"

bool Init();
void Work();
void Exit();
int main()
{
	
	bool bRet = Init();
	if (!bRet)
	{
		return 0;
	}
	Work();
	Exit();
	return 0;
};
void Exit()
{
	SHMManager::GetSingleton().Exit();
}
void Work()
{	
	while (1)
	{	
		/*CCSMonsterPacket packet;
		packet.SetNum(512);
		packet.SetStr("hello world!");
		HumanData humanData;
		humanData.m_ID = 1234;
		humanData.m_Sex = 1;
		CTools::Strcpy(humanData.m_Name, "chengyao", sizeof(humanData.m_Name));
		packet.SetHumanData(humanData);
		SendPacket(&packet);*/
		/*int iRet = InitLuaPacketData(GetLuaPacketID("CSPlayer"));
		if (iRet == 0)
		{
		return ;
		}
		SetLuaPacketIData(1, 100);
		SetLuaPacketIData(2, 533);
		PacketHumanData data;
		data.m_Data.m_ID = 222;
		data.m_Data.m_Sex = 1;
		SetLuaPacketPData(3, &data);
		SendLuaPacket();*/
		//CServerConnection::GetSingleton().ProcessNetData();
		HumanData data;
		SHMPlayer::GetSingleton().GetPlayerData(data, 0);
		//LOG_DEBUG("sizeof data: %d", sizeof(data));
		LOG_DEBUG("shm human data: %d,  %d", data.m_ID, data.m_Sex);
		::Sleep(1000);
	}	
}
bool Init()
{
	new CTimeManager;
	new CLogManager;
	new CIniSet;
	new CTableSet;
	new CPacketHandlerSet;
	new CPacketFactoryManager;
	new CServerConnection;
	new CScriptInterface;
	CTimeManager::GetSingleton().Init();
	CLogManager::GetSingleton().Init();	
	bool bRet = CServerConnection::GetSingleton().Init();	
	if (!bRet)
	{
		return false;
	}
	if (!SCRIPTMANAGER.Init())
	{
		LOG_DEBUG("Lua Init Failed!");
		return 0;
	}
	bRet = CTableSet::GetSingleton().Init();
	if (!bRet)
	{
		return false;
	}
	bRet = CIniSet::GetSingleton().Init();
	if (!bRet)
	{
		return false;
	}
	if (!SHMManager::GetSingleton().Init())
	{
		return false;
	}
	
	return true;
}
