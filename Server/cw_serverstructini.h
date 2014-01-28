#ifndef CW_SERVERSTRUCTINI_H
#define CW_SERVERSTRUCTINI_H
#include "cw_inibase.h"

struct INI_TEST:INI_BASE
{
	int id;
	int length;
	float width;
	void ReadData()
	{
		Read("id", id);
		Read("length", length);
		Read("width", width);
	}

};

struct INI_SERVERNET:INI_BASE 
{
	int m_Port;
	int m_ReceiveSocketBuffLen ;
	int m_SendSocketBuffLen ;
	void ReadData()
	{
		Read("port", m_Port);
		Read("ReceiveSocketBuffLen", m_ReceiveSocketBuffLen);
		Read("SendSocketBuffLen", m_SendSocketBuffLen);
	}
};


#endif