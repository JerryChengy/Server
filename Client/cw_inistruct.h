#ifndef CW_INISTRUCT_H
#define CW_INISTRUCT_H

#include "cw_inibase.h"


struct INI_SHM:INI_BASE 
{
	int m_Key;
	int m_Size;
	void ReadData()
	{
		Read("key", m_Key);
		Read("size", m_Size);
	}
};

#endif