#ifndef CW_LOCK_H
#define CW_LOCK_H
#include <Windows.h>

class CLock
{
public:
	CLock(){ InitializeCriticalSection(&m_cLock);}
	~CLock(){ DeleteCriticalSection(&m_cLock);}
	void Lock(){ EnterCriticalSection(&m_cLock);}
	void Unlock(){ LeaveCriticalSection(&m_cLock);}
protected:
private:
	CRITICAL_SECTION		m_cLock; //¹²ÏíËø±äÁ¿
};

#endif