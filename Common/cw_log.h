#ifndef CW_LOG_H
#define CW_LOG_H
#include "cw_const.h"
#include "cw_singleton.h"


class CLogManager: public Singleton<CLogManager>
{
public:
	void		Init();
	void		Tick();

	void		DebugLog(const char* format, ...);
	
private:
	void		_TickNewFold();
	const char* _GetCurrentPath(){ return m_CurrentPath; }
protected:
private:
	char    m_CurrentPath[MAX_FILE_PATH];
};

#define LOG_DEBUG(format,...) CLogManager::GetSingleton().DebugLog(format,__VA_ARGS__);
#endif
