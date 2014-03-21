#ifndef CW_DBHEADER_H
#define CW_DBHEADER_H
#include "cw_commondefine.h"

//文件删除
#if defined (_LINUX64_)
#define DELETE_FILE(_filename) unlink(_filename)
#elif defined (_WIN32_)
#define DELETE_FILE(_filename) \
{\
	if (access(_filename, 0) == 0)\
	{\
		char __tCommand[1024] = {};\
		_snprintf(__tCommand, sizeof(__tCommand)-1, "del /Q %s", _filename);\
		system(__tCommand);\
	}\
}
#endif



#if defined (_LINUX64_)
#define  SYSTEM(_command, _status, _return)\
	{\
		_status = system(_command);\
		if (_status!=-1 && WIFEXITED(_status) != 0 && WEXITSTATUS(_status) == 0)\
		{\
			_return = 1;\
		}\
		else\
		{\
			_return = 0;\
		}\
	}
#elif defined (_WIN32_)
#define  SYSTEM(_command, _status, _return)\
	{\
		_status = system(_command);\
		if (_status == 0)\
		{\
			_return = 1;\
		}\
		else\
		{\
			_return = 0;\
		}\
	}
#endif

//表全名最大长度
const int DB_TABLE_FULLNAME_MAX_LEN = 64;
// mysql预处理名字最大长度
const int DB_MYSQL_STMT_NAME_MAX_LEN = DB_TABLE_FULLNAME_MAX_LEN + 16;
// sql预处理语句最大长度
const int DB_MYSQL_STMT_MAX_LEN = 1024*8;

const int DB_ENCRYPT_KEY_MAX_LEN = 64;

const int DB_COLUMN_MAX_NAME_LEN = 64;

const int DB_COLUMN_DEFAULT_MAX_LEN = 32;

const int DB_INVALID_DATA_MAX_LEN = 32;

const int DB_DEFAULT_DATA_MAX_LEN = 32;

const int DB_COLUMN_FULLNAME_MAX_LENGTH = 1024;

const int DB_COLUMN_TYPENAME_MAX_LEN = 64;

const char* DB_SQL_PRIMARY_KEY = "PRIMARY KEY";

const int DB_TABLE_MAX_NAME_LEN = 64;
const int DB_PACKINFO_MAX_LEN = 1024*1024;
const int DB_OPERATOR_NAME_MAX_LEN = 64;
const char* DB_COLUMN_NAME_SPLIT = "_";


//数据库列类型
enum EM_TYPE_DB_COLUMN
{
	EM_TYPE_DB_COLUMN_INVALID = -1,
	EM_TYPE_DB_COLUMN_BYTE,
	EM_TYPE_DB_COLUMN_SHORT,
	EM_TYPE_DB_COLUMN_INT,
	EM_TYPE_DB_COLUMN_FLOAT,
	EM_TYPE_DB_COLUMN_DOUBLE,
	EM_TYPE_DB_COLUMN_VARCHAR,
	EM_TYPE_DB_COLUMN_CHAR,
	EM_TYPE_DB_COLUMN_BIGINT,		//64位
	EM_TYPE_DB_COLUMN_BLOB,			//最大长度为64K的二进制数据块
	EM_TYPE_DB_COLUMN_LONGBLOB,		//最大长度为4G的二进制数据快
	EM_TYPE_DB_COLUMN_STRUCT,		
	EM_TYPE_DB_COLUMN_COUNT
};

//数据库表引擎类型
enum EM_TYPE_DB_TABLE
{
	EM_TYPE_DB_TABLE_INVALID = -1,
	EM_TYPE_DB_TABLE_MYISAM,
	EM_TYPE_DB_TABLE_INNODB,
	EM_TYPE_DB_TABLE_DEFAULT,
	EM_TYPE_DB_TABLE_COUNT,
};

//模板类型
enum EM_TYPE_TEMPLATE
{
	EM_TYPE_TEMPLATE_INAVLID = -1,
	EM_TYPE_TEMPLATE_STRUCT,
	EM_TYPE_TEMPLATE_DISTRIBUTE,
	EM_TYPE_TEMPLATE_COUNT
};

//模板比较结果
enum EM_RESULT_TEMPLATE_COMPARE
{
	EM_RESULT_TEMPLATE_COMPARE_INVALID = -1,
	EM_RESULT_TEMPLATE_COMPARE_NEW,
	EM_RESULT_TEMPLATE_COMPARE_SAME,
	EM_RESULT_TEMPLATE_COMPARE_DIFFER,
	EM_RESULT_TEMPLATE_COMPARE_ERROR,
	EM_RESULT_TEMPLATE_COMPARE_COUNT
};

//操作比较结果
enum EM_RESULT_OPERATOR_COMPARE
{
	EM_RESULT_OPERATOR_COMPARE_INVALIE = -1,
	EM_RESULT_OPERATOR_COMPARE_NEW,
	EM_RESULT_OPERATOR_COMPARE_SAME,
	EM_RESULT_OPERATOR_COMPARE_DIFFER,
	EM_RESULT_OPERATOR_COMPARE_ERROR,
	EM_RESULT_OPERATOR_COMPARE_COUNT

};

//操作类型
enum EM_TYPE_DBOPERATOR
{
	EM_TYPE_DBOPERATOR_INVALID = -1,
	EM_TYPE_DBOPERATOR_TEMPLATE,
	EM_TYPE_DBOPERATOR_TOOLS,
	EM_TYPE_DBOPERATOR_COUNT
};

