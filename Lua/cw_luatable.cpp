#include "cw_luafunc.h"

bool Check_LuaTblParam(lua_State *L)
{
	if (!lua_isnumber(L, 1) || !lua_isstring(L, 2))
	{
		return false;
	}
	return true;
}

int Lua_GetTblData(lua_State *L)
{
	int nTblId = lua_tonumber(L, 1);
	const char* pRowName = lua_tostring(L, 2);
}

int Lua_GetTestTblData(lua_State *L)
{
	if (!Check_LuaTblParam(L))
	{
		return 0;
	}
		
	Tables.m_ScriptTbl
}
