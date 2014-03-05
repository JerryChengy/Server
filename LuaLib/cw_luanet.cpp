#include "cw_luafunc.h"
#include "cw_connectionmanager.h"
#include "cw_connection.h"
#include "cw_tools.h"
#include "cw_testdata.h"
#include "cw_luapacket.h"

static const luaL_Reg netlib[] = 
{
	{"DelConn", Lua_DelConn},
	{"GetSocketRecvBuff", Lua_GetSocketRecvBuff},
	{"MapBuff", Lua_MapBuff},
	{"RecoverBuff", Lua_RecoverBuff},
	{"EndParseBuff", Lua_EndParseBuff},
	{"GetSocketSendBuff", Lua_GetSocketSendBuff},
	{"FillBuff", Lua_FillBuff},
	{"PreFillBuff", Lua_PreFillBuff},
	{"SendTestPacket", Lua_SendTestPacket},
};

int luaopen_net(lua_State *L)
{
	luaL_register(L, "net", netlib);
	
	return 1;
}

int Lua_SendTestPacket(lua_State *L)
{
	if (!lua_isnumber(L, 1) || !lua_isnumber(L, 2))
	{
		return 0;
	}
	short iPacketID = (short)lua_tonumber(L, 1);
	int iSocket = (int)lua_tonumber(L, 2);
	int iRet = InitLuaPacketData(iPacketID);
	if (iRet == 0)
	{
		return 0;
	}
	SetLuaPacketIData(1, 30);
	SetLuaPacketSData(2, "haha");
	PacketHumanData data;
	data.m_Data.m_ID = 999;
	data.m_Data.m_Sex = 2;
	SetLuaPacketPData(3, &data);
	SendLuaPacket(iSocket);
	return 0;
}
int Lua_DelConn(lua_State *L)
{
	int iSocket = static_cast<int>(lua_tonumber(L, 1));
	CConnectionManager::GetSingleton().DelConn(iSocket);
	return 0;
}
int Lua_GetSocketSendBuff(lua_State *L)
{
	int iSocket = static_cast<int>(lua_tonumber(L, 1));
	CConnection* pConn = CConnectionManager::GetSingleton().GetConn(iSocket);
	if (!pConn)
	{
		return 0;
	}
	lua_pushlightuserdata(L, pConn->GetSendBuff());
	return 1;
}
int Lua_GetSocketRecvBuff(lua_State *L)
{
	int iSocket = static_cast<int>(lua_tonumber(L, 1));
	CConnection* pConn = CConnectionManager::GetSingleton().GetConn(iSocket);
	if (!pConn)
	{
		return 0;
	}
	lua_pushlightuserdata(L, pConn->GetRecvBuff());
	return 1;
}

int Lua_MapBuff(lua_State *L)
{
	CSocketBuff* pBuff = static_cast<CSocketBuff*>(lua_touserdata(L, 1));
	const char* strVarType = lua_tostring(L, 2);	
	if (strcmp(strVarType, "INT") == 0)
	{
		int iRet = 0;
		pBuff->PeekBuff((char*)(void *)&iRet, sizeof(iRet));
		lua_pushnumber(L, iRet);
		return 1;
	}
	else if (strcmp(strVarType, "STRING") == 0)
	{
		char szTmp[1024] = {};
		pBuff->PeekBuff((char*)(void *)&szTmp, sizeof(szTmp));
		lua_pushstring(L, szTmp);
		return 1;
	}
	
	return 0;
}

int Lua_FillBuff(lua_State *L)
{
	CSocketBuff* pBuff = static_cast<CSocketBuff*>(lua_touserdata(L, 1));
	const char* strVarType = lua_tostring(L, 2);	
	if (strcmp(strVarType, "INT") == 0)
	{
		if (!lua_isnumber(L, 3))
		{
			return 0;
		}
		int iData = (int)lua_tonumber(L, 3);
		pBuff->Fill((char*)(void *)&iData, sizeof(iData));
	}
	else if (strcmp(strVarType, "STRING") == 0)
	{
		if (!lua_isstring(L, 3))
		{
			return 0;
		}
		const char* szTmp = lua_tostring(L, 3);
		pBuff->Fill(szTmp, 32);
	}
	else 
	{
		void* pData = lua_touserdata(L, 3);
		if (!pData)
		{
			return 0;
		}
		int iLen;
		memcpy(&iLen, pData, sizeof(iLen));
		pBuff->Fill((char*)pData+sizeof(int), iLen);
	}
	return 0;
}

int Lua_PreFillBuff(lua_State *L)
{
	CSocketBuff* pBuff = static_cast<CSocketBuff*>(lua_touserdata(L, 1));
	short iPacketID = (short)(lua_tonumber(L, 2));
	if (!pBuff)
	{
		return 0;
	}
	int iPacketHead = PACKET_HEAD;
	pBuff->Fill(static_cast<char*>(static_cast<void*>(&iPacketHead)), sizeof(iPacketHead));
	pBuff->Fill(static_cast<char*>(static_cast<void*>(&iPacketID)), sizeof(iPacketID));
	return 0;
}
int Lua_RecoverBuff(lua_State *L)
{
	CSocketBuff* pBuff = static_cast<CSocketBuff*>(lua_touserdata(L, 1));
	if (!pBuff)
	{
		return 0;
	}
	pBuff->Recover();
	pBuff->EndParse();
	return 0;
}

int Lua_EndParseBuff(lua_State *L)
{
	CSocketBuff* pBuff = static_cast<CSocketBuff*>(lua_touserdata(L, 1));
	if (!pBuff)
	{
		return 0;
	}
	pBuff->EndParse();
	return 0;
}
