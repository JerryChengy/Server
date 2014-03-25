#ifndef CW_DBOPERATOR_TEMPLATE_H
#define CW_DBOPERATOR_TEMPLATE_H
#include "cw_dboperator.h"
#include "cw_mysqlwrap.h"

class CDBOperatorTemplate: public CDBOperator
{
public:
	CDBOperatorTemplate();
	~CDBOperatorTemplate();
public:
	virtual	EM_TYPE_DBOPERATOR GetType(){ return EM_TYPE_DBOPERATOR_TEMPLATE; };

	virtual BOOL	Execute(char* pData) = 0;

	virtual BOOL    Save(char* pData) = 0;

	virtual BOOL	Load(char* pData) = 0;

	virtual BOOL    _LoadPack(char* pData);

	virtual EM_RESULT_FIND Find(char* pData) = 0;

	virtual BOOL    Delete(char* pData) = 0;

	virtual int		EnumBegin() = 0;

	virtual BOOL	EnumNext(char* pData) = 0;

	virtual	BOOL	EnumEnd() = 0;

	virtual	BOOL	Init(CTemplateManager* pTemplateManager, CMysqlWrap* pMysql);

	virtual EM_RESULT_OPERATOR_COMPARE Compare(CDBOperatorManager* pOperatorManager) = 0;

	virtual BOOL	SetName(const char* pName) = 0;
protected:
private:
	DBTableInfo*			m_pTableInfo;
};

#endif