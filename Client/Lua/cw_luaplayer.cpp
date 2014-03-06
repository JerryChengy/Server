#include "cw_luafunc.h"
#include "cw_serverconnection.h"
#include "cw_log.h"
#include "cw_testdata.h"

static const luaL_Reg playerlib[] = 
{
	{"HandleSCTestPacket", Lua_HandleSCTestPacket},
	{ NULL, NULL }
};

int luaopen_player(lua_State *L)
{
	luaL_register(L, "player", playerlib);

	return 1;
}

int Lua_HandleSCTestPacket(lua_State *L)
{
	if (!lua_isnumber(L, 1))
	{
		return 0;
	}
	int p1 = (int)lua_tonumber(L, 1);
	LOG_DEBUG("p1: %d", p1);
	if (!lua_isstring(L, 2))
	{
		return 0;
	}
	const char* p2 = lua_tostring(L, 2);
	LOG_DEBUG("p2: %s", p2);
	if (!lua_isuserdata(L, 3))
	{
		return 0;
	}
	const HumanData* pData = (HumanData*)lua_touserdata(L, 3);
	if (!pData)
	{
		return 0;
	}
	LOG_DEBUG("p3: %d", pData->m_ID);
	return 0;
}