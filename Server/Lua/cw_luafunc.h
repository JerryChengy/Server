#ifndef CW_LUAFUNC_H
#define CW_LUAFUNC_H
extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

//void RegisterLuaTbl(lua_State* L, const char* pTblName, const char* pSectionName, lua_CFunction func);

int luaopen_player(lua_State *L);

int Lua_GetTestTblData(lua_State *L);

int Lua_GetPlayerLevel(lua_State *L);

int Lua_GetPlayer(lua_State *L);

int Lua_SendSCTestPacket(lua_State *L);

int Lua_HandleCSPlayerPacket(lua_State *L);

#endif