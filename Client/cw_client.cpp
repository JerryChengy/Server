#include "cw_connection.h"
#include "cw_packetdefine.h"
#include "cw_commonhandler.h"
#include "cw_packetfactorymanager.h"
#include "cw_packet.h"
#include "cw_time.h"
#include "cw_log.h"
#include "cw_serverconnection.h"
#include "cw_cspackettest.h"
#include "cw_handlerset.h"
#include "cw_tools.h"
#include "cw_scpackettest.h"

bool Init();
void Work();
int main()
{
	
	bool bRet = Init();
	if (!bRet)
	{
		return 0;
	}
	Work();
	return 0;
};
void Work()
{	
	while (1)
	{	
		CCSTestPacket packet;
		packet.SetNum(512);
		packet.SetStr("hello world!");
		HumanData humanData;
		humanData.m_ID = 1234;
		humanData.m_Sex = 1;
		CTools::Strcpy(humanData.m_Name, "chengyao", sizeof(humanData.m_Name));
		packet.SetHumanData(humanData);
		SendPacket(&packet);
		CServerConnection::GetSingleton().ProcessNetData();
		::Sleep(10);
	}	
}
bool Init()
{
	new CTimeManager;
	new CLogManager;
	new CPacketHandlerSet;
	new CPacketFactoryManager;
	new CServerConnection;
	CTimeManager::GetSingleton().Init();
	CLogManager::GetSingleton().Init();	
	bool bRet = CServerConnection::GetSingleton().Init();	
	if (!bRet)
	{
		return false;
	}
	return true;
}
