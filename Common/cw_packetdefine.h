#ifndef CW_PACKETDEFINE_H
#define CW_PACKETDEFINE_H
enum EM_PACKET_TYPE
{
	EM_PACKET_TYPE_INVALID = -1,
	EM_PACKET_TYPE_START = 10000,
	EM_PACKET_TYPE_CSMONSTER = EM_PACKET_TYPE_START,
	EM_PACKET_TYPE_SCMONSTER,

	EM_PACKET_TYPE_NUMBER
};


#endif