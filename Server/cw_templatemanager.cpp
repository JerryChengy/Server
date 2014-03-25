#include "cw_templatemanager.h"

SINGLETONG_IMPLEMENTION(CTemplateManager);

CTemplateManager::CTemplateManager()
{
	m_pTemplateArray = 0;
	m_TemplateCount = 0;
	m_MaxTemplateCount = 0;
}

CTemplateManager::~CTemplateManager()
{
	SAFE_DELETEARRAY(m_pTemplateArray);
}

bool CTemplateManager::Register( const char* pTemplateName, CDBTemplate* pTemplate, int iDataLen )
{
	if (!pTemplateName || !pTemplate)
	{
		return false;
	}
	if (m_TemplateCount >= m_MaxTemplateCount)
	{
		if (!_Resize())
		{
			return true;
		}
	}
	m_pTemplateArray[m_TemplateCount] = *pTemplate;
	pTemplate->SetInfo(pTemplateName, iDataLen);
	m_TemplateCount++;
}

bool CTemplateManager::_Resize()
{
	int nNewMaxCount = m_MaxTemplateCount + DB_TEMPLATE_INC_COUNT;
	CDBTemplate* pNewTemplateArray = new CDBTemplate[nNewMaxCount];
	if (!pNewTemplateArray)
	{
		return false;
	}
	if (m_TemplateCount > 0)
	{
		memcpy(pNewTemplateArray, m_pTemplateArray, sizeof(CDBTemplate)*m_TemplateCount);
	}
	SAFE_DELETEARRAY(m_pTemplateArray);
	m_pTemplateArray = pNewTemplateArray;
	m_MaxTemplateCount = nNewMaxCount;
	return true;
}

bool CTemplateManager::RegisterAll()
{
	CDBTemplateStruct HumanTemplate;
	HumanTemplate.RegInt(TRUE, "ID", TRUE, 0, FALSE, TRUE);
	HumanTemplate.RegInt(FALSE, "Level", TRUE, 0, FALSE, FALSE);
	Register("Human", &HumanTemplate, sizeof(HumanTemplate));
}
