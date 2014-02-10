#ifndef CW_LUAFUNC_H
#define CW_LUAFUNC_H
extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}


int Lua_GetTestTblData(lua_State *L);
#endif