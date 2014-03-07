#ifndef CW_SHMMANAGER_H
#define CW_SHMMANAGER_H
#include "cw_singleton.h"

class SHMManager: public Singleton<SHMManager>
{
public:
	bool	Init();

	void	Exit();
protected:
private:
};

#endif