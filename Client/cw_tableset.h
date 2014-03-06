#ifndef CW_TABLE_SET_H
#define CW_TABLE_SET_H

#include "cw_commondefine.h"
#include "cw_table.h"
#include "cw_publictablestruct.h"
#include "cw_singleton.h"


class CTableSet : public Singleton<CTableSet>
{
public:
	bool Init();	

protected:
private:

public:
	CTable<TABLE_SCRIPT> m_PublicScript;
};

#define Tables CTableSet::GetSingleton()
#endif