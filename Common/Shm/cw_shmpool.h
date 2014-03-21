#ifndef CW_SHMPOOL_H
#define CW_SHMPOOL_H
#include "cw_sharememoryapi.h"
#include "cw_shmDefine.h"
#include "cw_assert.h"
#include "cw_log.h"

template<typename T>
class SHMPool
{
public:
	bool				Init(int Size){ return Size<=0?false:(m_Size=Size, true);}
	bool				Create(SM_KEY key)
	{
			UINT	uTotalSize = m_Size*sizeof(T) + sizeof(SHMHead);
			m_Handle = ShareMemAPI::CreateShareMem(key, uTotalSize);
			if (m_Handle == INVALID_SM_HANDLE)
			{
				return false;
			}
			char* pMemHead = ShareMemAPI::MapShareMem(m_Handle);
			if (!pMemHead)
			{
				return false;
			}
			m_DataPtr = new T*[m_Size];
			SHMHead* pSHMHead = (SHMHead*)(void*)pMemHead;
			LOG_DEBUG("client shm head addr: %p", pMemHead);
			pSHMHead->m_Key = key;
			pSHMHead->m_Size = m_Size;
			char* pDataHead = pMemHead + sizeof(SHMHead);
			for (int i=0;i<m_Size;++i)
			{
				m_DataPtr[i] = (T*)(void*)pDataHead + i*sizeof(T);
			}
			m_Key = key;
			return true;
	}
	bool				Attach(SM_KEY Key)
	{
		UINT	uTotalSize = m_Size*sizeof(T) + sizeof(SHMHead);
		m_Handle = ShareMemAPI::OpenShareMem(Key, uTotalSize);
		if (m_Handle == INVALID_SM_HANDLE)
		{
			return false;
		}
		char* pMemHead = ShareMemAPI::MapShareMem(m_Handle);
		if (!pMemHead)
		{
			return false;
		}
		LOG_DEBUG("server shm head addr: %p", pMemHead);
		SHMHead* pSHMHead = (SHMHead*)(void*)pMemHead;
		if (pSHMHead->m_Key != Key || pSHMHead->m_Size != m_Size)
		{
			Assert(false);
			return false;
		}
		char* pDataHead = pMemHead + sizeof(SHMHead);
		m_DataPtr = new T*[m_Size];
		for (int i=0;i<m_Size;++i)
		{
			m_DataPtr[i] = (T*)(void*)pDataHead + i*sizeof(T);
		}
		m_Key = Key;
		return true;
	}
	bool				Detach(){ return true; }
	void				Destroy()
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
	SM_KEY				m_Key;
	T**					m_DataPtr;
};

#endif