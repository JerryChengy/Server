#include "cw_shmmanager.h"
#include "cw_shmplayer.h"

SINGLETONG_IMPLEMENTION(SHMManager);
bool SHMManager::Init()
{
	new SHMPlayer;
	if (!(SHMPlayer::GetSingleton().Init()))
	{
		return false;
	}

	return true;
}

void SHMManager::Exit()
{
	SHMPlayer::GetSingleton().Exit();
}
