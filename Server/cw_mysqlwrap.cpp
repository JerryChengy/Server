#include "cw_mysqlwrap.h"
#include "cw_log.h"
#include "cw_sqlstatement.h"


CMysqlWrap::CMysqlWrap():m_pMysql(0),m_pMysqlStmt(0),m_MysqlStmtCount(0),m_MysqlStmtMaxCount(0)
{

}

CMysqlWrap::~CMysqlWrap()
{
	for (int i=0;i<m_MysqlStmtCount;++i)
	{
		FreeStmtResult(&m_pMysqlStmt[i]);
		mysql_stmt_close(m_pMysqlStmt[i].m_pStmt);
		SAFE_DELETE(m_pMysqlStmt[i].m_pBind);
		SAFE_DELETE(m_pMysqlStmt[i].m_pBindParam);
	}
	SAFE_DELETEARRAY(m_pMysqlStmt);
	if (m_pMysql)
	{
		mysql_close(m_pMysql);
	}
}

bool CMysqlWrap::FreeStmtResult(Mysql_Stmt *pStmt)
{
	if (pStmt == 0 || pStmt->m_pStmt == 0)
	{
		return false;
	}
	if (!pStmt->m_HasResult)
	{
		return true;
	}
	mysql_stmt_free_result(pStmt->m_pStmt);
	pStmt->m_HasResult = true;
	return true;
}
//初始化数据
bool CMysqlWrap::Connect(char *host,int port ,char * Db,char * user,char* passwd)
{
	if( (m_pMysql = mysql_init(0)) == NULL )
	{
		LOG_DEBUG("MYSQL ERROR: mysql_init failed");
		return false;
	}    
	//支持断线重连
	char value = 1;
	if (mysql_options(m_pMysql, MYSQL_OPT_RECONNECT, &value) != 0)
	{
		LOG_DEBUG("MYSQL ERROR: mysql_options failed");
		mysql_close(m_pMysql);
		m_pMysql = 0;
		return false;
	}

	if (mysql_real_connect(m_pMysql,host,user,passwd,Db,port,NULL,CLIENT_MULTI_STATEMENTS) == NULL)
	{
		LOG_DEBUG("MYSQL ERROR: mysql_real_connect failed");
		mysql_close(m_pMysql);
		m_pMysql = 0;
		return false;
	}    	
	if (!_InitConnection())
	{
		LOG_DEBUG("MYSQL ERROR: _InitConnection failed");
		mysql_close(m_pMysql);
		m_pMysql = 0;
		return false;
	}
	LOG_DEBUG("connect db ok...");
	return true;
}

bool CMysqlWrap::_ReConnect()
{
	if (mysql_ping(m_pMysql) != 0)
	{
		LOG_DEBUG("MYSQL ERROR: mysql_ping failed");
		return false;
	}
	if (!_InitConnection())
	{
		LOG_DEBUG("MYSQL ERROR: _InitConnection failed");
		return false;
	}
	for (int i=0;i<m_MysqlStmtCount;++i)
	{
		FreeStmtResult(&m_pMysqlStmt[i]);
		_CleanUpStmt(&m_pMysqlStmt[i]);
		mysql_stmt_close(m_pMysqlStmt[i].m_pStmt);
		m_pMysqlStmt[i].m_pStmt = mysql_stmt_init(m_pMysql);
		if (m_pMysqlStmt[i].m_pStmt == 0)
		{
			LOG_DEBUG("MYSQL ERROR: _ReConnect failed");
			return false;
		}
		if (mysql_stmt_prepare(m_pMysqlStmt[i].m_pStmt, m_pMysqlStmt[i].m_Command, (unsigned long)strlen(m_pMysqlStmt[i].m_Command)) != 0)
		{
			_PrintError("mysql_stmt_prepare");
			LOG_DEBUG("MYSQL ERROR: _ReConnect failed");
			return false;
		}
	}
	LOG_DEBUG("ReConnect MYSQL OK.");
	return true;
}

