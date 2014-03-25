#ifndef CW_TEMPLATEMANAGER_H
#define CW_TEMPLATEMANAGER_H
#include "cw_dbheader.h"
#include "cw_singleton.h"
class CDBTemplate;
class CMemoryReader;
class CMemoryWriter;

class CTemplateManager: public Singleton(CTemplateManager)
{
public:
	CTemplateManager();
	~CTemplateManager();
public:
	bool	Register(const char* pTemplateName, CDBTemplate* pTemplate, int iDataLen);
	bool	RegisterAll();
protected:
private:
	bool	_Resize();
private:
	CDBTemplate*			m_pTemplateArray;
	int						m_TemplateCount;
	int						m_MaxTemplateCount;
};

#endif