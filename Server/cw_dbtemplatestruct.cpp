#include "cw_dbtemplatestruct.h"
#include "cw_assert.h"
#include "cw_tools.h"

CDBTemplateStruct::CDBTemplateStruct()
{
	m_pColumnInfo = 0;
	m_ColumnInfoCount = 0;
	m_MaxColumnInfoCount = 0;
	m_CurOffset = 0;
}

CDBTemplateStruct::~CDBTemplateStruct()
{
	SAFE_DELETEARRAY(m_pColumnInfo);
}

bool CDBTemplateStruct::_Resize()
{
	int nNewMaxCount = m_MaxColumnInfoCount + DB_COLUMN_INC_COUNT;
	ColumnInfo* pColumnInfoArray = new ColumnInfo[nNewMaxCount];
	if (!pColumnInfoArray)
	{
		return false;
	}
	if (m_ColumnInfoCount > 0)
	{
		memcpy(pColumnInfoArray, m_pColumnInfo, m_ColumnInfoCount);
	}
	SAFE_DELETEARRAY(m_pColumnInfo);
	m_pColumnInfo = pColumnInfoArray;
	m_MaxColumnInfoCount = nNewMaxCount;
	return true;
}

bool CDBTemplateStruct::RegInt( BOOL Primary, const char* pName, BOOL NewColumn, int Default, 
									BOOL IsUnsigned, BOOL IsIndex, 	BOOL IsEncrypt, const char* pEnctyptKey )
{	
	if (FindColumn(pName))
	{
		Assert(false);
		return false;
	}
	if (IsFull() && !_Resize())
	{
		Assert(false);
		return false;
	}
	ColumnInfo& ci = m_pColumnInfo[m_ColumnInfoCount];
	ci.m_Type = EM_TYPE_DB_COLUMN_INT;
	ci.m_Len = sizeof(int);
	ci.m_Pos = m_CurOffset;
	ci.m_Primary = Primary;
	ci.m_IsUnsigned = IsUnsigned;
	ci.m_NewColumn = NewColumn;
	ci.m_pTemplate = 0;
	ci.m_IsIndex = IsIndex;
	ci.m_IsEncrypt = IsEncrypt;

	CTools::Strcpy(ci.m_Name, pName, sizeof(ci.m_Name));
	std::string strName = pName;
	m_HashColumnInfo[strName] = &ci;
	if (IsEncrypt)
	{
		CTools::Strcpy(ci.m_EncryptKey, pEnctyptKey, sizeof(ci.m_EncryptKey));
	}
	ci.m_DefaultLen = sizeof(Default);
	memcpy(ci.m_Default, &Default, ci.m_DefaultLen);
	CTools::Strcpy(ci.m_ColumnDefault, DB_SQL_FORMAT_DEFAULT_INT, sizeof(ci.m_ColumnDefault));
	m_CurOffset += (int)sizeof(int);
	m_ColumnInfoCount++;
}

bool CDBTemplateStruct::FindColumn( const char* pName )
{
	if (!pName)
	{
		return false;
	}
	return m_HashColumnInfo.Find(pName);
}
