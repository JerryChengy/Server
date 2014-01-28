#include "cw_browsedir.h"
#include "cw_assert.h"
#include "cw_inireader.h"
#include "cw_tools.h"

bool CBrowseDir::Init(const char* dir, const char* fileName)
{
		__CleanUp();
	if (!dir || !fileName)
	{
		Assert(false);
		return false;
	}
	CTools::Strcpy(m_Dir, CIniReader::GetSingleton().GetWorkDir(), sizeof(m_Dir));
	//_getcwd(m_Dir, sizeof(m_Dir));
	if (_fullpath(m_Dir, dir, sizeof(m_Dir)) == NULL)
	{
		return false;
	}	
	int len = CTools::Strlen(m_Dir);
	if ( (len-1>=0)&&(len<sizeof(m_Dir))&&(m_Dir[len-1] != '\\') )
	{
		strncat(m_Dir, "\\", sizeof(m_Dir)-1);
	}
	CTools::Strcpy(m_FileName, fileName, sizeof(m_FileName)-1);
	m_FileName[MAX_FILE_NAME_LEN-1] = '\0';
	return true;
}

void CBrowseDir::__CleanUp()
{
		memset(m_Dir, 0, sizeof(m_Dir));
	memset(m_FileName, 0, sizeof(m_FileName));
	m_FileCount = 0;
	memset(m_FileFullPath, 0, sizeof(m_FileFullPath));
}

void CBrowseDir::BrowseDir()
{
		__BeginBrowseDir();
	__BrowseDir(m_Dir, m_FileName);
	__EndBrowseDir();
}
void CBrowseDir::__BeginBrowseDir()
{
		_chdir(m_Dir);
}

void CBrowseDir::__EndBrowseDir()
{
		_chdir(CIniReader::GetSingleton().GetWorkDir());
}
bool CBrowseDir::__BrowseDir(const char* dir, const char* filename)
{
		long hFile;
	_finddata_t fileinfo;
	if ((hFile=_findfirst(filename, &fileinfo)) != -1)
	{
		do 
		{
			if (!(fileinfo.attrib&_A_SUBDIR))
			{
				memset(m_FileFullPath, 0, sizeof(m_FileFullPath));
				_snprintf(m_FileFullPath, sizeof(m_FileFullPath)-1, "%s%s", dir, filename);
				m_FileCount++;
			}
		} while (_findnext(hFile, &fileinfo)==0);
		_findclose(hFile);
	}
	if ((hFile=_findfirst("*.*", &fileinfo)) != -1)
	{
		do 
		{
			if (fileinfo.attrib&_A_SUBDIR)
			{
				if (strcmp(fileinfo.name, ".")!=0&&
					strcmp(fileinfo.name, "..")!=0)
				{
					char subdir[MAX_FILE_PATH] = {0};
					CTools::Strcpy(subdir, dir, sizeof(subdir)-1);
					strncat(subdir, fileinfo.name, sizeof(subdir)-1);
					strncat(subdir, "\\", sizeof(subdir)-1);
					if (!__BrowseDir(subdir, filename))
					{
						return false;					
					}

				}
			}
		} while (_findnext(hFile, &fileinfo)==0);
		_findclose(hFile);
	}
	return true;
}
