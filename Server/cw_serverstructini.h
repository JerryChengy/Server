#ifndef CW_SERVERSTRUCTINI_H
#define CW_SERVERSTRUCTINI_H
#include "cw_inibase.h"
#include "cw_const.h"

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

struct INI_SHM:INI_BASE 
{
	int m_Key;
	int m_Size;
	void ReadData()
	{
		Read("key", m_Key);
		Read("size", m_Size);
	}
};


struct INI_DB:INI_BASE 
{	
	char*	m_IP;
	int		m_Port;
	char*	m_DBName;
	char*	m_UserName;
	char*	m_Password;
	void ReadData()
	{
		Read("ip", m_IP);
		Read("port", m_Port);
		Read("name", m_DBName);
		Read("username", m_UserName);
		Read("pwd", m_Password);
	}
};
#endif