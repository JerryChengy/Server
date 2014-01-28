/**
* 加载表格数据到内存中
* 模板类
*/
#ifndef __CW_TABLE_H__
#define __CW_TABLE_H__
#include "cw_commondefine.h"
#include "cw_tablereader.h"
#include "cw_tablebase.h"
#include "cw_assert.h"
template<class T>
class CTable
{
public:
	void Print()
	{
		for (int i=0;i<m_LineCount;i++)
		{
			m_pRow[i].Print();
		}
	}
	T* GetRowByIndex(int nIndex)
	{
		if (nIndex >= m_LineCount || nIndex < 0 || m_LineCount<=0)
		{
			Assert(false);
			return NULL;
		}
		return &m_pRow[nIndex];
	}
	T* Row(int nID)
	{
		int nUpIndex = m_LineCount;
		int nDownIndex = 0;
		int nIndex = (nUpIndex+nDownIndex)/2;
		while (nUpIndex >= nDownIndex)
		{
			if (m_pRow[nIndex].m_ID > nID)
			{
				nUpIndex = nIndex-1;
			}
			else if (m_pRow[nIndex].m_ID < nID)
			{
				nDownIndex = nIndex+1;
			}
			else
			{
				break;
			}
			nIndex = (nUpIndex+nDownIndex)/2;
		}
		if (m_pRow[nIndex].m_ID != nID)
		{
			return NULL;
		}
		return &m_pRow[nIndex];
	}
	/*!
	\brief
		初始化，将磁盘文件数据加载到内存中
	*/
	bool Init(const char* pFileName)
	{
		__CleanUp();
		if (!m_TableReader.Init(pFileName))
		{
			return false;
		}
		int nLineCount = m_TableReader.GetLineCount();
		if (nLineCount <= HEAD_LINE_COUINT)
		{
			return true;
		}		
		m_LineCount = nLineCount - HEAD_LINE_COUINT;
		m_pRow = new T[m_LineCount];		
		__SkipHeader();
		for (int i=0;i<m_LineCount;++i)
		{
			const char* pLine = m_TableReader.GetLine();			
			if (!m_pRow[i].Init(pLine))
			{
				Assert(false);
			}
			m_pRow[i].ReadTable();
		}
		if (!__CheckTableID())
		{
			m_TableReader.Release();
			return false;
		}
		m_TableReader.Release();		
		return true;
	}
	bool IsHaveRow(int nID)
	{
		T* pTableRow = Row(nID);
		if (!pTableRow)
		{
			return false;
		}
		return true;
	}
	int RowCount(){ return m_LineCount; }

private:
	bool __CheckTableID()
	{
		for (int i=0;i<m_LineCount-1;i++)
		{
			if (m_pRow[i].m_ID>=m_pRow[i+1].m_ID)
			{
				AssertEx(false, "File: %s; PrevLine: %d; NextLine: %d.", m_TableReader.GetFileFullPath(), i+1, i+2);
				return false;
			}
		}
		return true;
	}
	inline void __SkipHeader()
	{
		for (int i=0;i<HEAD_LINE_COUINT;++i)
		{
			m_TableReader.GetLine();
		}
	}
private:
	void __CleanUp()
	{
		m_pRow = NULL;		
		m_LineCount = 0;
	}
private:
	T* m_pRow;	
	int m_LineCount;
	CTableReader m_TableReader;
};
#endif