#include "cw_scmonster.h"
#include "cw_tools.h"

SINGLETONG_IMPLEMENTION(CSCMonsterPacketFactory)


bool CSCMonsterPacket::MapData()
{
	BEGINPEEKBUF	
	PEEKBUF(m_Num);
	PEEKBUF(m_Str);
	PEEKBUF(m_HumanData);
	ENDPEEKBUF
}


void CSCMonsterPacket::SetStr( const char* pStr )
{
	if (!pStr)
	{
		return ;
	}
	CTools::Strcpy(m_Str, pStr, sizeof(m_Str));
}
