#include "cw_commondefine.h"
#include "cw_shmutil.h"



void sm_lock( char& flag, char type )
{
	while (1)
	{
		if (flag == SM_FREE)
		{
			flag = type;
			if (flag == type)
			{
				return ;
			}
			else
			{
				SLEEP(1);
				continue;
			}
		}
		SLEEP(1);
		continue;
	}
}

void sm_unlock( char& flag)
{
	while (1)
	{
		if (flag == SM_ME_READ || flag == SM_ME_WRITE)
		{
			flag = SM_FREE;
			if (flag != SM_FREE)
			{
				SLEEP(1);
				continue;
			}
			return ;
		}
		break;
	}	
}

bool sm_trylock(char& flag, char type)
{
	flag = type;
	if (flag == type)
	{
		return true;
	}
	else
	{
		return false;
	}
}
