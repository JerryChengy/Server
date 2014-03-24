#ifndef CW_TEMPLATEMANAGER_H
#define CW_TEMPLATEMANAGER_H
#include "cw_dbheader.h"
class CDBTemplate;
class CMemoryReader;
class CMemoryWriter;

class CTemplateManager
{
public:
	CTemplateManager();
	~CTemplateManager();
public:
	bool	Register(const char*);
protected:
private:
};

#endif