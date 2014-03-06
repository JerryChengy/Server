#include "cw_clienthandler.h"
#include "cw_connection.h"
#include "cw_log.h"
#include "cw_tools.h"
#include "cw_serverconnection.h"
#include "cw_csmonster.h"
#include "cw_scmonster.h"

int SCMonsterPacketHandler(CPacket* pPacket, CConnection* pConnection)
{
	CSCMonsterPacket* pMonsterPacket = static_cast<CSCMonsterPacket*>(pPacket);
	const HumanData& humanData = pMonsterPacket->GetHumanData();
	LOG_DEBUG("SCTestPacketHandler OK, Num is %d, Str is %s, Human: ID[%d], Sex[%d], Name[%s]", 
		pMonsterPacket->GetNum(), 
		pMonsterPacket->GetStr(),
		humanData.m_ID,humanData.m_Sex, humanData.m_Name
		);
	return 1;
}
