#ifndef CW_TABLESTRUCT_H
#define CW_TABLESTRUCT_H
#include "cw_commondefine.h"
#include "cw_clearserializer.h"

struct TABLE_TEST
{	
	int	  m_ID;
	char* m_Name;
	int  m_Level;
	int  m_Hp;
	float  m_Mp;
	IntArray m_Title;
	void MapData(CSerializer& s)
	{
		s << m_ID;		
		s << m_Name;
		//s.Skip();
		s << m_Level;
		s << m_Hp;
		s << m_Mp;
		s << m_Title;
	}
	TABLE_TEST(){ CClearSerializer s; MapData(s); }
	bool operator>(int nID){ return m_ID > nID; }
	bool operator==(int nID){ return m_ID == nID; }
	bool operator>=(const TABLE_TEST& val){ return m_ID >= val.m_ID; }
};



#endif