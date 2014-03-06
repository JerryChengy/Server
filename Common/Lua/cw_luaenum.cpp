#include "cw_luaenum.h"
#include "cw_tools.h"

SINGLETONG_IMPLEMENTION(CScriptEnum);
void  CScriptEnum::BeginRegisterEnum( const char* pSetName )
{
	lua_newtable(m_pState);  /* create metatable */
	//lua_pushvalue(L, -1);
	lua_setfield(m_pState, LUA_REGISTRYINDEX, pSetName);  /* registry.name = metatable */
	CTools::Strcpy(m_SetName, pSetName, CTools::Strlen(pSetName));
	lua_pop(m_pState, 1);
}

void CScriptEnum::RegisterEnum( const char* pEnumName, int nEnumVal )
{
	luaL_findtable(m_pState, LUA_REGISTRYINDEX, m_SetName, 0);
	if (!lua_istable(m_pState, -1)) 
	{
		lua_pop(m_pState, 1);
		return ;
	}
	lua_pushnumber(m_pState, nEnumVal);
	lua_setfield(m_pState, -2, pEnumName);
	lua_pop(m_pState, 2);
}
