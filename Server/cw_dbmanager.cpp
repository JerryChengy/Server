#include "cw_dbmanager.h"
#include "cw_mysqlwrap.h"
#include "cw_serveriniset.h"

SINGLETONG_IMPLEMENTION(CDBManager)

	bool CDBManager::Init()
{
	m_pMysql = new CMysqlWrap;
	int nRet = m_pMysql->Connect(CServerIniSet::GetSingleton().m_DB.m_IP,
						CServerIniSet::GetSingleton().m_DB.m_Port,
						CServerIniSet::GetSingleton().m_DB.m_DBName,
						CServerIniSet::GetSingleton().m_DB.m_UserName,
						CServerIniSet::GetSingleton().m_DB.m_Password);
	if (nRet == 0)
	{
		return true;
	}
	return false;
}

bool CDBManager::SaveHumanData( const HumanData& data )
{

	
}

bool CDBManager::LoadHumanData( HumanData& data )
{
	
}
