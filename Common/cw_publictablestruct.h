#ifndef CW_PUBLICTABLESTRUCT_H
#define CW_PUBLICTABLESTRUCT_H

#include "cw_commondefine.h"
#include "cw_clearserializer.h"

struct TABLE_SCRIPT
{
	int	  m_ID;
	char* m_ScriptFileName;
	void MapData(CSerializer& s)
	{
		s << m_ID;
		s << m_ScriptFileName;
	}
	TABLE_SCRIPT(){ CClearSerializer s; MapData(s); }
	bool operator>(int nID){ return m_ID > nID; }
	bool operator==(int nID){ return m_ID == nID; }
	bool operator>=(const TABLE_SCRIPT& val){ return m_ID == val.m_ID; }
};
#endif