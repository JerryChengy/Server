#include "cw_luainterface.h"
#include "cw_assert.h"
#include "cw_tools.h"

extern "C"
{	
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
};

SINGLETONG_IMPLEMENTION(CLuaInterface);



CLuaInterface::CLuaInterface()
{
	m_pState = 0;
}

bool CLuaInterface::Init()
{
	m_pState = lua_open();
	if (!m_pState)
	{
		return false;
	}
	luaL_openlibs(m_pState);
	RegisterLuaFunc();
	return true;
}

bool CLuaInterface::Load(const char* pFileName)
{
	if (!m_pState)
	{
		return false;
	}
	if (!pFileName)
	{
		return false;
	}
	int ret = luaL_dofile(m_pState, pFileName);
	if (ret != 0)
	{
		char szErrorMsg[256] = {0};
		CTools::Strcpy(szErrorMsg, lua_tostring(m_pState, -1), sizeof(szErrorMsg));
		AssertEx(false, "Call Scrit Error£º%s", szErrorMsg);
		lua_pop(m_pState, -1);
		return false;
	}
	return true;
}

int CLuaInterface::CallScript(char* szFuncName, const char* szFormat, ...)
{
	if (!szFuncName || !szFormat)
	{
		return -1;
	}
	int nArg = 0;
	char* pString = 0;
	double dArg = 0.0f;
	lua_getglobal(m_pState,szFuncName); 
	va_list args;
	va_start(args, szFormat);
	int iIndex = 0;
	char cFormat = 0;
	while (cFormat = szFormat[iIndex])
	{
		bool bRet = true;
		switch (cFormat)
		{
		case 'i':
			nArg = va_arg(args, int);
			lua_pushinteger(m_pState, nArg);			
			break;
		case 'd':
			dArg = va_arg(args, double);
			lua_pushnumber(m_pState, dArg);
			break;
		case 's':
			pString = va_arg(args, char*);
			lua_pushstring(m_pState, pString);			
			break;
		default:
			bRet = false;
			break;
		}
		if (!bRet)
		{
			break;
		}
		++iIndex;
	}
	va_end(args);	
	int ret = lua_pcall(m_pState, iIndex, 1, 0);
	if (ret != 0)
	{
		char szErrorMsg[256] = {0};
		CTools::Strcpy(szErrorMsg, lua_tostring(m_pState, -1), sizeof(szErrorMsg));
		AssertEx(false, "Call Scrit Error£º%s", szErrorMsg);
		lua_pop(m_pState, -1);
		return -1;
	}	
	return static_cast<int>(lua_tonumber(m_pState, -1));
	
	/*lua_pushinteger(m_pState, iParam1);
	lua_pushinteger(m_pState, iParam2);

	int ret = lua_pcall(m_pState, 2, 1, 0);
	if (ret != 0)
	{
	return -1;
	}	
	return static_cast<int>(lua_tonumber(m_pState, -1));*/
}