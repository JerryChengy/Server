#include "cw_cspackettest.h"
#include "cw_tools.h"

SINGLETONG_IMPLEMENTION(CCSTestPacketFactory)


	bool CCSTestPacket::MapData()
{
	BEGINPEEKBUF	
	PEEKBUF(m_Num);
	PEEKBUF(m_Str);
	PEEKBUF(m_HumanData);
	ENDPEEKBUF
}

void CCSTestPacket::SetStr( const char* pStr )
{
	if (!pStr)
	{
		return ;
	}
	CTools::Strcpy(m_Str, pStr, sizeof(m_Str));
}
