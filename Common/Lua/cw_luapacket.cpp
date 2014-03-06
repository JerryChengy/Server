#include "cw_luapacket.h"
#include "cw_scriptinterface.h"


int  GetLuaPacketID(const char* strFunc)
{
	if (!strFunc)
	{
		return -1;
	}
	return SCRIPTMANAGER.CallScript(5, strFunc);
}
void SetLuaPacketIData(int iIndex, int iVal )
{
	SCRIPTMANAGER.CallScript(3, "SetPacketData", iIndex, iVal);
}

void SetLuaPacketSData(int iIndex, const char* szVal )
{
	SCRIPTMANAGER.CallScript(3, "SetPacketData", iIndex, szVal);
}

void SetLuaPacketPData(int iIndex, void* pVal )
{
	SCRIPTMANAGER.CallScript(3, "SetPacketData", iIndex, pVal);
}

int InitLuaPacketData( int iPacketID )
{
	return SCRIPTMANAGER.CallScript(3, "InitPacketData", iPacketID);

}

void SendLuaPacket(int iSocket)
{
	SCRIPTMANAGER.CallScript(3, "SendPacket", iSocket);
}
