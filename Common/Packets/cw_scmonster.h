#ifndef CW_SCPACKETTEST_H
#define CW_SCPACKETTEST_H

#include "cw_commondefine.h"
#include "cw_packet.h"
#include "cw_testdata.h"

class CSCMonsterPacket: public CPacket
{
public:
	CSCMonsterPacket(){ CleanUp(); }

	short GetPacketID(){ return EM_PACKET_TYPE_SCMONSTER; }

	void	CleanUp()
	{ 
		m_Num = -1; 
		memset(m_Str, 0, sizeof(m_Str));
		m_HumanData.CleanUp();
	}

	void	SetNum(int nNum){ m_Num = nNum; }
	int		GetNum(){ return m_Num; }

	bool	MapData();
	void	SetStr( const char* pStr );
	const char* GetStr(){ return m_Str; }

	const HumanData& GetHumanData(){ return m_HumanData; }
	void	SetHumanData(const HumanData& data){ m_HumanData = data; }
protected:
private:
	int			m_Num;
	char		m_Str[32];
	HumanData	m_HumanData;
};

class CSCMonsterPacketFactory: public CPacketFactory
{
public:
	void DoCreate(){ m_pPacket = new CSCMonsterPacket; }
protected:
private:
};
#endif