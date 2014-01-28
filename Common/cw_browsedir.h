#ifndef CW_BROWSE_DIR_H
#define CW_BROWSE_DIR_H
#include "cw_commondefine.h"
#include "cw_const.h"

class CBrowseDir
{
public:
	bool Init(const char* dir, const char* fileName);
	void BrowseDir();
	int  GetFileCount(){ return m_FileCount; }
	const char* GetFileFullPath(){ return m_FileFullPath; }
protected:

private:
	void __CleanUp();
	bool __BrowseDir(const char* dir, const char* filename);	//��dirĿ¼�µݹ�ʽѰ��filename�ļ�����¼�ܵ��ļ����������һ�����ļ������ļ�ȫ·��
	void __BeginBrowseDir();
	void __EndBrowseDir();
private:
	char m_Dir[MAX_FILE_PATH];		//Ҫ������Ŀ¼
	char m_FileName[MAX_FILE_NAME_LEN]; //Ҫ�������ļ���
	int  m_FileCount;					//���ļ����������ļ�����
	char m_FileFullPath[MAX_FILE_PATH];//���һ�����ļ������ļ�ȫ·��
};


#endif