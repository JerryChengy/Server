#include "cw_commondefine.h"
#include "cw_serveriniset.h"
#include "cw_inireader.h"
#include "cw_assert.h"

SINGLETONG_IMPLEMENTION(CServerIniSet);

bool CServerIniSet::Init()
{
	new CIniReader;

	bool bRet = m_Test.Load("../Config/config.ini", "TEST");
	if (!bRet)
	{
		Assert(false);
		return false;
	}	

	bRet = m_ServerNet.Load("../Config/config.ini", "SERVER");
	if (!bRet)
	{
		Assert(false);
		return false;
	}	

	bRet = m_Shm.Load("../../Public/Config/config.ini", "SHM");
	if (!bRet)
	{
		Assert(false);
		return false;
	}	

	bRet = m_DB.Load("../Config/config.ini", "DB");
	if (!bRet)
	{
		Assert(false);
		return false;
	}	
	return true;
}
