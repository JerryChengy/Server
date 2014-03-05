#include "cw_luainterface.h"
#include "cw_luafunc.h"
#define LUA_REGISTER(szFuncname, func) lua_register(L, szFuncname, func);


//注册全局函数
void RegisterLuaFunc()
{
	lua_State* L = CLuaInterface::GetSingleton().m_pState;
	LUA_REGISTER("GetTestTblData", Lua_GetTestTblData);

}

void RegisterAllTable(lua_State* L)
{
	luaopen_player(L);
	luaopen_net(L);
}
//注册表内函数
void RegisterLuaTbl(lua_State* L, const char* pTblName, const char* pSectionName, lua_CFunction func)
{
	if (!L)
	{
		return ;
	}
	lua_getglobal(L, pTblName);
	if (!lua_isnil(L, -1))
	{
		lua_newtable(L);
		lua_setglobal(L, pTblName);
		lua_getglobal(L, pTblName);
	}
	lua_pushstring(L, pSectionName);
	lua_pushcfunction(L, func);
	lua_settable(L, -3);
}