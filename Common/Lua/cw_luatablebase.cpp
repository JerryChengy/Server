#include "cw_luatablebase.h"


bool Check_LuaTblParam(lua_State *L)
{
	if (!lua_isnumber(L, 1) || !lua_isstring(L, 2))
	{
		return false;
	}
	return true;
}




