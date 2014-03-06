#include "cw_tableset.h"
SINGLETONG_IMPLEMENTION(CTableSet);

bool CTableSet::Init()
{
	if (!m_PublicScript.Load("../../Public/Script/script.tab"))
	{
		return false;
	}	
	return true;
}
