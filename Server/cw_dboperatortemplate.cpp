#include "cw_dboperatortemplate.h"

CDBOperatorTemplate::CDBOperatorTemplate()
{

}

CDBOperatorTemplate::~CDBOperatorTemplate()
{

}

BOOL CDBOperatorTemplate::Init( CTemplateManager* pTemplateManager, CMysqlWrap* pMysql )
{
	if (!pTemplateManager || !pMysql)
	{
		return FALSE;
	}
	m_pTableInfo
}
