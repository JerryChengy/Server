#include "cw_commondefine.h"
#include "cw_luafunc.h"
#include "cw_luatablebase.h"

int Lua_GetTestTblData(lua_State *L)
{
	if (!Check_LuaTblParam(L))
	{
		return 0;
	}
	return Lua_GetTblData(Tables.m_Test, L);	
}
