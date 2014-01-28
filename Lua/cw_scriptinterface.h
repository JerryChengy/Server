#ifndef CW_SCRIPTINTERFACE_H
#define CW_SCRIPTINTERFACE_H
#include "cw_singleton.h"
#include "cw_luainterface.h"

class CScriptInterface: public Singleton<CScriptInterface>
{
public:
	CScriptInterface();
	bool				Init();
	bool				Load();

	int					CallScript(int iScriptID, const char* pFuncName, int iArg1, int iArg2);
	int					CallScript( int iScriptID, const char* pFuncName, double dArg1, double dArg2 );
protected:
private:
	
};

#define SCRIPTMANAGER CScriptInterface::GetSingleton()

#endif