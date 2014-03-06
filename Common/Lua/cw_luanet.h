#ifndef CW_LUA_NET_H
#define CW_LUA_NET_H

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}
int luaopen_net(lua_State *L);

int lua_IsServer(lua_State *L);

int Lua_DelConn(lua_State *L);

int Lua_GetSocketRecvBuff(lua_State *L);

int Lua_MapBuff(lua_State *L);

int Lua_RecoverBuff(lua_State *L);

int Lua_EndParseBuff(lua_State *L);

int Lua_GetSocketSendBuff(lua_State *L);

int Lua_FillBuff(lua_State *L);

int Lua_PreFillBuff(lua_State *L);

extern char*	g_VarData;
#endif