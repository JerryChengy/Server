#include "cw_luafunc.h"
#include "cw_tableset.h"
#include "cw_fieldserializer.h"

bool Check_LuaTblParam(lua_State *L)
{
	if (!lua_isnumber(L, 1) || !lua_isstring(L, 2))
	{
		return false;
	}
	return true;
}

template<typename T>
int Lua_GetTblData(CTable<T>& table, lua_State *L)
{
	try
	{
		int nTblId = static_cast<int>(lua_tonumber(L, 1));
		const char* pColumnName = lua_tostring(L, 2);
		int iColumnIndex = table.GetColumnIndex(pColumnName);
		CFieldSerializer fSerializer;
		fSerializer.SetDesColumnIndex(iColumnIndex);
		T* pRow = table.Row(nTblId);
		if (!pRow)
		{
			return 0;
		}
		pRow->MapData(fSerializer);
		int nResCount = 0;
		fSerializer.PushLValue(L, nResCount);
		return nResCount;
	}
	catch (...)
	{
		return 0;
	}
	
}

int Lua_GetTestTblData(lua_State *L)
{
	if (!Check_LuaTblParam(L))
	{
		return 0;
	}
	return Lua_GetTblData(Tables.m_Test, L);	
}


