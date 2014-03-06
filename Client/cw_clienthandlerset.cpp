#include "cw_clienthandler.h"
#include "cw_handlerset.h"

void CPacketHandlerSet::Init()
{
	REG_HANDLER(EM_PACKET_TYPE_SCMONSTER, &SCMonsterPacketHandler);
}
