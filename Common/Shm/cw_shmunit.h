#ifndef CW_SHMUNIT_H
#define CW_SHMUNIT_H
#include "cw_shmutil.h"

struct SMUHead 
{
	int			m_Index;
	char		m_Flag;
	void		CleanUp()
	{
		m_Index = -1;
		m_Flag = SM_FREE;
	}
	SMUHead(){ CleanUp(); }
};

template<typename T>
class SMUnit
{
public:	

	void	ReadData(T& data)
	{
		_LockForRead();
		data = m_Data;
		_UnLock();
	}

	void	WriteData(const T& data)
	{
		_LockForWrite();
		m_Data = data;
		_UnLock();
	}

private:
	void		_LockForRead()
	{
		sm_lock(m_Head.m_Flag, SM_ME_READ);
	}

	void		_LockForWrite()
	{
		sm_lock(m_Head.m_Flag, SM_ME_WRITE);
	}

	void		_UnLock()
	{
		sm_unlock(m_Head.m_Flag);
	}
private:
	SMUHead		m_Head;
	T			m_Data;
};
#endif