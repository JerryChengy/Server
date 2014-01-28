#ifndef CW_SOCKETDEF_H
#define CW_SOCKETDEF_H



#define BACK_LOG	10
#define MSGSIZE  1024
#define IP_SIZE  24
static const int PACKET_HEAD = 0xFEFEFEFE;

static const int ReceiveSocketBuffLen = 200*1024;
static const int SendSocketBuffLen = 200*1024;
typedef short PacketID;


#endif
