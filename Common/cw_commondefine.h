#ifndef CW_COMMONDEFINE_H
#define CW_COMMONDEFINE_H

#define FD_SETSIZE 1024
#include <WinSock2.h>
#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <direct.h>
#include <time.h>
#include <fstream>
#include <io.h>
#include <iostream>
#include <sys/stat.h>
#include <stdlib.h>
#include <map>
#include <vector>
using namespace std;

#pragma warning(disable: 4996)
#pragma warning(disable: 4018)


#define SAFE_DELETE(X) {delete X; X=0;}
#define SAFE_DELETEARRAY(X){ delete [] X; X = 0;}
typedef vector<string> MUL_STRING;
typedef vector<int>	MUL_INT;
typedef unsigned int		UINT;

#if defined (_WIN32_)
	typedef void*	SM_Handle;
	typedef unsigned int SM_KEY;
#elif defined (_LINUX64_)
	typedef int		SM_Handle;
	typedef key_t   SM_KEY;
#endif
struct IntArray 
{
	IntArray()
	{
		m_pInt=0;
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
	int& operator[](int iIndex) const
	{
		return m_pInt[iIndex];
	}
	int GetValue(int iIndex) const
	{
		return m_pInt[iIndex];
	}
	IntArray& operator=(const IntArray& val)
	{
		m_Count = val.GetCount();
		Init();
		for (int i=0;i<m_Count;++i)
		{
			m_pInt[i] = val[i];
		}
		return *this;
	}
	void SetCount(int nCount){ m_Count = nCount; }
	int	 GetCount() const {return m_Count;}
private:
	int* m_pInt;
	int m_Count;
};

struct Table_Field 
{
	enum FIELD_TYPE
	{
		FIELD_TYPE_INVALID = -1,
		FIELD_TYPE_INT,
		FIELD_TYPE_FLOAT,
		FIELD_TYPE_STRING,
		FIELD_TYPE_INTARRAY
	};
	FIELD_TYPE		m_FieldType;
	union FieldValue
	{
		int		m_iValue;
		float	m_fValue;
		const char* m_strValue;
		IntArray* m_MulIntValue;
	};
	FieldValue		m_FieldValue;
	Table_Field()
	{
		m_FieldType = FIELD_TYPE_INVALID;		
	}
};
//#define Assert(x) if(x) { Ass}
#endif