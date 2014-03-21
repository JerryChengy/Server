#ifndef CW_DBTEMPLATE_H
#define CW_DBTEMPLATE_H
#include "cw_dbheader.h"
class CTemplateManager;
class CColumnInfoEnv;

class CDBTemplate
{
public:
	CDBTemplate(){};
	virtual ~CDBTemplate(){};
public:
	virtual EM_TYPE_TEMPLATE GetType();

	virtual BOOL Init(CTemplateManager* pTemplateManager) = 0;

	virtual EM_TYPE_SERIALIZE InitSerializeInfo() = 0;

	virtual BOOL GetColumnInfo(CColumnInfoEnv &Env);

	virtual BOOL BindStmtParam(char* pData, Mysql_Stmt * pStmt, EM_TYPE_BIND BindType) = 0;

	virtual BOOL BindPrimaryKey(char* pData, Mysql_Stmt *pStmt, EM_TYPE_BIND BindType) = 0;

	virtual BOOL SetPrimaryKey(char* pData, const char* pKey) = 0;
	virtual BOOL SetPrimaryKey(char* pData, const char* pKey, int KeyLen) = 0;
protected:
private:
};

#endif