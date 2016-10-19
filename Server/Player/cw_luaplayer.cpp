#include "cw_luafunc.h"
#include "cw_player.h"
#include "cw_luapacket.h"
#include "cw_testdata.h"
#include "cw_log.h"

static const luaL_Reg playerlib[] = 
{
	{"GetPlayer", Lua_GetPlayer},
	{"GetLevel", Lua_GetPlayerLevel},
	{"SendSCTestPacket", Lua_SendSCTestPacket},
	{"HandleCSPlayerPacket", Lua_HandleCSPlayerPacket},

	{NULL, NULL}
};

int luaopen_player(lua_State *L)
{
	luaL_register(L, "player", playerlib);
	return 1;
}


int Lua_GetPlayer(lua_State *L)
{
	const char* pFuncName = lua_tostring(L, 1);
	/*lua_pushlightuserdata(L, g_Player);
	return 1;*/
	lua_pushcclosure(L, Lua_GetPlayerLevel, 0);
	return 1;
}

int Lua_GetPlayerLevel(lua_State *L)
{
	/*CPlayer *pPlayer = static_cast<CPlayer *>(lua_touserdata(L, 1));
	if (!pPlayer)
	{
		return 0;
	}
	lua_pushnumber(L, pPlayer->GetLevel());*/
	int p1 = static_cast<int>(lua_tonumber(L, 1));
	int p2 = static_cast<int>(lua_tonumber(L, 2));
	int p3 = static_cast<int>(lua_tonumber(L, 3));
	int res = p1 + p2 + p3;
	lua_pushnumber(L, res);
	return 1;
}

int Lua_SendSCTestPacket(lua_State *L)
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
	SetLuaPacketSData(2, "sctestpacket");
	PacketHumanData data;
	data.m_Data.m_ID = 999;
	SetLuaPacketPData(3, &data);
	SendLuaPacket(iSocket);
	return 0;
}

int Lua_HandleCSPlayerPacket(lua_State *L)
{
	if (!lua_isnumber(L, 1) || !lua_isnumber(L, 2))
	{
		return 0;
	}
	if (!lua_isuserdata(L, 3))
	{
		return 0;
	}
	int iVar1 = lua_tointeger(L, 1);
	int iVar2 = lua_tointeger(L, 2);
	const HumanData* pHumanData = (const HumanData*)lua_touserdata(L, 3);
	if (!pHumanData)
	{
		return 0;
	}
	LOG_DEBUG("p1: %d", iVar1);
	LOG_DEBUG("p2: %d", iVar2);
	LOG_DEBUG("p3: %d", pHumanData->m_ID);
	return 0;
}