#include "cw_serverhandler.h"
#include "cw_connection.h"
#include "cw_log.h"
#include "cw_csmonster.h"
#include "cw_scmonster.h"

int CSMonsterPacketHandler(CPacket* pPacket, CConnection* pConnection)
{
	if (!pConnection)
	{
		return 0;
	}
	CCSMonsterPacket* pCSMonsterPacket = static_cast<CCSMonsterPacket*>(pPacket);
	const HumanData& humanData = pCSMonsterPacket->GetHumanData();
	
	CSCMonsterPacket SCMonsterPacket;
	SCMonsterPacket.SetNum(1111);
	SCMonsterPacket.SetStr("wangningna");
	SCMonsterPacket.SetHumanData(humanData);
	pConnection->SendPacket(&SCMonsterPacket);
	return 1;
}
