#ifndef CW_SOCKET_BUFF_H
#define CW_SOCKET_BUFF_H
#include "cw_commondefine.h"
#include "cw_socketdef.h"

class CSocketBuff
{
public:
	CSocketBuff(int iBuffLen);
	~CSocketBuff();

	//缓冲区空间不够，扩充
	char*			ResizeBuff(char* buff, int& curMaxLen, int& iHead, int& iTail, int minLen);

	//往缓冲区里填充数据
	void			Fill(const char* pBuff, int iBuffLen);

	void			BeginParse();
	void			EndParse();
	void			Recover(){ m_iHead = m_iOldHead; m_iTail = m_iOldTail; }

	bool			PeekBuff(char* pBuff, int iBuffLen);

	void			SetSocket(SOCKET s){ m_Socket = s; }

	void			Clear(){ m_iHead = -1; m_iTail = -1; }
	bool			Flush();
protected:
private:
	char*		m_Buff;
	int			m_BuffLen;

	int			m_iHead;
	int			m_iTail;
	int			m_iOldHead;
	int			m_iOldTail;
	int			m_Socket;
};

#endif
