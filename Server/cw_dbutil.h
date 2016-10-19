#ifndef CW_DBUTIL_H
#define CW_DBUTIL_H

#include "cw_dbheader.h"

const char* TableType2EngineName(EM_TYPE_DB_TABLE Type);
EM_TYPE_DB_TABLE EngineName2TableType(const char* pName);
const char* GetCollateFlag(EM_TYPE_DB_COLUMN Type);
int TableTypeCompare(EM_TYPE_DB_TABLE Type, const char* pName);
BOOL	ColumnType2FiledName(EM_TYPE_DB_COLUMN Type, int MaxLen, BOOL IsUnsigned, BOOL IsEncrypt, char pResult[DB_COLUMN_TYPENAME_MAX_LEN]);
#endif