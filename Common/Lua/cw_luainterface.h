#ifndef CW_LUAINTERFACE_H
#define CW_LUAINTERFACE_H
#include "cw_singleton.h"

extern "C"
{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

};
#define LUA_REGISTER(szFuncname, func) lua_register(L, szFuncname, func);
class CLuaInterface: public Singleton<CLuaInterface>
{
public:
	CLuaInterface();
	bool Init();
	bool Load(const char* pFileName);
	int CallScript(char* szFuncName, const char* szFormat, ...);
	void RegisterTable();
	bool CreateTable(lua_State* L, const char* pTblName);
protected:
public:
	lua_State* m_pState;

};

void RegisterAllTable(lua_State* L);
void RegisterLuaFunc();


#endif