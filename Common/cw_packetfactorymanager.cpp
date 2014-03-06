#include "cw_packetfactorymanager.h"
#include "cw_handlerset.h"
#include "cw_csmonster.h"
#include "cw_scmonster.h"

SINGLETONG_IMPLEMENTION(CPacketFactoryManager)
void CPacketFactoryManager::Init()
{
	FACTORY_REGISTER(EM_PACKET_TYPE_CSMONSTER, CCSMonsterPacketFactory);
	FACTORY_REGISTER(EM_PACKET_TYPE_SCMONSTER, CSCMonsterPacketFactory);
}

CPacket* CPacketFactoryManager::GeneratePacket(short sPacketId)
{
	if (m_pPacketFactory[sPacketId])
	{
		CPacket* pPacket = m_pPacketFactory[sPacketId]->GetPacket();
		pPacket->CleanUp();
		return pPacket;
	}
	return 0;	
}

CPacketFactoryManager::CPacketFactoryManager()
{
	for (int i=0;i<EM_PACKET_TYPE_NUMBER;++i)
	{
		m_pPacketFactory[i] = 0;
	}
}
