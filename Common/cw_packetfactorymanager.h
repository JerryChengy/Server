#ifndef CW_PACKETFACTORY_MANAGER_H
#define CW_PACKETFACTORY_MANAGER_H
#include "cw_packetdefine.h"
#include "cw_singleton.h"

class CPacket;
class CPacketFactory;
class CPacketFactoryManager: public Singleton<CPacketFactoryManager>
{
public:
	CPacketFactoryManager();
	void Init();
	CPacket* GeneratePacket(short sPacketId);
protected:
private:
	CPacketFactory*		m_pPacketFactory[EM_PACKET_TYPE_NUMBER];
};


#define FACTORY_REGISTER(PacketId, ClassPacketFactory) if(CPacketHandlerSet::GetSingleton().IsToMePacket(PacketId)){\
m_pPacketFactory[PacketId] = new ClassPacketFactory;\
	ClassPacketFactory::GetSingleton().DoCreate();}

#endif