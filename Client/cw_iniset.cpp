#include "cw_iniset.h"
#include "cw_commondefine.h"
#include "cw_inireader.h"
#include "cw_assert.h"

SINGLETONG_IMPLEMENTION(CIniSet);

bool CIniSet::Init()
{
	new CIniReader;

	bool bRet = m_Shm.Load("../../Public/Config/config.ini", "SHM");
	if (!bRet)
	{
		Assert(false);
		return false;
	}	
	return true;
}
