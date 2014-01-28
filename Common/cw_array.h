#ifndef CW_ARRAY
#define CW_ARRAY

template<typename T>
class Array
{
public:
	typedef size_t                         size_type;
public:
	Array(size_type size = 0);
	~Array();
public:
	T& operator[](size_type index);
	size_type size(){ return m_Size; }
protected:
private:
	size_type			m_Size;
	T*					m_NodeList;
};


#endif
