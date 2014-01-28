#include "cw_packet.h"
#include "cw_socketbuff.h"

SINGLETONG_IMPLEMENTION(CPacketFactory)

bool CPacket::PeekBuff( void* pData, int iLen )
{
	if (!m_bSend)
	{
		return m_pBuff->PeekBuff(static_cast<char *>(pData), iLen);
	}
	else
	{ 
		printf(static_cast<char*>(pData));		
		m_pBuff->Fill(static_cast<char *>(pData), iLen);
		return true;
	}
}
