#ifndef CW_TABLESTRUCT_H
#define CW_TABLESTRUCT_H
#include "cw_commondefine.h"
#include "cw_tablebase.h"


struct TABLE_SCRIPT: TABLE_BASE 
{
	char* m_ScriptFileName;
	void ReadTable()
	{
		In(m_ScriptFileName);		
	}
};

struct TABLE_TEST: TABLE_BASE
{	
	char* m_Name;
	int  m_Level;
	int  m_Hp;
	float  m_Mp;
	IntArray m_Title;
	void ReadTable()
	{
		In(m_Name);
		In(m_Level);
		In(m_Hp);
		In(m_Mp);
		In(m_Title);	
	}
	
};



#endif