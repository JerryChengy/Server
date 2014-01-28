#ifndef CW_TABLE_READER_H
#define CW_TABLE_READER_H
#include "cw_commondefine.h"
#include "cw_const.h"

class CTableReader
{
public:
	//CTableReader();
	//~CTableReader();	
	bool Init(const char* pFileName);//初始化表格阅读器	
	const char* GetFileFullPath(){ return m_FileFullPath; }	
	bool IsEof();
	const char* GetLine();
	bool Release();
	int  GetLineCount(){ return m_LineCount; }
protected:
private:
	void __CleanUp();//清除成员数据
	bool __FormFileFullPath();//根据文件名搜索并得到文件全路径
	int  __GetColumnCount(char* pLineBuf);//获取表格列数	
	void __CalcLineCount();//计算并设置文件行数		


private:	
	fstream m_File;//文件对象
	char m_LineData[MAX_LINE_CHAR_COUNT];
	char m_FileName[MAX_FILE_NAME_LEN];//文件名称
	char m_FileFullPath[MAX_FILE_PATH];//文件全路径	
	int  m_LineCount;
};

#endif