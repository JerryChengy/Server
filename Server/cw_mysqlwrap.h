#ifndef CW_MYSQLWRAP_H
#define CW_MYSQLWRAP_H
#include "cw_commondefine.h"
#include "mysql.h"
#include "cw_dbheader.h"

struct BindParam 
{
	ullong			m_BufferLen;
	my_bool			m_IsNull;
};
struct Mysql_Stmt 
{
	Mysql_Stmt():m_pStmt(0),m_pBind(0),m_pBindParam(0),
		m_BindCount(0),m_BindLen(0),m_HasResult(false)
	{
		m_Name[0] = 0;
		m_Command[0] = 0;
	}
	char			m_Name[DB_MYSQL_STMT_NAME_MAX_LEN];		//对应名字
	char			m_Command[DB_MYSQL_STMT_MAX_LEN];	//预处理指令
	MYSQL_STMT		*m_pStmt;	//预处理
	MYSQL_BIND		*m_pBind;	//绑定参数
	BindParam		*m_pBindParam;//绑定参数
	int				m_BindCount;//当前绑定数
	int				m_BindLen;	//绑定参数长度
	bool			m_HasResult;//是否有结果没有释放
};
class CMysqlWrap
{
public:      
    CMysqlWrap();
	~CMysqlWrap();
    bool			LoadBlockData(char * sql, char* pData, int iLen);

	void			CloseMySQLConn();
	bool			InsertData(char * SQL);
	bool			Connect(char *host,int port ,char * Db,char * user,char* passwd);
	bool			FreeStmtResult(Mysql_Stmt *pStmt);
	bool			RealQuery(const char* pCommand);
	bool			ExecuteStmt(Mysql_Stmt* pStmt);
	bool			StoreStmtResult(Mysql_Stmt* pStmt);
	Mysql_Stmt*		GetStmtByName(const char* pStmtName);
	bool			RegisterStmt(const char* pStmtName, const char* pStmtCommand, int StmtParamLen);
private:
	bool			_InitConnection();
	bool			_CleanUpStmt(Mysql_Stmt* pStmt);
	bool			_ReConnect();
	void			_PrintError(const char* pInfo);
	void			_PrintStmtError(Mysql_Stmt* pStmt, const char* pInfo);
	bool			_EnlargeStmt();

private:
	MYSQL*			m_pMysql; 
	MYSQL_ROW		m_row;  
	Mysql_Stmt*		m_pMysqlStmt;
	int				m_MysqlStmtCount;
	int				m_MysqlStmtMaxCount;
};

#endif