#include <test/cw_array.h>
#include <ace\Assert.h>
template<typename T> 
Array<T>::Array(size_type size)
	:m_Size(size)
{
	ACE_ASSERT(size>0);
	m_NodeList = new T[size];
}
template<typename T> 
Array<T>::~Array()
{
	delete[] m_NodeList;
}
template<typename T> 
T& Array<T>::operator [](size_type size)
{
	if (size < 0 || size >= m_Size)
	{
		ACE_ASSERT(0);
		return *(new T);
	}
	return m_NodeList[size];
}
