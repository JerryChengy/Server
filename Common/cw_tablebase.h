#ifndef CW_TABLEBASE_H
#define CW_TABLEBASE_H
#include "cw_commondefine.h"
#include "cw_tablereader.h"
#include "cw_singleton.h"
#include "cw_const.h"

struct IntArray;
struct TABLE_BASE 
{
	bool Init(const char* pLine);
	void In(int& para);
	void In(char*& para);
	void In(IntArray& para);
	void In(float &para);
	virtual void ReadTable(){}
	TABLE_BASE()
	{
		m_ID = -1;
	}
	int  m_ID;
	static bool smTableGood;
};

//数据整理
class CLineDataDisposer: public Singleton<CLineDataDisposer>
{
public:
	bool Init(const char* pLine);	
	int  MoveBlock();

public:
	char m_BlockData[MAX_BLOCK_CHAR_COUNT];
protected:
private:
	char m_LineData[MAX_LINE_CHAR_COUNT];	
	char* m_pCurLineChar;
	char* m_pCurBlockChar;	
};
#define g_pLineDataDisposer CLineDataDisposer::GetSingletonPtr()
struct IntArray 
{
	IntArray()
	{
		m_pInt=NULL;
		m_Count = 0;
	}
	void Init()
	{
		if (m_Count>0)
		{
			SAFE_DELETE(m_pInt);
			m_pInt = new int[m_Count];
		}
	}
	int& operator[](int iIndex)
	{
		return m_pInt[iIndex];
	}
	void SetCount(int nCount){ m_Count = nCount; }
	int	 GetCount(){return m_Count;}
private:
	int* m_pInt;
	int m_Count;
};

#endif