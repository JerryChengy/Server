#ifndef CW_INI_READER_H
#define CW_INI_READER_H
#include "cw_commondefine.h"
#include "cw_singleton.h"
#include "cw_const.h"

class CIniReader: public Singleton<CIniReader>
{
public:
	CIniReader();
public:
	bool Init(const char* pFileName, const char* pKeyStr);
	void Release();
	const char* GetLine();
	const char* GetVarBuf(){ return m_VarBuf; }
	void	SetVarBuf(const char* pBuf, int iLen);
	void ClearVarBuf();

	const char* GetWorkDir(){ return m_WorkDir; }
public:
	

protected:	
private:
	void __CleanUp();
	bool __FormFileFullPath();
	
private:
	fstream m_File;//文件对象
	char m_LineData[BUFF_LEN_128];
	char m_FileName[MAX_FILE_NAME_LEN];
	char m_FileFullPath[MAX_FILE_PATH];
	char m_VarBuf[BUFF_LEN_256];
	char m_WorkDir[MAX_FILE_PATH];
};


#endif