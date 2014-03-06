#ifndef CW_LUATABLEBASE_H
#define CW_LUATABLEBASE_H
#include "cw_tableset.h"
#include "cw_fieldserializer.h"

struct lua_State;
bool Check_LuaTblParam(lua_State *L);


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
#endif