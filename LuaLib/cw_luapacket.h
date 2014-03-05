#ifndef CW_LUAPACKET_H
#define CW_LUAPACKET_H

int			InitLuaPacketData(int iPacketID);
void		SetLuaPacketIData(int iIndex, int iVal);
void		SetLuaPacketSData(int iIndex, const char* szVal);
void		SetLuaPacketPData(int iIndex, void* pVal );
void		SendLuaPacket(int iSocket);
#endif