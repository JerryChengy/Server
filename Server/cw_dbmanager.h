#ifndef CW_DBMANAGER_H
#define CW_DBMANAGER_H
#include "cw_singleton.h"
#include "cw_testdata.h"

class CMysqlWrap;
class CDBManager: public Singleton<CDBManager> 
{
public:
	bool		Init();

	bool		SaveHumanData(const HumanData& data);

	bool		LoadHumanData(HumanData& data);
protected:
private:
	CMysqlWrap*			m_pMysql;
};
#endif