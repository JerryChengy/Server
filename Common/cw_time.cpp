#include "cw_const.h"
#include "cw_time.h"

SINGLETONG_IMPLEMENTION(CTimeManager)
//TimeManager* Singleton<TimeManager>::sm_Singleton = 0;
void CTimeManager::_SetThisTime()
{
	time_t ttime;
	time(&ttime);
	m_thisTime = (unsigned int)ttime + SECONDS_PER_HOUR*SERVER_TIME_ZONE;
	gmtime_s(&m_thisTMTime, &m_thisTime);
	m_thisTMTime.tm_year += 1900;
	m_thisTMTime.tm_mon += 1;
}

void CTimeManager::Init()
{
	_SetThisTime();
}

void CTimeManager::Tick()
{
	_SetThisTime();
}


const tm& CTimeManager::GetThisTime()
{
	return m_thisTMTime;
}
