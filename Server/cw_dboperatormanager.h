#ifndef CW_DBOPERATORMANAGER_H
#define CW_DBOPERATORMANAGER_H
#include "cw_dbheader.h"
#include "cw_singleton.h"
class CDBOperator;
class CTemplateManager;
class CMemoryReader;
class CMemoryWriter;

class CDBOperatorManager: public Singleton<CDBOperatorManager>
{
public:
	CDBOperatorManager();
	~CDBOperatorManager();
protected:
	bool	Register(const char* pName, CDBOperator* pDBOperator);

	CDBOperator* GetDBOperator(const char* pName);

	EM_RESULT_OPERATOR_COMPARE CompareAll(CDBOperatorManager* pDBOperatorManager);

	bool	InitAll(CTemplateManager* pTemplateManager,
				const char* pIP, const char* pUser, const char* pPwd, const char* pInstance, int Port);

	bool	AdjustAll(CDBOperatorManager* pDBOperatorManager);

	bool	PrepareAll();

	bool	WriteTo(CMemoryWriter);

	bool	ReadFrom(CMemoryReader& Reader, int ProtocolVersion);

	bool	RegisterAll();
private:
	bool	_EnLarge();

	bool	_InitMysqlWrap(const char* pIP, const char* pUser, const char* pPwd, const char* pInstance, int Port);

private:
	struct DBOperatorData 
	{
		void			CleanUp()
		{
			ZEROMEM(m_Name);
			m_pDBOperator = 0;
		}
		DBOperatorData()
		{
			CleanUp();
		}
		char			m_Name[DB_OPERATOR_NAME_MAX_LEN];		//操作名
		CDBOperator*	m_pDBOperator;	//操作实例
	};
	DBOperatorData*				m_pDBOperatorData;
	int							m_DBOperatorCount;
	int							m_DBOperatorDataLen;

	CMysqlWrap*					m_pMysql;
};
#endif