#include "cw_scriptinterface.h"
#include "cw_luainterface.h"
#include "cw_tableset.h"
#include "cw_assert.h"

SINGLETONG_IMPLEMENTION(CScriptInterface)

CScriptInterface::CScriptInterface()
{
	new CLuaInterface;
}

bool CScriptInterface::Init()
{
	bool bRet = CLuaInterface::GetSingleton().Init();
	if (!bRet)
	{
		return false;
	}
	bRet = Load();
	if (!bRet)
	{
		return false;
	}
	return true;
}

bool CScriptInterface::Load()
{
	int nRowCount = Tables.m_PublicScript.RowCount();
	for (int i=0;i<nRowCount;++i)
	{
		TABLE_SCRIPT* pRowScript = Tables.m_PublicScript.GetRowByIndex(i);
		if (!pRowScript)
		{
			break;
		}
		bool bRet = CLuaInterface::GetSingleton().Load(pRowScript->m_ScriptFileName);
		if (!bRet)
		{
			AssertEx(false, "Public Script File Load Failed: %s", pRowScript->m_ScriptFileName);
			return false;
		}
	}
#ifdef _SERVER_
	nRowCount = Tables.m_Script.RowCount();
	for (int i=0;i<nRowCount;++i)
	{
		TABLE_SCRIPT* pRowScript = Tables.m_Script.GetRowByIndex(i);
		if (!pRowScript)
		{
			break;
		}
		bool bRet = CLuaInterface::GetSingleton().Load(pRowScript->m_ScriptFileName);
		if (!bRet)
		{
			AssertEx(false, "Server Script File Load Failed: %s", pRowScript->m_ScriptFileName);
			return false;
		}
	}
#endif
	return true;
}

int CScriptInterface::CallScript( int iScriptID, const char* pFuncName)
{
	char szFuncName[64] = {};
	_snprintf_s(szFuncName, sizeof(szFuncName)-1, "x%06d_%s", iScriptID, pFuncName);
	return CLuaInterface::GetSingleton().CallScript(szFuncName, "");
}

int CScriptInterface::CallScript( int iScriptID, const char* pFuncName, int iArg1, int iArg2, int iArg3 )
{
	char szFuncName[64] = {};
	_snprintf_s(szFuncName, sizeof(szFuncName)-1, "x%06d_%s", iScriptID, pFuncName);
	return CLuaInterface::GetSingleton().CallScript(szFuncName, "iii", iArg1, iArg2, iArg3);
}
int CScriptInterface::CallScript( int iScriptID, const char* pFuncName, int iArg1 )
{
	char szFuncName[64] = {};
	_snprintf_s(szFuncName, sizeof(szFuncName)-1, "x%06d_%s", iScriptID, pFuncName);
	return CLuaInterface::GetSingleton().CallScript(szFuncName, "i", iArg1);
}
int CScriptInterface::CallScript( int iScriptID, const char* pFuncName, int iArg1, const char* szArg2 )
{
	char szFuncName[64] = {};
	_snprintf_s(szFuncName, sizeof(szFuncName)-1, "x%06d_%s", iScriptID, pFuncName);
	return CLuaInterface::GetSingleton().CallScript(szFuncName, "is", iArg1, szArg2);
}
int CScriptInterface::CallScript( int iScriptID, const char* pFuncName, int iArg1, void* pArg2 )
{
	char szFuncName[64] = {};
	_snprintf_s(szFuncName, sizeof(szFuncName)-1, "x%06d_%s", iScriptID, pFuncName);
	return CLuaInterface::GetSingleton().CallScript(szFuncName, "ip", iArg1, pArg2);
}
int CScriptInterface::CallScript( int iScriptID, const char* pFuncName, int iArg1, int iArg2 )
{
	char szFuncName[64] = {};
	_snprintf_s(szFuncName, sizeof(szFuncName)-1, "x%06d_%s", iScriptID, pFuncName);
	return CLuaInterface::GetSingleton().CallScript(szFuncName, "ii", iArg1, iArg2);
}


int CScriptInterface::CallScript( int iScriptID, const char* pFuncName, double dArg1, double dArg2 )
{
	char szFuncName[64] = {};
	_snprintf_s(szFuncName, sizeof(szFuncName)-1, "x%06d_%s", iScriptID, pFuncName);
	return CLuaInterface::GetSingleton().CallScript(szFuncName, "dd", dArg1, dArg2);
}
