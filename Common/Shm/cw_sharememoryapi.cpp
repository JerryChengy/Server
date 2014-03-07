#include "cw_sharememoryapi.h"
#include "cw_SHMDefine.h"
#if defined (_LINUX64_)
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>
#elif defined (_WIN32_)
#include <WinBase.h>
#endif

namespace ShareMemAPI
{
	SM_Handle CreateShareMem( SM_KEY Key, unsigned int Size )
	{
#if defined (_LINUX64_)
		SM_Handle hd = shmget(Key, Size, IPC_CREAT|IPC_EXCL|0666);
		if (hd == INVALID_SM_HANDLE && errno == EEXIST)
		{
			hd = shmget(Key, 0, 0);
			if (INVALID_SM_HANDLE == hd && errno == EINVAL)
			{
				LOG_DEBUG("shmget handle = %d, key = %d, error: %d", hd, Key, errno);
			}
			shmid_ds buf;
			if (INVALID_SM_HANDLE == shmctl(hd, IPC_STAT, &buf))
			{
				LOG_DEBUG("getState handle = %d, key = %d, error: %d", hd, Key, errno);
			}
			else
			{
				LOG_DEBUG("attach: %d", buf.shm_nattch);
				if (buf.shm_nattch <= 0)
				{
					if (INVALID_SM_HANDLE == shmctl(hd, IPC_RMID, &buf))
					{
						LOG_DEBUG("Del shm handle = %d, key = %d, error: %d", hd, Key, errno);
					}
					else
					{
						hd = shmget(Key, Size, IPC_CREAT|IPC_EXCL|0666);
						if (INVALID_SM_HANDLE == hd)
						{
							LOG_DEBUG("Create New handle = %d, key = %d, error: %d", hd, Key, errno);
						}
					}
				}
			}
		}
		LOG_DEBUG("Create handle Successful = %d, key = %d", hd, key);
		return hd;
#elif defined (_WIN32_)
		char keybuf[64] = {};
		_snprintf(keybuf, sizeof(keybuf)-1, "%d", Key);
		return CreateFileMapping((HANDLE)0xFFFFFFFFFFFFFFFF, NULL, PAGE_READWRITE, 0, Size, (LPCWSTR)keybuf);
#endif
	}
	SM_Handle OpenShareMem( SM_Handle handle )
	{
#if defined (_LINUX64_)
		return shmget(key, Size, 0);
#elif defined (_WIN32_)
		char keybuf[64] = {};
		_snprintf(keybuf, sizeof(keybuf)-1, "%d", Key);
		return OpenFileMapping(FILE_MAP_ALL_ACCESS, TRUE, (LPCWSTR)keybuf);
#endif

	}

	char* MapShareMem( SM_Handle handle )
	{
#if defined (_LINUX64_)
		return (char*)shmat(handle, 0, 0);
#elif defined (_WIN32_)
		return (char*)MapViewOfFile(handle, FILE_MAP_ALL_ACCESS, 0, 0, 0);
#endif
	}

	void UnMapShareMem( char* MemoryPtr )
	{
#if defined (_LINUX64_)
		shmdt(MemoryPtr);
#elif defined (_WIN32_)
		UnmapViewOfFile(MemoryPtr);
#endif
	}

	void CloseShareMem( SM_Handle handle )
	{
#if defined (_LINUX64_)
		shmctl(handle, IPC_RMID, 0);
#elif defined (_WIN32_)
		CloseHandle(handle);
#endif
	}


}