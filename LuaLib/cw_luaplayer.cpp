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
	lua_pushlightuserdata(L, g_Player);
	return 1;
}

int Lua_GetPlayerLevel(lua_State *L)
{
	CPlayer *pPlayer = static_cast<CPlayer *>(lua_touserdata(L, 1));
	if (!pPlayer)
	{
		return 0;
	}
	lua_pushnumber(L, pPlayer->GetLevel());
	return 1;
}