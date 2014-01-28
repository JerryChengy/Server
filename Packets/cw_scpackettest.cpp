#include "cw_scpackettest.h"
#include "cw_tools.h"

SINGLETONG_IMPLEMENTION(CSCTestPacketFactory)


bool CSCTestPacket::MapData()
{
	BEGINPEEKBUF	
	PEEKBUF(m_Num);
	PEEKBUF(m_Str);
	PEEKBUF(m_HumanData);
	ENDPEEKBUF
}


void CSCTestPacket::SetStr( const char* pStr )
{
	if (!pStr)
	{
		return ;
	}
	CTools::Strcpy(m_Str, pStr, sizeof(m_Str));
}
