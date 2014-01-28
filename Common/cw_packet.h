#ifndef CW_PACKET_H
#define CW_PACKET_H
#include "cw_packetdefine.h"
#include "cw_singleton.h"
#include "cw_socketbuff.h"

class CPacket
{
public:

	virtual void CleanUp(){}
	virtual short GetPacketID(){ return EM_PACKET_TYPE_INVALID; }
	virtual bool	MapData(){ return true; }

	bool PeekBuff(void* pData, int iLen);

	void SetBuff(CSocketBuff* pBuff){ m_pBuff = pBuff; }

	void SetIsSend(bool bSend){ m_bSend = bSend; }
protected:
	bool	m_bSend;
	CSocketBuff*	m_pBuff;
private:
	
	
};
#define BEGINPEEKBUF bool bRet;if (m_bSend){ int iPacketHead = PACKET_HEAD;\
m_pBuff->Fill(static_cast<char*>(static_cast<void*>(&iPacketHead)), sizeof(iPacketHead));\
short iPacketID = GetPacketID();\
m_pBuff->Fill(static_cast<char*>(static_cast<void*>(&iPacketID)), sizeof(iPacketID));\
}

#define ENDPEEKBUF return true;
#define PEEKBUF(m_Data) bRet = PeekBuff(&m_Data, sizeof(m_Data)); \
	if (!bRet)\
{\
	return false;\
}
class CPacketFactory: public Singleton<CPacketFactory>
{
public:
	virtual CPacket* GetPacket(){ return m_pPacket; }
	virtual void	DoCreate(){  }
protected:
	CPacket*	m_pPacket;
private:
	
};
#endif