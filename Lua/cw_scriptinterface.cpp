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
	return CLuaInterface::GetSingleton().Init();
}

bool CScriptInterface::Load()
{
	int nRowCount = Tables.m_Script.RowCount();
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
			AssertEx(false, "Script File Load Failed: %s", pRowScript->m_ScriptFileName);
			return false;
		}
	}
	return true;
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
