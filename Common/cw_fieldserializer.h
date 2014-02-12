#ifndef CW_FIELDSERIALIZER_H
#define CW_FIELDSERIALIZER_H
#include "cw_serializer.h"
struct lua_State;
class CFieldSerializer: public CSerializer
{
public:
	CFieldSerializer()
	{
		m_DesColumnIndex = -1;
		m_CurrentColumnIndex = -1;
	}
public:
	CFieldSerializer& operator<<(int& val);
	CFieldSerializer& operator<<(float& val);
	CFieldSerializer& operator<<(IntArray& val);
	CFieldSerializer& operator<<(char*& val);

	void		SetDesColumnIndex(int nIndex){ m_DesColumnIndex = nIndex; }

	void		PushLValue(lua_State* L, int& nResCount);

	void		Skip();
protected:
private:
	Table_Field			m_Field;
	int					m_DesColumnIndex;	//从0开始索引
	int					m_CurrentColumnIndex;//从0开始索引
};


#endif