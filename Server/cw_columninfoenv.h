#ifndef CW_COLUMNINFOENV_H
#define CW_COLUMNINFOENV_H
#include "cw_dbheader.h"

class CColumnInfoEnv
{
public:
	CColumnInfoEnv()
	{
		m_pColumnInfo = 0;
		m_ColumnSerial = 0;
		ZEROMEM(m_pColumnInfoStack);
		m_ColumnInfoStackCount = 0;
		ZEROMEM(m_ColumnName);
		m_ColumnNameValid = FALSE;
		ZEROMEM(m_ColumnTypeName);
	}
	~CColumnInfoEnv();
public:
	void	SetColumnInfo(ColumnInfo* pInfo){ m_pColumnInfo = pInfo; }
	const ColumnInfo* GetColumnInfo(){ return m_pColumnInfo;}
	BOOL	PushColumnInfo(ColumnInfo* pInfo);
	BOOL	PopColumnInfo();

	int		GetColumnRemainSerial(){ return m_ColumnSerial; }
	void	SetColumnSerial(int serial){ m_ColumnSerial = serial; }
	void	DecColumnSerial(){ --m_ColumnSerial; }

	const char* GetColumnFullName();
	const char* GetColumnTypeName();
	const char* GetColumnDefault();
	const char* GetColumnPrimary();
	BOOL		IsIndex();
	BOOL		IsEncrypt();
protected:
private:
	enum { MAX_COLUMN_STACK_SIZE = 64,};
	ColumnInfo*			m_pColumnInfo;
	int					m_ColumnSerial;
	ColumnInfo*			m_pColumnInfoStack[MAX_COLUMN_STACK_SIZE];
	int					m_ColumnInfoStackCount;
	char				m_ColumnName[DB_COLUMN_FULLNAME_MAX_LENGTH];
	BOOL				m_ColumnNameValid;
	char				m_ColumnTypeName[DB_COLUMN_TYPENAME_MAX_LEN];
};
#endif