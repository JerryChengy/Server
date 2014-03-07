#include "cw_luaenum.h"
#include "cw_tools.h"
#include "cw_assert.h"
#include "cw_luainterface.h"

SINGLETONG_IMPLEMENTION(CScriptEnum);

void CScriptEnum::Init(lua_State* L)
{ 
	m_pState = L; 
	lua_register(L, "RegEnum_NewIndex", RegEnum_NewIndex); 
}
void  CScriptEnum::BeginRegisterEnum( const char* pSetName )
{
	memset(m_SetName, 0, sizeof(pSetName));
	memset(m_TblExName, 0, sizeof(m_TblExName));
	memset(m_MetaTblName, 0, sizeof(m_MetaTblName));
	CTools::Strcpy(m_SetName, pSetName, sizeof(m_SetName));

	bool bRet = CLuaInterface::GetSingleton().CreateTable(m_pState, m_SetName);
	if (!bRet)
	{
		return ;
	}

	_snprintf(m_TblExName, sizeof(m_TblExName)-1, "%s_EX", m_SetName);
	bRet = CLuaInterface::GetSingleton().CreateTable(m_pState, m_TblExName);
	if (!bRet)
	{
		return ;
	}
	
	_snprintf(m_MetaTblName, sizeof(m_MetaTblName)-1, "%s_Meta", m_SetName);
	bRet = CLuaInterface::GetSingleton().CreateTable(m_pState, m_MetaTblName);
	if (!bRet)
	{
		return ;
	}
}

void CScriptEnum::RegisterEnum( const char* pEnumName, int nEnumVal )
{
	luaL_findtable(m_pState, LUA_GLOBALSINDEX, m_TblExName, 0);	
	lua_pushnumber(m_pState, nEnumVal);
	lua_setfield(m_pState, -2, pEnumName);
	lua_pop(m_pState, 2);
}

void CScriptEnum::EndRegisterEnum()
{
	luaL_findtable(m_pState, LUA_GLOBALSINDEX, m_SetName, 0);	
	luaL_findtable(m_pState, LUA_GLOBALSINDEX, m_TblExName, 0);	
	luaL_findtable(m_pState, LUA_GLOBALSINDEX, m_MetaTblName, 0);
	
	lua_pushvalue(m_pState, -1);
	lua_setmetatable(m_pState, 1);//将原始表的元表设成MetaTbl
	lua_pushvalue(m_pState, 2);
	lua_setfield(m_pState, 3, "__index");//将元表的__index方法设成扩展表
	lua_pushcfunction(m_pState, RegEnum_NewIndex);
	lua_setfield(m_pState, 3, "__newindex");//将元表的__index方法设成扩展表
	lua_pop(m_pState, 3);

}

int RegEnum_NewIndex( lua_State* L )
{
	return 0;
}
