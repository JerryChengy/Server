#ifndef CW_SHMPLAYER_H
#define CW_SHMPLAYER_H
#include "cw_shmpool.h"
#include "cw_shmunit.h"
#include "cw_singleton.h"
#include "cw_testdata.h"

typedef SMUnit<HumanData> SMUPlayer;
class SHMPlayer: public Singleton<SHMPlayer>
{
public:
	bool	Init();
	void	Exit();
	bool	GetPlayerData(HumanData& data, int iSMUIndex);
	bool	SetPlayerData(const HumanData& data, int iSMUIndex);
protected:
private:
	SHMPool<SMUPlayer>	m_Pool;
};

#endif