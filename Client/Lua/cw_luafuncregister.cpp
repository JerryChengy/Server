#include "cw_luainterface.h"
#include "cw_luanet.h"
#include "cw_luafunc.h"

//ע��ȫ�ֺ���
void RegisterLuaFunc()
{
	lua_State* L = CLuaInterface::GetSingleton().m_pState;
}

void RegisterAllTable(lua_State* L)
{
	luaopen_net(L);
	luaopen_player(L);
}
