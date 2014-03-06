#ifndef CW_LUAFUNC_H
#define CW_LUAFUNC_H
extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}
int luaopen_player(lua_State *L);

int Lua_HandleSCTestPacket(lua_State *L);
#endif