#ifndef CW_LUAINTERFACE_H
#define CW_LUAINTERFACE_H
#include "cw_singleton.h"

extern "C"
{
#include "lua.h"
};



class CLuaInterface: public Singleton<CLuaInterface>
{
public:
	CLuaInterface();
	bool Init();
	bool Load(const char* pFileName);
	int CallScript(char* szFuncName, const char* szFormat, ...);
protected:
public:
	lua_State* m_pState;
};

#endif