#include "cw_tableset.h"
SINGLETONG_IMPLEMENTION(CTableSet);

bool CTableSet::Init()
{
	if (!m_Test.Load("./tables/test.tab"))
	{
		return false;
	}	
	if (!m_Script.Load("./Lua/script.tab"))
	{
		return false;
	}	
	return true;
}
