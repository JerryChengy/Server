#ifndef CW_COMMONHANDLER_H_
#define CW_COMMONHANDLER_H_

class CPacket;
class CConnection;



typedef int (*FuncHandler)(CPacket* pPacket, CConnection* pConnection);
#endif