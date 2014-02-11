#ifndef CW_CLEARSERIALIZER_H
#define CW_CLEARSERIALIZER_H

#include "cw_commondefine.h"
#include "cw_serializer.h"

class CClearSerializer: public CSerializer
{
public:
	CClearSerializer& operator<<(int& val) { val = 0; return *this; };
	CClearSerializer& operator<<(float& val){ val = 0.0f; return *this; };
	CClearSerializer& operator<<(IntArray& val){ return *this; };
	CClearSerializer& operator<<(char*& val){ val = 0; return *this; };
protected:
private:
};

#endif