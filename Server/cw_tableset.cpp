#include "cw_tableset.h"
#include "cw_tablebase.h"
SINGLETONG_IMPLEMENTION(CTableSet);

bool CTableSet::Init()
{
	new CLineDataDisposer;
	if (!m_Test.Init("./tables/test.tab"))
	{
		return false;
	}	
	if (!m_Script.Init("./Lua/script.tab"))
	{
		return false;
	}	
	if (!TABLE_BASE::smTableGood)
	{
		Assert(false);
		return false;
	}
	return true;
}