bool CMysqlWrap::_CleanUpStmt(Mysql_Stmt* pStmt)
{
	if (!pStmt || pStmt->m_pStmt == 0)
	{
		return false;
	}
	memset(pStmt->m_pBind, 0, sizeof(MYSQL_BIND)*pStmt->m_BindLen);
	pStmt->m_BindCount = 0;
	return true;
}

void CMysqlWrap::_PrintError(const char* pInfo)
{
	if (m_pMysql)
	{
		if (pInfo)
		{
			LOG_DEBUG("MYSQL ERROR: %s.", mysql_error(m_pMysql));
		}
		else
		{
			LOG_DEBUG("MYSQL ERROR: %s {INFO: %s}.", mysql_error(m_pMysql), pInfo);
		}
	}
}
bool CMysqlWrap::RealQuery(const char* pCommand)
{
	if (!pCommand)
	{
		return false;
	}
	if (mysql_real_query(m_pMysql, pCommand, (unsigned long) strlen(pCommand)) != 0)
	{
		LOG_DEBUG("MYSQL ERROR: %s {INFO: %s}.", mysql_error(m_pMysql), pCommand);
		return false;
	}
	return true;
}
bool CMysqlWrap::_InitConnection()
{
	if (!RealQuery(sqlSetSqlMode))
	{
		return false;
	}
	if (!RealQuery(sqlSetIsolationLevel))
	{
		return false;
	}
	if (!RealQuery(sqlFormatSetTimeout))
	{
		return false;
	}
	if (!RealQuery(sqlSetCharacterSet))
	{
		return false;
	}
	return true;
}
//查询数据
bool CMysqlWrap::LoadBlockData(char * sql, char* pData, int iLen)
{	
	if (iLen <= 0)
	{
		return false;
	}
	if(mysql_query(m_pMysql,sql) != 0)
	{
		LOG_DEBUG("select ps_info Error");
		return false;
	}
	MYSQL_RES *res;
	res = mysql_store_result(m_pMysql);
	if(res==NULL)
	{
		LOG_DEBUG("select username Error");
		return false;
	}
	m_row = mysql_fetch_row(res);
	if (m_row == 0)
	{
		return false;
	}
	memcpy(pData, m_row[0], iLen);	
	mysql_free_result(res);
	return true;
}

//插入数据
bool CMysqlWrap::InsertData(char * sql)
{
	if(mysql_query(m_pMysql,sql) != 0)
	{
		LOG_DEBUG("Insert Data Error");
		return true;
	}
	return false;
}


//关闭数据库连接
void CMysqlWrap::CloseMySQLConn()
{
	mysql_close(m_pMysql);
}

bool CMysqlWrap::ExecuteStmt(Mysql_Stmt* pStmt)
{
	if (pStmt == 0 || pStmt->m_pStmt = 0)
	{
		return false;
	}
	if (pStmt->m_HasResult == true)
	{
		FreeStmtResult(pStmt);
	}
	if (mysql_stmt_bind_param(pStmt->m_pStmt, pStmt->m_pBind) != 0)
	{
		_PrintStmtError(pStmt, "mysql_stmt_bind_param");
		_CleanUpStmt(pStmt);
		return false;
	}
	if (mysql_stmt_execute(pStmt->m_pStmt) != 0)
	{
		_PrintStmtError(pStmt, "mysql_stmt_execute");
		_CleanUpStmt(pStmt);
		_ReConnect();
		return false;
	}
	_CleanUpStmt(pStmt);
	return true;
}
Mysql_Stmt* CMysqlWrap::GetStmtByName(const char* pStmtName)
{
	for (int i=0;i<m_MysqlStmtCount;++i)
	{
		if (CTools::Stricmp(m_pMysqlStmt[i].m_Name, pStmtName) == 0)
		{
			_CleanUpStmt(&m_pMysqlStmt[i]);
			return &m_pMysqlStmt[i];
		}
	}
}

