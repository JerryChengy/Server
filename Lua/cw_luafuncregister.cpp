#include "cw_luainterface.h"
#include "cw_luafunc.h"
#define LUA_REGISTER(szFuncname, func) lua_register(L, szFuncname, func);


void RegisterLuaFunc()
{
	lua_State* L = CLuaInterface::GetSingleton().m_pState;
	LUA_REGISTER("GetTestTblData", Lua_GetTestTblData);

}