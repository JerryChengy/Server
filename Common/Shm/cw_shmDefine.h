#ifndef _CW_SHMDEFINE_H_
#define _CW_SHMDEFINE_H_

#if defined (_WIN32_)
#define INVALID_SM_HANDLE ((void*)0)
#elif defined (_LINUX64_)
#define INVALID_SM_HANDLE (-1)
#endif


struct SHMHead 
{
	SM_KEY		m_Key;
	UINT		m_Size;
	void		CleanUp()
	{
		m_Key = -1;
		m_Size = 0;
	}
	SHMHead()
	{
		CleanUp();
	}
};
#endif