enum EM_RESULT_FIND
{
	EM_RESULT_FIND_INVALID = -1,
	EM_RESULT_FIND_EXIST,
	EM_RESULT_FIND_ERROR,

	EM_RESULT_FIND_COUNT
};

enum EM_TYPE_BIND
{
	EM_TYPE_BIND_INVALID = -1,
	EM_TYPE_BIND_SET,
	EM_TYPE_BIND_GET,
	EM_TYPE_BIND_COUNT
};

enum EM_TYPE_SERIALIZE
{
	EM_TYPE_SERIALIZE_INVALID = -1,
	EM_TYPE_SERIALIZE_BLOCK,
	EM_TYPE_SERIALIZE_SEGMENT,
	EM_TYPE_SERIALIZE_NONE,
	EM_TYPE_SERIALIZE_ERROR,
	EM_TYPE_SERIALIZE_COUNT
};

//默认表引擎
const EM_TYPE_DB_TABLE DB_DEFAULT_TABLE_ENGINE = EM_TYPE_DB_TABLE_INNODB;

struct ColumnInfo 
{
	ColumnInfo(){ CleanUp(); }
	void		CleanUp()
	{
		m_Type = EM_TYPE_DB_COLUMN_INVALID;
		m_Pos = 0;
		m_Len = 0;
		m_Primary = FALSE;
		m_NewColumn = FALSE;
		m_IsUnsigned = FALSE;
		m_HasInvalid = FALSE;
		m_DefaultLen = 0;
		m_IsIndex = FALSE;
		m_IsEncrypt = FALSE;
		memset(m_EncryptKey, 0, sizeof(m_EncryptKey));
		memset(m_Name, 0, sizeof(m_Name));
		memset(m_ColumnDefault, 0, sizeof(m_ColumnDefault));
		memset(m_Invalid, 0, sizeof(m_Invalid));
		memset(m_Default, 0, sizeof(m_Default));
	}
	EM_TYPE_DB_COLUMN		m_Type;			//数据列类型
	int						m_Pos;			//数据偏移量
	int						m_Len;			//数据长度
	BOOL					m_Primary;		//是否是主键
	BOOL					m_NewColumn;	//是否开列
	BOOL					m_IsUnsigned;
	BOOL					m_HasInvalid;
	int						m_DefaultLen;
	BOOL					m_IsIndex;
	BOOL					m_IsEncrypt;
	char					m_EncryptKey[DB_ENCRYPT_KEY_MAX_LEN];
	
	char					m_Name[DB_COLUMN_MAX_NAME_LEN];
	char					m_ColumnDefault[DB_COLUMN_DEFAULT_MAX_LEN];
	char					m_Invalid[DB_INVALID_DATA_MAX_LEN];
	char					m_Default[DB_DEFAULT_DATA_MAX_LEN];
};


struct DBTableInfo 
{

	void		CleanUp()
	{
		m_TableEngine = EM_TYPE_DB_TABLE_INVALID;
		m_ColumnCount = 0;
		m_pMysql = 0;
		ZEROMEM(m_TableName);
		ZEROMEM(m_TablePackName);
		ZEROMEM(m_SaveStmtName);
		ZEROMEM(m_LoadStmtName);
		ZEROMEM(m_PackInfo);
		ZEROMEM(m_PackInfoEx);
		ZEROMEM(m_SavePackStmtName);
		ZEROMEM(m_LoadPackStmtName);
		ZEROMEM(m_DeleteStmtName);
		ZEROMEM(m_DeletePackStmtName);
		ZEROMEM(m_FindStmtName);
		ZEROMEM(m_LoadPrimaryStmtName);
		ZEROMEM(m_OperatorName);
		m_PackInfoLen = 0;
		m_PackeInfoExLen = 0;
		m_OperatorCompareResult = EM_RESULT_TEMPLATE_COMPARE_INVALID;
		m_HasPackData = FALSE;
	}
	EM_TYPE_DB_TABLE		m_TableEngine;
	int						m_ColumnCount;
	CMysqlWrap*				m_pMysql;

	char					m_TableName[DB_TABLE_MAX_NAME_LEN];
	char					m_TablePackName[DB_TABLE_MAX_NAME_LEN];
	char					m_SaveStmtName[DB_MYSQL_STMT_NAME_MAX_LEN];
	char					m_LoadStmtName[DB_MYSQL_STMT_NAME_MAX_LEN];

	char					m_PackInfo[DB_PACKINFO_MAX_LEN];
	ullong					m_PackInfoLen;

	char					m_PackInfoEx[DB_PACKINFO_MAX_LEN];
	ullong					m_PackeInfoExLen;

	char					m_SavePackStmtName[DB_MYSQL_STMT_NAME_MAX_LEN];
	char					m_LoadPackStmtName[DB_MYSQL_STMT_NAME_MAX_LEN];

	char					m_DeleteStmtName[DB_MYSQL_STMT_NAME_MAX_LEN];
	char					m_DeletePackStmtName[DB_MYSQL_STMT_NAME_MAX_LEN];

	char					m_FindStmtName[DB_MYSQL_STMT_NAME_MAX_LEN];
	char					m_LoadPrimaryStmtName[DB_MYSQL_STMT_NAME_MAX_LEN];
	EM_RESULT_OPERATOR_COMPARE	m_OperatorCompareResult;
	char					m_OperatorName[DB_OPERATOR_NAME_MAX_LEN];
	BOOL					m_HasPackData;
};
#endif