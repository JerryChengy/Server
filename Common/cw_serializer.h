#ifndef CW_SERIALIZER_H
#define CW_SERIALIZER_H
#include "cw_commondefine.h"
#include "cw_const.h"
#include "cw_singleton.h"
class CSerializer
{
public:
	virtual CSerializer& operator<<(int& val) = 0;
	virtual CSerializer& operator<<(float& val) = 0;
	virtual CSerializer& operator<<(IntArray& val) = 0;
	virtual CSerializer& operator<<(char*& val) = 0;
protected:
private:
};
//数据整理
class CLineDataDisposer
{
public:
	bool Init(const char* pLine, char cSplitChar);	
	int  MoveBlock();
	const char* NextBlock();

public:
	char m_BlockData[MAX_BLOCK_CHAR_COUNT];
protected:
private:
	char m_LineData[MAX_LINE_CHAR_COUNT];	
	char* m_pCurLineChar;
	char* m_pCurBlockChar;	
	char  m_SplitChar;
};

#endif