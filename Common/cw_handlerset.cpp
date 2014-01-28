#include "cw_handlerset.h"

SINGLETONG_IMPLEMENTION(CPacketHandlerSet)



FuncHandler CPacketHandlerSet::GetHandler( PacketID packetid )
{
	if (packetid < 0 || packetid >= EM_PACKET_TYPE_NUMBER)
	{
		return 0;
	}
	return m_pHandlerSet[packetid];
}


bool CPacketHandlerSet::IsToMePacket(int iPacketID)
{
	if (iPacketID < 0 || iPacketID >= EM_PACKET_TYPE_NUMBER)
	{
		return false;
	}
	if (m_pHandlerSet[iPacketID])
	{
		return true;
	}
	return false;
}

CPacketHandlerSet::CPacketHandlerSet()
{
	for (int i=0;i<EM_PACKET_TYPE_NUMBER;++i)
	{
		m_pHandlerSet[i] = 0;
	}
}
