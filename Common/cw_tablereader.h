#ifndef CW_TABLE_READER_H
#define CW_TABLE_READER_H
#include "cw_commondefine.h"
#include "cw_const.h"

class CTableReader
{
public:
	//CTableReader();
	//~CTableReader();	
	bool Init(const char* pFileName);//��ʼ������Ķ���	
	const char* GetFileFullPath(){ return m_FileFullPath; }	
	bool IsEof();
	const char* GetLine();
	bool Release();
	int  GetLineCount(){ return m_LineCount; }
protected:
private:
	void __CleanUp();//�����Ա����
	bool __FormFileFullPath();//�����ļ����������õ��ļ�ȫ·��
	int  __GetColumnCount(char* pLineBuf);//��ȡ�������	
	void __CalcLineCount();//���㲢�����ļ�����		


private:	
	fstream m_File;//�ļ�����
	char m_LineData[MAX_LINE_CHAR_COUNT];
	char m_FileName[MAX_FILE_NAME_LEN];//�ļ�����
	char m_FileFullPath[MAX_FILE_PATH];//�ļ�ȫ·��	
	int  m_LineCount;
};

#endif