#ifndef CW_DBTEMPLATE_STRUCT_H
#define CW_DBTEMPLATE_STRUCT_H
#include "cw_dbtemplate.h"
#include "cw_hashlist.h"
class CMemoryIO;
class CDBTemplateStruct;
typedef tony::THashList<ColumnInfo*> CIHashList;
class CDBTemplateStruct: public CDBTemplate
{
public:
	CDBTemplateStruct();
	~CDBTemplateStruct();
public:

protected:
private:
	bool	_Resize();
	bool	RegInt(BOOL Primary, const char* pName, BOOL NewColumn,
					int Default, BOOL IsUnsigned,  BOOL IsIndex=FALSE,
					BOOL IsEncrypt=FALSE, const char* pEnctyptKey=0);
	bool	FindColumn(const char* pName);
	bool	IsFull(){ return m_ColumnInfoCount >= m_MaxColumnInfoCount; }
private:
	ColumnInfo*			m_pColumnInfo;
	int					m_ColumnInfoCount;
	int					m_MaxColumnInfoCount;
	CIHashList			m_HashColumnInfo;
	int					m_CurOffset;
};
#endif