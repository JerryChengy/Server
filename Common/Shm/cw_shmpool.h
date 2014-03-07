#ifndef CW_SHMPOOL_H
#define CW_SHMPOOL_H
#include "cw_sharememoryapi.h"

template<typename T>
class CSHMPool
{
public:
	bool				Init(int Size){ return Size<=0?false:(m_Size=Size, true);}
	bool				Create(SM_KEY key)
	{
			int	nTotalSize = m_Size*sizeof(T);
			m_Handle = ShareMemAPI::CreateShareMem(key, nTotalSize);
			if (m_Handle == INVALID_HANDLE_VALUE)
			{
				return false;
			}
			char* pHead = ShareMemAPI::MapShareMem(m_Handle);
			if (!pHead)
			{
				return false;
			}
			m_DataPtr = new T*[m_Size];
			for (int i=0;i<m_Size;++i)
			{
				m_DataPtr[i] = (T*)(void*)pHead + i*sizeof(T);
			}
			return true;
	}
	void				Close()
	{
		ShareMemAPI::CloseShareMem(m_Handle);
	}

	T*					GetSMUByIndex(int iIndex)
	{
		if (iIndex < 0 || iIndex >= m_Size)
		{
			return 0;
		}
		return m_DataPtr[iIndex];
	}
protected:
private:
	SM_Handle			m_Handle;
	int					m_Size;
	T**					m_DataPtr;
};

#endif