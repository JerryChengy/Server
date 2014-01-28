#ifndef CW_HANDLERSET_H
#define CW_HANDLERSET_H
#include "cw_commondefine.h"
#include "cw_commonhandler.h"
#include "cw_socketdef.h"
#include "cw_singleton.h"
#include "cw_packetdefine.h"
class CPacketHandlerSet: public Singleton<CPacketHandlerSet>
{
public:
	CPacketHandlerSet();
	void			Init();
	FuncHandler    GetHandler(PacketID packetid);
	bool			IsToMePacket(int iPacketID);

protected:
private:
	FuncHandler		m_pHandlerSet[EM_PACKET_TYPE_NUMBER];
};
#define REG_HANDLER(sPacketid, packetHandler) m_pHandlerSet[sPacketid] = packetHandler;
#endif