#ifndef CW_TABLESERIALIZER_H
#define CW_TABLESERIALIZER_H
#include "cw_commondefine.h"
#include "cw_serializer.h"

class CTableSerializer: public CSerializer
{
public:
	void			  Init(const char* pStrData);
	CTableSerializer& operator<<(int& val);
	CTableSerializer& operator<<(float& val);
	CTableSerializer& operator<<(IntArray& val);
	CTableSerializer& operator<<(char*& val);

	void Skip();
protected:
private:
	CLineDataDisposer	m_LineDisposer;
};

#endif