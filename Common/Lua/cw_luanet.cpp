#include "cw_luanet.h"
#ifdef _SERVER_
#include "cw_connectionmanager.h"
#endif
#ifdef _CLIENT_
#include "cw_serverconnection.h"
#endif
#include "cw_connection.h"
#include "cw_tools.h"
#include "cw_testdata.h"
#include "cw_luapacket.h"

char* g_VarData = 0;

const int VAR_DATA_LEN = 200*1024;

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
	{"IsServer", lua_IsServer},

	{NULL, NULL}
};

int luaopen_net(lua_State *L)
{
	luaL_register(L, "net", netlib);	
	g_VarData = new char[VAR_DATA_LEN];
	memset(g_VarData, 0, VAR_DATA_LEN);
	return 1;
}

int lua_IsServer(lua_State *L)
{
#ifdef _SERVER_
	lua_pushnumber(L, 1);
#else
	lua_pushnumber(L, 0);
#endif
	return 1;
}

int Lua_DelConn(lua_State *L)
{
#ifdef _SERVER_
	int iSocket = static_cast<int>(lua_tonumber(L, 1));
	CConnectionManager::GetSingleton().DelConn(iSocket);
#endif
#ifdef	_CLIENT_
	CServerConnection::GetSingleton().CloseConn();
#endif	
	return 0;
}
int Lua_GetSocketSendBuff(lua_State *L)
{
#ifdef _SERVER_
	int iSocket = static_cast<int>(lua_tonumber(L, 1));
	CConnection* pConn = CConnectionManager::GetSingleton().GetConn(iSocket);
	if (!pConn)
	{
		return 0;
	}
	lua_pushlightuserdata(L, pConn->GetSendBuff());
#endif
#ifdef	_CLIENT_
	lua_pushlightuserdata(L, CServerConnection::GetSingleton().GetSendBuff());
#endif	
	return 1;
}
int Lua_GetSocketRecvBuff(lua_State *L)
{
#ifdef _SERVER_
	int iSocket = static_cast<int>(lua_tonumber(L, 1));
	CConnection* pConn = CConnectionManager::GetSingleton().GetConn(iSocket);
	if (!pConn)
	{
		return 0;
	}
	lua_pushlightuserdata(L, pConn->GetRecvBuff());
#endif
#ifdef	_CLIENT_
	lua_pushlightuserdata(L, CServerConnection::GetSingleton().GetRecvBuff());
#endif
	return 1;
}

int Lua_MapBuff(lua_State *L)
{
	CSocketBuff* pBuff = static_cast<CSocketBuff*>(lua_touserdata(L, 1));
	const char* strVarType = lua_tostring(L, 2);	
	if (strcmp(strVarType, "INT") == 0)
	{
		int iRet = 0;
		bool bRet = pBuff->PeekBuff((char*)(void *)&iRet, sizeof(iRet));
		if (!bRet)
		{
			return 0;
		}
		lua_pushnumber(L, 1);
		lua_pushnumber(L, iRet);
		return 2;
	}
	else if (strcmp(strVarType, "STRING") == 0)
	{
		short	iStrLen = 0;
		bool bRet = pBuff->PeekBuff((char*)(void *)&iStrLen, sizeof(iStrLen));
		if (!bRet)
		{
			return 0;
		}
		if (iStrLen <= 0)
		{
			lua_pushnumber(L, 1);
			lua_pushstring(L, "");
			return 2;
		}
		else
		{
			char szTmp[256] = {};
			bRet = pBuff->PeekBuff(szTmp, iStrLen);
			if (!bRet)
			{
				return 0;
			}
			lua_pushnumber(L, 1);
			lua_pushstring(L, szTmp);
			return 2;
		}
	}
	else
	{
		int iDataLen = 0;
		bool bRet = pBuff->PeekBuff((char*)(void *)&iDataLen, sizeof(iDataLen));
		if (!bRet)
		{
			return 0;
		}
		if (iDataLen <= 0)
		{
			lua_pushnumber(L, 1);
			lua_pushlightuserdata(L, NULL);
			return 2;
		}
		else
		{
			bRet = pBuff->PeekBuff((char*)(void *)g_VarData, iDataLen);		
			if (!bRet)
			{
				return 0;
			}
			lua_pushnumber(L, 1);
			lua_pushlightuserdata(L, (void *)g_VarData);
			return 2;
		}		
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
		pBuff->FillString(szTmp, CTools::Strlen(szTmp));
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
		pBuff->Fill((char*)&iLen, sizeof(iLen));
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
