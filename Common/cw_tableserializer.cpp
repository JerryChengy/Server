#include "cw_tableserializer.h"
#include "cw_assert.h"
#include "cw_tools.h"


void CTableSerializer::Init(const char* pStrData)
{
	m_LineDisposer.Init(pStrData, '\t');
}

CTableSerializer& CTableSerializer::operator<<(int& val)
{
	const char* pData = m_LineDisposer.NextBlock();
	if (!pData)
	{
		Assert(false);
		return *this;
	}
	bool bRet = CTools::StringToInt(pData, val);
	if (!bRet)
	{
		Assert(false);
	}
	return *this;
}


CTableSerializer& CTableSerializer::operator<<(float& val)
{
	const char* pData = m_LineDisposer.NextBlock();
	if (!pData)
	{
		Assert(false);
		return *this;
	}
	bool bRet = CTools::StringToFloat(pData, val);
	if (!bRet)
	{
		Assert(false);
	}
	return *this;
}


CTableSerializer& CTableSerializer::operator<<(char*& val)
{
	const char* pData = m_LineDisposer.NextBlock();
	if (!pData)
	{
		Assert(false);
		return *this;
	}
	int nStrLen = CTools::Strlen(pData);
	if (nStrLen == 0)
	{
		return *this;
	}
	val = new char[nStrLen+1];
	memset(val, 0, nStrLen+1);
	CTools::Strcpy(val, pData, nStrLen);
	return *this;
}


CTableSerializer& CTableSerializer::operator<<(IntArray& val)
{
	const char* pData = m_LineDisposer.NextBlock();
	if (!pData)
	{
		Assert(false);
		return *this;
	}
	MUL_INT tmpMulInt;
	bool bRet = CTools::SplitString(pData, tmpMulInt, '|');
	if (!bRet)
	{
		Assert(false);
		return *this;
	}
	val.SetCount(tmpMulInt.size());
	val.Init();
	for (int i=0;i<val.GetCount();++i)
	{
		val[i] = tmpMulInt[i];
	}
	return *this;
}