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
	bool __BrowseDir(const char* dir, const char* filename);	//在dir目录下递归式寻找filename文件，记录总得文件个数和最后一个此文件名的文件全路径
	void __BeginBrowseDir();
	void __EndBrowseDir();
private:
	char m_Dir[MAX_FILE_PATH];		//要遍历的目录
	char m_FileName[MAX_FILE_NAME_LEN]; //要搜索的文件名
	int  m_FileCount;					//此文件名的所有文件个数
	char m_FileFullPath[MAX_FILE_PATH];//最后一个此文件名的文件全路径
};


#endif