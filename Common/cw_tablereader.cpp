#include "cw_tablereader.h"
#include "cw_browsedir.h"
#include "cw_assert.h"

//表格数据存放目录（可以有多个目录）
const char* g_TableDirArray[]=
{
	".\\tables\\"
};

bool CTableReader::Init(const char* pFileName)
{
		__CleanUp();	
	Assert(pFileName);
	if (!pFileName)
	{
		return false;
	}
	strncpy(m_FileName, pFileName, sizeof(m_FileName)-1);
	m_FileName[sizeof(m_FileName)-1] = '\0';
// 	if (!__FormFileFullPath())
// 	{
// 		AssertEx(false, "TableReader Init Fail: %s", pFileName);
// 		return false;
// 	}
	__CalcLineCount();	
	m_File.open(m_FileName, ios_base::in);
	if (!m_File)
	{
		return false;
	}
	return true;
}

const char* CTableReader:: GetLine()
{
		m_File.getline(m_LineData, sizeof(m_LineData), '\n');
	while(m_LineData[0]=='#' && !m_File.eof())
	{
		memset(m_LineData, 0, sizeof(m_LineData));
		m_File.getline(m_LineData, sizeof(m_LineData), '\n');
	}	
	if (strlen(m_LineData)==0)
	{
		return NULL;
	}
	return m_LineData;
}

bool CTableReader::Release()
{
		m_File.close();
	__CleanUp();
	return true;
}
void CTableReader::__CleanUp()
{
		memset(m_FileName, 0, sizeof(m_FileName));
	memset(m_FileFullPath, 0, sizeof(m_FileFullPath));	
	m_LineCount = 0;
	memset(m_LineData, 0, sizeof(m_LineData));
}
bool CTableReader::IsEof()
{
		return m_File.eof();
}
bool CTableReader::__FormFileFullPath()
{
		int nFileCount = 0;
	int nFileDirArrayCount = sizeof(g_TableDirArray)/sizeof(char*);
	for (int i=0;i<nFileDirArrayCount;++i)
	{
		CBrowseDir iBrowseDir;
		if (!iBrowseDir.Init(g_TableDirArray[i], m_FileName))
		{
			AssertEx(false, "TableFileDir Error: %s", g_TableDirArray[i]);
			return false;
		}
		iBrowseDir.BrowseDir();
		if (iBrowseDir.GetFileCount()>0)
		{
			nFileCount += iBrowseDir.GetFileCount();
			strncpy(m_FileFullPath, iBrowseDir.GetFileFullPath(), sizeof(m_FileFullPath)-1);
			m_FileFullPath[sizeof(m_FileFullPath)-1] = '\0';
		}		
	}
	if (nFileCount > 1)
	{
		AssertEx(false, "FileName duplicate, name:%s, count:%d", m_FileName, nFileCount);
		return false;
	}	
	return true;
}

void CTableReader::__CalcLineCount()
{
		m_LineCount = 0;
	fstream file;
	file.open(m_FileName, ios_base::in);
	if (!file)
	{
		AssertEx(false, "Open file\"%s\" fail!!!", m_FileName);
		file.close();
		return ;
	}
	char szTmpBuf[BUFF_LEN_16K] = "";
	int nLineCount = 0;
	while (!file.eof())
	{
		file.getline(szTmpBuf, sizeof(szTmpBuf), '\n');
		if (szTmpBuf[0] == '#')//注释行忽略
		{
			continue;
		}
		if (strlen(szTmpBuf) == 0)//空行后面的不解析
		{
			break;
		}
		nLineCount++;
		memset(szTmpBuf, 0, sizeof(szTmpBuf));
	}
	file.close();
	m_LineCount = nLineCount;
}