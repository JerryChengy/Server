#ifndef CW_SOCKETAPI_H
#define CW_SOCKETAPI_H
#include "cw_commondefine.h"
class CSocketAPI
{
public:
	static unsigned int GetLeftRecvDataLen(SOCKET s);
	static int SetIOMode(SOCKET s, bool bBlock);
protected:
private:
};


#endif