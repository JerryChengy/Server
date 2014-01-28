#include "cw_serverhandler.h"
#include "cw_connection.h"
#include "cw_cspackettest.h"
#include "cw_log.h"
#include "cw_scpackettest.h"

int CSTestPacketHandler(CPacket* pPacket, CConnection* pConnection)
{
	if (!pConnection)
	{
		return 0;
	}
	CCSTestPacket* pCSTestPacket = static_cast<CCSTestPacket*>(pPacket);
	const HumanData& humanData = pCSTestPacket->GetHumanData();
	LOG_DEBUG("TestPacketHandler OK, Num is %d, Str is %s, Human: ID[%d], Sex[%d], Name[%s]", 
		pCSTestPacket->GetNum(), 
		pCSTestPacket->GetStr(),
		humanData.m_ID,humanData.m_Sex, humanData.m_Name
		);
	CSCTestPacket SCTestPacket;
	SCTestPacket.SetNum(1111);
	SCTestPacket.SetStr("wangningna");
	SCTestPacket.SetHumanData(humanData);
	pConnection->SendPacket(&SCTestPacket);
	return 1;
}
