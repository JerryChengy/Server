#ifndef CW_THREAD_H
#define CW_THREAD_H
#include "cw_commondefine.h"
class Thread
{
public:
	Thread():running(false)
	{
		thread = (HANDLE)_beginthreadex(NULL, 0, __threadmain, this, CREATE_SUSPENDED, NULL);
	}
	virtual ~Thread()
	{
		CloseHandle(thread);
	}

	virtual bool IsRunningNow()
	{
		 return running;
	}

	virtual void stopRunning()
	{
		running = false;
	}

	virtual void start()
	{
		running =  true;
		ResumeThread(thread);
	}

	virtual void join()
	{
		WaitForSingleObject(thread, INFINITE);	//等待线程结束
	}

	virtual void run() = 0;
protected:

private:
	static unsigned __stdcall __threadmain(void* args)
	{
		Thread* thread = (Thread*) args;
		while (1)
		{
			thread->run();
		}
		
		return 0;
	}
private:
	HANDLE thread;
	volatile bool running;
};
#endif