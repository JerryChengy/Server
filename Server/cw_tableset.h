#ifndef CW_TABLESET_H
#define CW_TABLESET_H
#include "cw_commondefine.h"
#include "cw_table.h"
#include "cw_servertablestruct.h"
#include "cw_publictablestruct.h"
#include "cw_singleton.h"


class CTableSet : public Singleton<CTableSet>
{
public:
	bool Init();	

protected:
private:

public:
	CTable<TABLE_TEST> m_Test;
	CTable<TABLE_SCRIPT> m_Script;
	CTable<TABLE_SCRIPT> m_PublicScript;
};

#define Tables CTableSet::GetSingleton()

#endif