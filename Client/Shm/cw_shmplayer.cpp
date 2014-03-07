#include "cw_shmplayer.h"
#include "cw_iniset.h"

SINGLETONG_IMPLEMENTION(SHMPlayer);

bool SHMPlayer::Init( )
{
	bool bRet = m_Pool.Init(g_Ini.m_Shm.m_Size); 
	if (!bRet)
	{
		return false;
	}
	bRet = m_Pool.Attach(g_Ini.m_Shm.m_Key);
	if (!bRet)
	{
		return false;
	}
	return true;
}

void SHMPlayer::Exit()
{
	m_Pool.Detach();
}

bool SHMPlayer::GetPlayerData( HumanData& data, int iSMUIndex )
{
	SMUPlayer* pSMUPlayer = m_Pool.GetSMUByIndex(iSMUIndex);
	if (!pSMUPlayer)
	{
		return false;
	}
	pSMUPlayer->ReadData(data);
	return true;
}

bool SHMPlayer::SetPlayerData( const HumanData& data, int iSMUIndex )
{
	SMUPlayer* pSMUPlayer = m_Pool.GetSMUByIndex(iSMUIndex);
	if (!pSMUPlayer)
	{
		return false;
	}
	pSMUPlayer->WriteData(data);
	return true;
}
