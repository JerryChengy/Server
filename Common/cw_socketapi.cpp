#include "cw_commondefine.h"
#include "cw_socketapi.h"


unsigned int CSocketAPI::GetLeftRecvDataLen(SOCKET s)
{
	unsigned int arg = 0;
	::ioctlsocket(s, FIONREAD, (u_long*)&arg);
	return arg;
}

int CSocketAPI::SetIOMode( SOCKET s, bool bBlock )
{
	return ::ioctlsocket(s, FIONBIO, (u_long*)&bBlock);
}
