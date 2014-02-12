#ifndef CW_STRINGHASHTABLE_H
#define CW_STRINGHASHTABLE_H

class CStringHashTable
{
public:
	static const int MAX_STR_LEN = 512;
public:
	struct Node 
	{
		char	m_Key[MAX_STR_LEN];
		int		m_Value;
		Node(){ m_Key[0] = '\0';m_Value = -1;}
	};
protected:
private:

	Node*		m_pNode;
};
#endif