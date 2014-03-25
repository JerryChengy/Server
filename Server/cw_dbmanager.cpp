#include "cw_dbmanager.h"
#include "cw_mysqlwrap.h"
#include "cw_serveriniset.h"
#include "cw_dboperatormanager.h"
#include "cw_templatemanager.h"

SINGLETONG_IMPLEMENTION(CDBManager)

	bool CDBManager::Init()
{	
	new CTemplateManager;
	new CDBOperatorManager;
	bool bRet;
	bRet = CTemplateManager::GetSingleton().RegisterAll();
	if (!bRet)
	{
		return false;
	}
	bRet = CDBOperatorManager::GetSingleton().RegisterAll();
	if (!bRet)
	{
		return false;
	}
	bRet = CDBOperatorManager::GetSingleton().InitAll(CTemplateManager::GetSingleton(), 
													CServerIniSet::GetSingleton().m_DB.m_IP,
													CServerIniSet::GetSingleton().m_DB.m_UserName,
													CServerIniSet::GetSingleton().m_DB.m_Password,
													CServerIniSet::GetSingleton().m_DB.m_DBName,
													CServerIniSet::GetSingleton().m_DB.m_Port);
	if (!bRet)
	{
		return false;
	}
}

bool CDBManager::SaveHumanData( const HumanData& data )
{
	CDBOperatorTemplate* pDBOperator = CDBOperatorManager::GetDBOperator("opt_human");
	if (!pDBOperator)
	{
		return false;
	}
	pDBOperator->Execute(&data);
}

bool CDBManager::LoadHumanData( HumanData& data )
{
	
}
