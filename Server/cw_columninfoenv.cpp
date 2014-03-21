#include "cw_columninfoenv.h"


BOOL CColumnInfoEnv::PushColumnInfo( ColumnInfo* pInfo )
{
	if (!pInfo)
	{
		return FALSE;
	}
	if (m_ColumnInfoStackCount == MAX_COLUMN_STACK_SIZE)
	{
		return FALSE;
	}
	m_pColumnInfoStack[m_ColumnInfoStackCount++] = pInfo;
	return TRUE;
}

BOOL CColumnInfoEnv::PopColumnInfo()
{
	if (m_ColumnInfoStackCount <= 0)
	{
		return FALSE;
	}
	else
	{
		--m_ColumnInfoStackCount;
		return True;
	}
}

const char* CColumnInfoEnv::GetColumnFullName()
{
	if (m_ColumnNameValid)
	{
		return m_ColumnName;
	}
	if (m_pColumnInfo == 0)
	{
		return NULL_STR;
	}
	ZEROMEM(m_ColumnName);
	if (m_ColumnInfoStackCount == 0)
	{
		return m_pColumnInfo->m_Name;
	}
	for (int i=0;i<m_ColumnInfoStackCount;++i)
	{
		CTools::Strcat(m_ColumnName, m_pColumnInfoStack[i]->m_Name, sizeof(m_ColumnName));
		CTools::Strcat(m_ColumnName, DB_COLUMN_NAME_SPLIT, sizeof(m_ColumnName));
	}
	CTools::Strcat(m_ColumnName, m_pColumnInfo->m_Name, sizeof(m_ColumnName));
	m_ColumnNameValid = TRUE;
	return m_ColumnName;
}


const char* CColumnInfoEnv::GetColumnTypeName()
{
	if (m_pColumnInfo == 0)
	{
		return NULL_STR;
	}
	if (ColumnType2FiledName(m_pColumnInfo->m_Type,
							m_pColumnInfo->m_Len,
							m_pColumnInfo->m_IsUnsigned,
							IsEncrypt(),
							m_ColumnTypeName) == FALSE)
	{
		return NULL_STR;
	}
	return m_ColumnTypeName;

}

const char* CColumnInfoEnv::GetColumnDefault()
{
	if (m_pColumnInfo == 0)
	{
		return NULL_STR;
	}
	if (m_pColumnInfo->m_ColumnDefault == 0)
	{
		return NULL_STR;
	}
	if (IsEncrypt())
	{
		return NULL_STR;
	}
	return m_pColumnInfo->m_ColumnDefault;
}

const char* CColumnInfoEnv::GetColumnPrimary()
{
	if (m_pColumnInfo == 0)
	{
		return NULL_STR;
	}
	if (m_pColumnInfo->m_Primary == FALSE)
	{
		return NULL_STR;
	}
	return DB_SQL_PRIMARY_KEY;
}

BOOL CColumnInfoEnv::IsIndex()
{
	
	if (m_pColumnInfo == 0)
	{
		return FALSE;
	}
	if (!m_pColumnInfo->m_IsIndex)
	{
		return FALSE;
	}
	for (int i=0;i<m_ColumnInfoStackCount;;++i)
	{
		if (m_pColumnInfo[i].m_IsIndex == FALSE)
		{
			return FALSE;
		}
	}
	return TRUE;
}

BOOL CColumnInfoEnv::IsEncrypt()
{
	if (m_pColumnInfo == 0)
	{
		return FALSE;
	}
	if (!m_pColumnInfo->m_IsEncrypt)
	{
		return FALSE;
	}
	for (int i=0;i<m_ColumnInfoStackCount;;++i)
	{
		if (m_pColumnInfo[i].m_IsEncrypt == FALSE)
		{
			return FALSE;
		}
	}
	return TRUE;
}
