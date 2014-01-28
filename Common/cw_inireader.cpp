#include "cw_inireader.h"
#include "cw_browsedir.h"
#include "cw_const.h"
#include "cw_tools.h"
#include "cw_assert.h"

SINGLETONG_IMPLEMENTION(CIniReader);

const char* g_IniDirArray[]=
{
	".\\Config\\"	
};

CIniReader::CIniReader()
{
	memset(m_WorkDir, 0, sizeof(m_WorkDir));
	_getcwd(m_WorkDir, MAX_FILE_PATH);	
}

void CIniReader::Release()
{
	m_File.close();
	__CleanUp();
	
}

void CIniReader::__CleanUp()
{
		memset(m_LineData, 0, sizeof(m_LineData));
	memset(m_VarBuf, 0, sizeof(m_VarBuf));
	memset(m_FileFullPath, 0, sizeof(m_FileFullPath));
	memset(m_FileName, 0, sizeof(m_FileName));
}

bool CIniReader::__FormFileFullPath()
{
		int nFileCount = 0;
	int nFileDirArrayCount = sizeof(g_IniDirArray)/sizeof(char*);
	for (int i=0;i<nFileDirArrayCount;i++)
	{
		CBrowseDir iBrowseDir;
		if (!iBrowseDir.Init(g_IniDirArray[i], m_FileName))
		{
			AssertEx(false, "IniFileDir Error: %s", g_IniDirArray[i]);
			return false;
		}
		iBrowseDir.BrowseDir();
		if (iBrowseDir.GetFileCount()>0)
		{
			nFileCount += iBrowseDir.GetFileCount();
			strncpy_s(m_FileFullPath, iBrowseDir.GetFileFullPath(), MAX_FILE_PATH);
		}		
	}
	if (nFileCount > 1)
	{
		AssertEx(false, "FileName Duplicate: %s", m_FileName);
		return false;
	}	
	return true;
}

const char* CIniReader::GetLine()
{
	if (!m_File)
	{
		return NULL;
	}
	memset(m_LineData, 0, sizeof(m_LineData));
	m_File.getline(m_LineData, sizeof(m_LineData), '\n');
	return m_LineData;
}
bool CIniReader::Init(const char* pFileName, const char* pKeyStr)
{
		__CleanUp();
	if (!pFileName || !pKeyStr)
	{
		Assert(false);
		return false;
	}
	strncpy(m_FileName, pFileName, sizeof(m_FileName)-1);
// 	if (!__FormFileFullPath())
// 	{
// 		AssertEx(false, "IniReader Init Fail:%s", pFileName);
// 		return false;
// 	}
	m_File.open(m_FileName);
	if (!m_File)
	{
		AssertEx(false, "Open file\"%s\" fail!!!", pFileName);
		return false;
	}
	char szFullKeyStr[BUFF_LEN_128] = {};
	_snprintf(szFullKeyStr, sizeof(szFullKeyStr)-1, "[%s]", pKeyStr);
	char szBuf[BUFF_LEN_1024] = {};
	while (!m_File.eof())
	{
		m_File.getline(szBuf, sizeof(szBuf), '\n');
		if (NULL != strstr(szBuf, szFullKeyStr))
		{
			return true;
		}
		memset(szBuf, 0, sizeof(szBuf));
	}
	return false;
}

void CIniReader::SetVarBuf( const char* pBuf, int iLen )
{
	if (!pBuf)
	{
		return ;
	}
	CTools::Strcpy(m_VarBuf, pBuf, iLen);
}


void CIniReader::ClearVarBuf()
{
	memset(m_VarBuf, 0, sizeof(m_VarBuf));
}
