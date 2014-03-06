#ifndef _CW_SHMDEFINE_H_
#define _CW_SHMDEFINE_H_

#if defined (_WIN32_)
#define INVALID_SM_HANDLE ((void*)0)
#elif defined (_LINUX64_)
#define INVALID_SM_HANDLE (-1)
#endif

struct SHMHead 
{
	SM_KEY			m_Key;
	unsigned int	m_Size;

};
#endif