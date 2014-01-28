#include "cw_clienthandler.h"
#include "cw_connection.h"
#include "cw_scpackettest.h"
#include "cw_log.h"
#include "cw_cspackettest.h"
#include "cw_tools.h"
#include "cw_serverconnection.h"

int SCTestPacketHandler(CPacket* pPacket, CConnection* pConnection)
{
	CSCTestPacket* pTestPacket = static_cast<CSCTestPacket*>(pPacket);
	const HumanData& humanData = pTestPacket->GetHumanData();
	LOG_DEBUG("SCTestPacketHandler OK, Num is %d, Str is %s, Human: ID[%d], Sex[%d], Name[%s]", 
		pTestPacket->GetNum(), 
		pTestPacket->GetStr(),
		humanData.m_ID,humanData.m_Sex, humanData.m_Name
		);
	return 1;
}
