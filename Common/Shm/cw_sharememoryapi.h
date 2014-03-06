#ifndef CW_SHAREMEMORYAPI_H
#define CW_SHAREMEMORYAPI_H
#include "cw_commondefine.h"


namespace ShareMemAPI
{
	SM_Handle	CreateShareMem(SM_KEY Key, unsigned int Size);

	SM_Handle	OpenShareMem(SM_Handle handle);

	char*		MapShareMem(SM_Handle handle);

	void		UnMapShareMem(char* MemoryPtr);

	void		CloseShareMem(SM_Handle handle);
}
#endif
