#include "cw_commondefine.h"
#include "cw_time.h"
#include "cw_log.h"
SINGLETONG_IMPLEMENTION(CLogManager);


void CLogManager::Init()
{
	_TickNewFold();
}

void CLogManager::Tick()
{
	_TickNewFold();
}

void CLogManager::DebugLog(const char* format, ...)
{
	char fileName[MAX_FILE_PATH] = {};
	_snprintf_s(fileName, sizeof(fileName)-1, "%s\\debug.log", _GetCurrentPath());
	ofstream myostream;
	myostream.open(fileName, ios::out|ios::app);
	if (myostream.bad())
	{
		return ;
	}
	va_list argp;
	va_start(argp, format);
	char logBuffer[1024] = {};
	memset(logBuffer, sizeof(logBuffer), 0);
	_vsnprintf_s(logBuffer, sizeof(logBuffer)-1, format, argp);
	va_end(argp);
	strcat_s(logBuffer, sizeof(logBuffer)-1, "\n");
	char totalBuffer[1024] = {};
	const tm& nowTime = CTimeManager::GetSingleton().GetThisTime();
	_snprintf_s(totalBuffer, sizeof(totalBuffer)-1, "%02d:%02d:%02d %s", nowTime.tm_hour, nowTime.tm_min, nowTime.tm_sec, logBuffer);
	myostream<<totalBuffer;
	printf(totalBuffer);
	myostream.close();
}

void CLogManager::_TickNewFold()
{
	const tm& Time = CTimeManager::GetSingleton().GetThisTime();
	memset(m_CurrentPath, 0, sizeof(m_CurrentPath));
	_snprintf_s(m_CurrentPath, sizeof(m_CurrentPath)-1, "./Log/%04d-%02d-%02d", Time.tm_year, Time.tm_mon, Time.tm_mday);
	struct _stat fileStat;
	if ((_stat(m_CurrentPath, &fileStat)==0) && (fileStat.st_mode & _S_IFDIR))
	{

	}
	else
	{
		_mkdir(m_CurrentPath);
	}
}
