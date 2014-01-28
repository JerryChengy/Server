#ifndef CW_TIME_H
#define CW_TIME_H
#include "cw_commondefine.h"
#include "cw_singleton.h"



class CTimeManager: public Singleton<CTimeManager>
{
public:
	void Init();
	void Tick();
	const tm& GetThisTime();
protected:

private:
	void	_SetThisTime();
private:
	time_t	m_thisTime;
	tm		m_thisTMTime;
};

#endif
