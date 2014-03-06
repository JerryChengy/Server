#include "cw_csmonster.h"
#include "cw_tools.h"

SINGLETONG_IMPLEMENTION(CCSMonsterPacketFactory)


	bool CCSMonsterPacket::MapData()
{
	BEGINPEEKBUF	
	PEEKBUF(m_Num);
	PEEKBUF(m_Str);
	PEEKBUF(m_HumanData);
	ENDPEEKBUF
}

void CCSMonsterPacket::SetStr( const char* pStr )
{
	if (!pStr)
	{
		return ;
	}
	CTools::Strcpy(m_Str, pStr, sizeof(m_Str));
}
