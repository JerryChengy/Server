#ifndef CW_SINGLETON_H
#define CW_SINGLETON_H
#include "cw_commondefine.h"
template<typename T>
class Singleton
{
public:
	Singleton()
	{
		if (sm_Singleton)
		{
			throw 1;
		}
		sm_Singleton = static_cast<T*>(this);
	}
public:
	static T*	GetSingletonPtr(){ return sm_Singleton; }
	static T&  GetSingleton(){ return * sm_Singleton; }
protected:
public:
	static T*	sm_Singleton;
};

#define SINGLETONG_IMPLEMENTION(Class) Class* Singleton<Class>::sm_Singleton = 0;
#endif
