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
	
	return 1;
}
