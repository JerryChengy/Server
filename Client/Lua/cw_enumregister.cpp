#include "cw_luaenum.h"
#include "cw_packetdefine.h"

void		CScriptEnum::RegisterAll()
{
	BEGIN_REG_ENUM("EM_PACKET_TYPE");
	REG_ENUM(EM_PACKET_TYPE_CSMONSTER, "CSMONSTER");
	REG_ENUM(EM_PACKET_TYPE_SCMONSTER, "SCMONSTER");
	END_REG_ENUM
}
