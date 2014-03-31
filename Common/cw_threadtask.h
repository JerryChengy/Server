#ifndef  CW_THREADTASK_H
#define  CW_THREADTASK_H
#include "cw_commondefine.h"
#include "cw_thread.h"
#include "cw_lock.h"
#include "cw_singleton.h"
#include "cw_log.h"

template<class T>
class TaskQueue
{
	CLock				m_Lock;
	std::queue<T*>		m_TaskQueue;
public:
	T* GetTask()
	{
		CLock::Scoped scoped(m_Lock);
		if (m_TaskQueue.empty())
		{
			return 0;
		}
		T* task = m_TaskQueue.front();
		m_TaskQueue.pop();	
		return task;
	}

	void AddTask(T* task)
	{
		CLock::Scoped scoped(m_Lock);
		m_TaskQueue.push(task);
	}

	void PrintTask(){ }
};
template<>
void TaskQueue<int>::PrintTask()
{
	int* task = GetTask();
	if (task)
	{
		LOG_DEBUG("task id: %d", *task);
	}
}

template<class T>
class TaskProcessor: public Thread
{
		TaskQueue<T>*  m_pTaskQueue;
public:
	TaskProcessor(TaskQueue<T>* taskQueue)
	{
		m_pTaskQueue = taskQueue;
	}
	bool startup()
	{
		Thread::start();
		return true;
	}

	virtual void run()
	{
		if (m_pTaskQueue)
		{
			m_pTaskQueue->PrintTask(); 
		}

	}
};

template<class T>
class TaskManager/*: public Singleton<TaskManager>*/
{
public:

	static const int TASK_PROCESSOR_NUM = 5;
public:
	TaskManager()
	{
		if (sm_Singleton)
		{
			throw 1;
		}
		sm_Singleton = static_cast<TaskManager<T>*>(this);
	}
	static TaskManager*	GetSingletonPtr(){ return sm_Singleton; }
	static TaskManager&  GetSingleton(){ return * sm_Singleton; }
public:
	void		Init()
	{
		for (int i=0;i<TASK_PROCESSOR_NUM;++i)
		{
			m_pProcessor[i] = new TaskProcessor<T>(&m_TaskQueue);
			m_pProcessor[i]->startup();
		}
	}
	void		AddTask(T* task)
	{
		m_TaskQueue.AddTask(task);
	}
protected:
private:
	
	TaskProcessor<T>*			m_pProcessor[TASK_PROCESSOR_NUM];
	TaskQueue<T>				m_TaskQueue;
	static TaskManager<T>*	sm_Singleton;
};

#endif