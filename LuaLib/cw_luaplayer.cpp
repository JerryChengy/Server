#include "cw_luafunc.h"
#include "cw_player.h"

static const luaL_Reg playerlib[] = 
{
	{"GetPlayer", Lua_GetPlayer},
	{"GetLevel", Lua_GetPlayerLevel},
	
};

int luaopen_player(lua_State *L)
{
	luaL_register(L, "player", playerlib);
	
	return 1;
}


int Lua_GetPlayer(lua_State *L)
{
	const char* pFuncName = lua_tostring(L, 1);
	/*lua_pushlightuserdata(L, g_Player);
	return 1;*/
	lua_pushcclosure(L, Lua_GetPlayerLevel, 0);
	return 1;
}

int Lua_GetPlayerLevel(lua_State *L)
{
	/*CPlayer *pPlayer = static_cast<CPlayer *>(lua_touserdata(L, 1));
	if (!pPlayer)
	{
		return 0;
	}
	lua_pushnumber(L, pPlayer->GetLevel());*/
	int p1 = static_cast<int>(lua_tonumber(L, 1));
	int p2 = static_cast<int>(lua_tonumber(L, 2));
	int p3 = static_cast<int>(lua_tonumber(L, 3));
	int res = p1 + p2 + p3;
	lua_pushnumber(L, res);
	return 1;
}
