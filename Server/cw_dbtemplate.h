#ifndef CW_DBTEMPLATE_H
#define CW_DBTEMPLATE_H
#include "cw_dbheader.h"
class CTemplateManager;
class CColumnInfoEnv;
class CMemoryReader;
class CMemoryWriter;

class CDBTemplate
{
public:
	CDBTemplate(){};
	virtual ~CDBTemplate(){};
public:
	virtual EM_TYPE_TEMPLATE GetType();

	virtual BOOL Init(CTemplateManager* pTemplateManager) = 0;

	virtual EM_TYPE_SERIALIZE InitSerializeInfo() = 0;

	virtual BOOL GetColumnInfo(CColumnInfoEnv &Env) = 0;

	virtual BOOL BindStmtParam(char* pData, Mysql_Stmt * pStmt, EM_TYPE_BIND BindType) = 0;

	virtual BOOL BindPrimaryKey(char* pData, Mysql_Stmt *pStmt, EM_TYPE_BIND BindType) = 0;

	virtual BOOL SetPrimaryKey(char* pData, const char* pKey) = 0;
	virtual BOOL SetPrimaryKey(char* pData, const char* pKey, int KeyLen) = 0;
	virtual BOOL FillBindStmtParam(char* pData, const ColumnInfo* pColumnInfo, Mysql_Stmt* pStmt, EM_TYPE_BIND BindType) = 0;
	virtual BOOL GetPrimaryColumnInfo(CColumnInfoEnv& Env) = 0;
	virtual EM_RESULT_TEMPLATE_COMPARE Compare(CTemplateManager* pTemplateManager) = 0;
	virtual BOOL SetInfo(const char* pName, int DataLen) = 0;
	virtual const TemplateInfo* GetInfo() = 0;
	virtual BOOL WriteTo(CMemoryWriter& Writer) = 0;
	virtual BOOL ReadFrom(CMemoryReader& Reader, int ProtocolVersion) = 0;
	virtual BOOL WriteDataTo(char* pData, CMemoryWriter& Writer) = 0;
	virtual BOOL ReadDataFrom(char* pData, CMemoryReader& Reader) = 0;
	virtual BOOL SetDefault(char* pData) = 0;
	virtual BOOL CopyFrom(char* pData, CDBTemplate* pSrcTemplate, char* pSrcData) = 0;
	virtual BOOL HasPackData() = 0;
protected:
private:
};

#endif