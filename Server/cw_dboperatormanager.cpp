#include "cw_dboperatormanager.h"
#include "cw_tools.h"


static const int DB_DBOPERATOR_DATA_ENLARGE_COUNT = 64;
SINGLETONG_IMPLEMENTION(CDBOperatorManager);

CDBOperatorManager::CDBOperatorManager()
{
	m_DBOperatorCount = 0;
	m_pDBOperatorData = 0;
	m_DBOperatorDataLen = 0;
	m_pMysql = 0;
}

CDBOperatorManager::~CDBOperatorManager()
{
	for (int i=0;i<m_DBOperatorCount;++i)
	{
		SAFE_DELETE(m_pDBOperatorData[i].m_pDBOperator);
	}
	SAFE_DELETEARRAY(m_pDBOperatorData);
	m_DBOperatorDataLen = 0;
	m_DBOperatorCount = 0;
	SAFE_DELETE(m_pMysql);
}

bool CDBOperatorManager::Register( const char* pName, CDBOperator* pDBOperator )
{
	if (!pName)
	{
		return false;
	}
	if (!pDBOperator)
	{
		return false;
	}
	if (GetDBOperator(pName) != 0)
	{
		return false;
	}
	int NameLen = CTools::Strlen(pName) + 1;
	if (NameLen > DB_OPERATOR_NAME_MAX_LEN)
	{
		return false;
	}
	if (m_DBOperatorCount >= m_DBOperatorDataLen && _EnLarge() == false)
	{
		return false;
	}
	CTools::Strcpy(m_pDBOperatorData[m_DBOperatorCount].m_Name, pName, sizeof(m_pDBOperatorData[m_DBOperatorCount].m_Name));
	m_pDBOperatorData[m_DBOperatorCount].m_pDBOperator = pDBOperator;
	m_DBOperatorCount++;
	pDBOperator->SetName(pName);
	return true;
}

bool CDBOperatorManager::_EnLarge()
{
	int NewDataLen = m_DBOperatorDataLen + DB_DBOPERATOR_DATA_ENLARGE_COUNT;
	DBOperatorData* pNewDBOperatorData = new DBOperatorData[NewDataLen];
	if (m_DBOperatorCount > 0)
	{
		memcpy(pNewDBOperatorData, m_pDBOperatorData, sizeof(DBOperatorData)*m_DBOperatorCount);
	}	
	m_DBOperatorDataLen = NewDataLen;
	SAFE_DELETEARRAY(m_pDBOperatorData);
	m_pDBOperatorData = pNewDBOperatorData;
	return true;
}

CDBOperator* CDBOperatorManager::GetDBOperator( const char* pName )
{
	if (!pName)
	{
		return 0;
	}
	for (int i=0;i<m_DBOperatorCount;++i)
	{
		if (CTools::Stricmp(m_pDBOperatorData[i].m_Name, pName) == 0)
		{
			return &m_pDBOperatorData[i];
		}		
	}
	return 0;
}

bool CDBOperatorManager::AdjustAll( CDBOperatorManager* pDBOperatorManager )
{
	return true;
}

bool CDBOperatorManager::PrepareAll()
{
	return true;
}

bool CDBOperatorManager::InitAll( CTemplateManager* pTemplateManager, const char* pIP, const char* pUser, const char* pPwd, const char* pInstance, int Port )
{
	if (!_InitMysqlWrap(pIP, pUser, pPwd, pInstance, Port))
	{
		return false;
	}
	for (int i=0;i<m_DBOperatorCount;++i)
	{
		if (m_pDBOperatorData[i].m_pDBOperator->Init(pTemplateManager, m_pMysql) == false)
		{
			return false;
		}
	}
	return true;
}

bool CDBOperatorManager::_InitMysqlWrap( const char* pIP, const char* pUser, const char* pPwd, const char* pInstance, int Port )
{
	m_pMysql = new CMysqlWrap();
	if (!m_pMysql)
	{
		return false;
	}
	bool bRes = m_pMysql->Connect(pIP, pUser, pPwd, pInstance, Port);
	if (!bRes)
	{
		return false;
	}
	return true;
}

bool CDBOperatorManager::WriteTo( CMemoryWriter )
{
	return true;
}

bool CDBOperatorManager::ReadFrom( CMemoryReader& Reader, int ProtocolVersion )
{
	return true;
}
