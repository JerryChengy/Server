#include "cw_handlerset.h"
#include "cw_serverhandler.h"

void CPacketHandlerSet::Init()
{
	REG_HANDLER(EM_PACKET_TYPE_CSMONSTER, &CSMonsterPacketHandler);
}
