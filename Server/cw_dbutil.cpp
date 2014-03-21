#include "cw_dbutil.h"
#include "cw_tools.h"

const char* TableType2EngineName( EM_TYPE_DB_TABLE Type )
{
	switch (Type)
	{
	case EM_TYPE_DB_TABLE_MYISAM:
		{
			return "MyISAM";
		}		
		break;
	case EM_TYPE_DB_TABLE_INNODB:
		{
			return "InnoDB";
		}
		break;
	default:
		{
			LOG_DEBUG("TableType2EngineName invalid table type: %d", Type);
			return NULL_STR;
		}
		break;
	}
	return NULL_STR;
}

EM_TYPE_DB_TABLE EngineName2TableType( const char* pName )
{
	if (!pName)
	{
		return EM_TYPE_DB_TABLE_INVALID;
	}
	for (int i=0;i<EM_TYPE_DB_TABLE_COUNT;++i)
	{
		if (CTools::Stricmp(TableType2EngineName((EM_TYPE_DB_TABLE)i), pName) == 0)
		{
			return (EM_TYPE_DB_TABLE)i;
		}
	}
	return EM_TYPE_DB_TABLE_INVALID;
}

const char* GetCollateFlag( EM_TYPE_DB_COLUMN Type )
{
	switch (Type)
	{
	case EM_TYPE_DB_COLUMN_VARCHAR:
	case EM_TYPE_DB_COLUMN_CHAR:
		{
			return "BINARY";
		}
		break;
	}
	return NULL_STR;
}

int TableTypeCompare( EM_TYPE_DB_TABLE Type, const char* pName )
{
	if (!pName)
	{
		return 0;
	}
	const char* pTypeName = TableType2EngineName(Type);
	return CTools::Stricmp(pTypeName, pName);
}

BOOL ColumnType2FiledName( EM_TYPE_DB_COLUMN Type, int MaxLen, BOOL IsUnsigned, BOOL IsEncrypt, char pResult[DB_COLUMN_TYPENAME_MAX_LEN] )
{
	if (!pResult)
	{
		return FALSE;
	}
	if (IsEncrypt)
	{
		CTools::Snprintf(pResult, DB_COLUMN_TYPENAME_MAX_LEN, "VARBINARY(32)");
	}
	switch (Type)
	{
	case EM_TYPE_DB_COLUMN_BYTE:
		{
			if (IsUnsigned)
			{
				CTools::Snprintf(pResult, DB_COLUMN_TYPENAME_MAX_LEN, "TINYINT UNSIGNED");
			}
			else
			{
				CTools::Snprintf(pResult, DB_COLUMN_TYPENAME_MAX_LEN, "TINYINT");
			}
			return TRUE;
		}
		break;
	case EM_TYPE_DB_COLUMN_SHORT:
		{
			if (IsUnsigned)
			{
				CTools::Snprintf(pResult, DB_COLUMN_TYPENAME_MAX_LEN, "SMALLINT UNSIGNED");
			}
			else
			{
				CTools::Snprintf(pResult, DB_COLUMN_TYPENAME_MAX_LEN, "SMALLINT");
			}
			return TRUE;
		}
		break;
	case EM_TYPE_DB_COLUMN_INT:
		{
			if (IsUnsigned)
			{
				CTools::Snprintf(pResult, DB_COLUMN_TYPENAME_MAX_LEN, "INT UNSIGNED");
			}
			else
			{
				CTools::Snprintf(pResult, DB_COLUMN_TYPENAME_MAX_LEN, "INT");
			}
			return TRUE;
		}
		break;
	case EM_TYPE_DB_COLUMN_INT:
		{
			if (IsUnsigned)
			{
				CTools::Snprintf(pResult, DB_COLUMN_TYPENAME_MAX_LEN, "BIGINT UNSIGNED");
			}
			else
			{
				CTools::Snprintf(pResult, DB_COLUMN_TYPENAME_MAX_LEN, "BIGINT");
			}
			return TRUE;
		}
		break;
	case EM_TYPE_DB_COLUMN_FLOAT:
		{
			if (IsUnsigned)
			{
				CTools::Snprintf(pResult, DB_COLUMN_TYPENAME_MAX_LEN, "FLOAT UNSIGNED");
			}
			else
			{
				CTools::Snprintf(pResult, DB_COLUMN_TYPENAME_MAX_LEN, "FLOAT");
			}
			return TRUE;
		}
		break;
	case EM_TYPE_DB_COLUMN_DOUBLE:
		{
			if (IsUnsigned)
			{
				CTools::Snprintf(pResult, DB_COLUMN_TYPENAME_MAX_LEN, "DOUBLE UNSIGNED");
			}
			else
			{
				CTools::Snprintf(pResult, DB_COLUMN_TYPENAME_MAX_LEN, "DOUBLE");
			}
			return TRUE;
		}
		break;
	case EM_TYPE_DB_COLUMN_VARCHAR:
		{
			CTools::Snprintf(pResult, DB_COLUMN_TYPENAME_MAX_LEN, "VARCHAR(%d)", MaxLen);
			return TRUE;
		}
		break;
	case EM_TYPE_DB_COLUMN_CHAR:
		{
			CTools::Snprintf(pResult, DB_COLUMN_TYPENAME_MAX_LEN, "CHAR(%d)", MaxLen);
			return TRUE;
		}
		break;
	
	case EM_TYPE_DB_COLUMN_BLOB:
		{
			CTools::Snprintf(pResult, DB_COLUMN_TYPENAME_MAX_LEN, "BLOB");
			return TRUE;
		}
		break;
	case EM_TYPE_DB_COLUMN_LONGBLOB:
		{
			CTools::Snprintf(pResult, DB_COLUMN_TYPENAME_MAX_LEN, "LONGBLOB");
			return TRUE;
		}
		break;
	default:
		{
			LOG_DEBUG("Invalid Column Type = %d", Type);
			return FALSE;
		}
		break;
	}
	return TRUE;
}
