#ifndef CW_LOCK_H
#define CW_LOCK_H
#include "cw_commondefine.h"

class CLock
{
	CRITICAL_SECTION		m_cLock; //¹²ÏíËø±äÁ¿
public:
	CLock(){ InitializeCriticalSection(&m_cLock);}
	~CLock(){ DeleteCriticalSection(&m_cLock);}
	void Lock(){ EnterCriticalSection(&m_cLock);}
	void Unlock(){ LeaveCriticalSection(&m_cLock);}
	class Scoped
	{
		CLock&		m_Lock;
	public:		
		explicit Scoped(CLock & lock):m_Lock(lock){ m_Lock.Lock(); }
		explicit Scoped(CLock * lock):m_Lock(*lock){ m_Lock.Lock(); }
		~Scoped(){ m_Lock.Unlock(); }
	};
	
};

#endif