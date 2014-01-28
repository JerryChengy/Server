#ifndef CW_INIBASE_H
#define CW_INIBASE_H
#include "cw_commondefine.h"


struct INI_BASE 
{
public:
	bool Init(const char* pFileName, const char* pKeyStr);
	bool Load(const char* pFileName, const char* pKeyStr);
	void Release();
	void Read(const char* pVarName, int& VarValue);
	void Read(const char* pVarName, float& VarValue);
	void Read(const char* pVarName, char*& pVarValue);
	virtual void ReadData(){};
private:	
	bool IsKeyLine(const char* pLine);
	void DelSpaceAndTab(const char* pSrcBuf, char* pDestBuf, int nDestLen);
	void GetVarValStr(const char* pVarName);

};


#endif