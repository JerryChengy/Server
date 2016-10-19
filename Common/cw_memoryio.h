#ifndef CW_MEMORY_IO_H
#define CW_MEMORY_IO_H
#include "cw_commondefine.h"

class CMemoryIO
{
public:
	bool			Init(char* pSrcData, int iDataLen);
protected:
	char*			m_pData;
	int				m_CurLen;
	int				m_MaxLen;

};

class CMemoryReader: public CMemoryIO
{
public:
	bool			Read(char* pDesData, int iDataLen);
protected:
private:
};
class CMemoryWriter: public CMemoryIO
{
public:
	bool			Write(char* pSrcData, int iDataLen);
protected:
private:
};

#endif