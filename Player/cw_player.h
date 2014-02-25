#ifndef CW_PLAYER_H
#define CW_PLAYER_H
#include "cw_commondefine.h"
#include "cw_const.h"

class CPlayer
{
public:
	CPlayer(){ CleanUp(); }
	void CleanUp()
	{
		m_Level = 0;
		memset(m_Name, 0, sizeof(m_Name));
	}
	void SetLevel(int val){ m_Level = val; }
	int	 GetLevel(){ return m_Level; }
protected:
private:
	int			m_Level;
	char		m_Name[MAX_NAME_LEN];
};
extern CPlayer* g_Player;
#endif
