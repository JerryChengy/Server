#ifndef CW_LUAFUNC_H
#define CW_LUAFUNC_H
extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

void RegisterLuaTbl(lua_State* L, const char* pTblName, const char* pSectionName, lua_CFunction func);




int luaopen_player(lua_State *L);

int luaopen_net(lua_State *L);

int Lua_GetTestTblData(lua_State *L);

int Lua_GetPlayerLevel(lua_State *L);

int Lua_GetPlayer(lua_State *L);

int Lua_DelConn(lua_State *L);

int Lua_SendTestPacket(lua_State *L);

int Lua_GetSocketRecvBuff(lua_State *L);

int Lua_MapBuff(lua_State *L);

int Lua_RecoverBuff(lua_State *L);

int Lua_EndParseBuff(lua_State *L);

int Lua_GetSocketSendBuff(lua_State *L);

int Lua_FillBuff(lua_State *L);

int Lua_PreFillBuff(lua_State *L);

#endif