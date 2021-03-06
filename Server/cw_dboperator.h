#ifndef CW_DBOPERATOR_H
#define CW_DBOPERATOR_H
#include "cw_mysqlwrap.h"
#include "cw_dbheader.h"

class CDBOperator
{
public:
	virtual	EM_TYPE_DBOPERATOR GetType()=0;

	virtual BOOL	Execute(char* pData) = 0;

	virtual BOOL    Save(char* pData) = 0;

	virtual BOOL	Load(char* pData) = 0;

	virtual EM_RESULT_FIND Find(char* pData) = 0;

	virtual BOOL    Delete(char* pData) = 0;

	virtual int		EnumBegin() = 0;

	virtual BOOL	EnumNext(char* pData) = 0;

	virtual	BOOL	EnumEnd() = 0;

	virtual	BOOL	Init(CTemplateManager* pTemplateManager, CMysqlWrap* pMysql) = 0;

	virtual EM_RESULT_OPERATOR_COMPARE Compare(CDBOperatorManager* pOperatorManager) = 0;

	virtual BOOL	SetName(const char* pName) = 0;
protected:
private:
};

#endif