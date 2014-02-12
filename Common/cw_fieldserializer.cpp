#include "cw_fieldserializer.h"
extern "C"
{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

};
CFieldSerializer& CFieldSerializer::operator<<(int& val)
{
	m_CurrentColumnIndex++;
	if (m_DesColumnIndex == m_CurrentColumnIndex)
	{
		m_Field.m_FieldType = Table_Field::FIELD_TYPE_INT;
		m_Field.m_FieldValue.m_iValue = val;
	}
	return *this;
}


CFieldSerializer& CFieldSerializer::operator<<(float& val)
{
	m_CurrentColumnIndex++;
	if (m_DesColumnIndex == m_CurrentColumnIndex)
	{
		m_Field.m_FieldType = Table_Field::FIELD_TYPE_FLOAT;
		m_Field.m_FieldValue.m_fValue = val;
	}
	return *this;
}


CFieldSerializer& CFieldSerializer::operator<<(char*& val)
{
	m_CurrentColumnIndex++;
	if (m_DesColumnIndex == m_CurrentColumnIndex)
	{
		m_Field.m_FieldType = Table_Field::FIELD_TYPE_STRING;
		m_Field.m_FieldValue.m_strValue = val;
	}
	return *this;
}


CFieldSerializer& CFieldSerializer::operator<<(IntArray& val)
{
	m_CurrentColumnIndex++;
	if (m_DesColumnIndex == m_CurrentColumnIndex)
	{
		m_Field.m_FieldType = Table_Field::FIELD_TYPE_INTARRAY;
		m_Field.m_FieldValue.m_MulIntValue = &val;
	}
	return *this;
}

void CFieldSerializer::PushLValue( lua_State* L, int& nResCount)
{
	switch (m_Field.m_FieldType)
	{
	case Table_Field::FIELD_TYPE_INT:
		lua_pushnumber(L, m_Field.m_FieldValue.m_iValue);
		nResCount++;
		break;
	case Table_Field::FIELD_TYPE_FLOAT:
		lua_pushnumber(L, m_Field.m_FieldValue.m_fValue);
		nResCount++;
		break;
	case Table_Field::FIELD_TYPE_STRING:
		lua_pushstring(L, m_Field.m_FieldValue.m_strValue);
		nResCount++;
		break;
	case Table_Field::FIELD_TYPE_INTARRAY:
		for (int i=0;i<m_Field.m_FieldValue.m_MulIntValue->GetCount();++i)
		{
			lua_pushnumber(L, m_Field.m_FieldValue.m_MulIntValue->GetValue(i));
			nResCount++;
		}		
		break;
	}
}

void CFieldSerializer::Skip()
{
	m_CurrentColumnIndex++;
}
