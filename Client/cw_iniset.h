#ifndef CW_INISET_H
#define CW_INISET_H
#include "cw_inistruct.h"
#include "cw_singleton.h"


class CIniSet: public Singleton<CIniSet>
{
public:
	bool Init();


protected:
private:

public:
	INI_SHM	m_Shm;

};

#define g_Ini (CIniSet::GetSingleton())

#endif