bool CMysqlWrap::RegisterStmt(const char* pStmtName, const char* pStmtCommand, int StmtParamLen)
{
	if (!pStmtName || !pStmtCommand)
	{
		return false;
	}
	int NameLen = CTools::Strlen(pStmtName)+1;
	if (NameLen > DB_MYSQL_STMT_NAME_MAX_LEN)
	{
		LOG_DEBUG("MYSQL ERROR: stmt name=%s too long", pStmtName);
		return false;
	}
	int CommandLen = CTools::Strlen(pStmtCommand)+1;
	if (CommandLen > DB_MYSQL_STMT_MAX_LEN)
	{
		LOG_DEBUG("MYSQL ERROR: stmt command=%s too long", pStmtCommand);
		return false;
	}
	if (GetStmtByName(pStmtName) != 0)
	{
		LOG_DEBUG("MYSQL ERROR: stmt name=%s repeat", pStmtName);
		return false;
	}
	if (m_MysqlStmtCount == m_MysqlStmtMaxCount && _EnlargeStmt() == false)
	{
		return false;
	}
	Mysql_Stmt* pStmt = mysql_stmt_init(m_pMysql);
	if (!pStmt)
	{
		_PrintStmtError("mysql_stmt_intit");
		return false;
	}
	if (mysql_stmt_prepare(pStmt, pStmtCommand, (unsigned long)strlen(pStmtCommand)) != 0)
	{
		_PrintStmtError("mysql_stmt_prepare");
		mysql_stmt_close(pstmt);
		return false;
	}
	if (StmtParamLen > 0)
	{
		m_pMysqlStmt[m_MysqlStmtCount]->m_pBind = new MYSQL_BIND[StmtParamLen];
		m_pMysqlStmt[m_MysqlStmtCount]->m_pBindParam = new BindParam[StmtParamLen];
	}
	m_pMysqlStmt[m_MysqlStmtCount].m_BindLen = StmtParamLen;
	m_pMysqlStmt[m_MysqlStmtCount].m_pStmt = pStmt;
	CTools::Strcpy(m_pMysqlStmt[m_MysqlStmtCount].m_Command, pStmtCommand, sizeof(m_pMysqlStmt[m_MysqlStmtCount].m_Command));
	CTools::Strcpy(m_pMysqlStmt[m_MysqlStmtCount].m_Name, pStmtName, sizeof(m_pMysqlStmt[m_MysqlStmtCount].m_Name));
	_CleanUpStmt(m_pMysqlStmt[m_MysqlStmtCount]);
	m_MysqlStmtCount++;
	return true;
}

bool CMysqlWrap::_EnlargeStmt()
{
	static const int DB_MYSQL_STMT_ENLARGE_COUNT = 64;
	int NewDataLen = m_MysqlStmtMaxCount + DB_MYSQL_STMT_ENLARGE_COUNT;
	Mysql_Stmt* pNewData = new Mysql_Stmt[NewDataLen];
	if (!pNewData)
	{
		return false;
	}
	if (m_MysqlStmtCount > 0)
	{
		memcpy(pNewData, m_pMysqlStmt, sizeof(Mysql_Stmt)*m_MysqlStmtCount);
	}
	SAFE_DELETEARRAY(m_pMysqlStmt);
	m_pMysqlStmt = pNewData;
	m_MysqlStmtMaxCount = NewDataLen;
	return true;
}
bool CMysqlWrap::StoreStmtResult(Mysql_Stmt* pStmt)
{
	if (pStmt == 0 || pStmt->m_pStmt == 0)
	{
		return false;
	}
	if (mysql_stmt_store_result(pStmt->m_pStmt) != 0)
	{
		_PrintStmtError(pStmt, "mysql_stmt_store_result");
		_ReConnect();
		return false;
	}
	pStmt->m_HasResult = true;
	return true;
}
void CMysqlWrap::_PrintStmtError(Mysql_Stmt* pStmt, const char* pInfo)
{
	if (!pStmt || pStmt->m_pStmt == 0)
	{
		return ;
	}
	if (pInfo)
	{
		LOG_DEBUG("MYSQL ERROR: %s.", mysql_stmt_error(pStmt->m_pStmt));
	}
	else
	{
		LOG_DEBUG("MYSQL ERROR: %s {INFO: %s}.", mysql_stmt_error(pStmt->m_pStmt), pInfo);
	}

}