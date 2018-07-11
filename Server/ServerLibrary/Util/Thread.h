#pragma once
#include "stdafx.h"

#define MAKE_THREAD(className, process)	(new Thread(new thread_t(&className##::##process, this), L#className))
#define GET_CURRENT_THREAD_ID		std::this_thread::get_id
class Lock;
typedef std::function<void(void *)> ThreadFunction;

class Thread
{
public:
	Thread(thread_t *thread, wstr_t name);
	~Thread();	

	threadId_t id();
	wstr_t &name();

	void setLock(Lock *lock);
	Lock *lock();

private:
	threadId_t				id_;
	wstr_t					name_;
	thread_t				*thread_;
	Lock					*lock_;			//지금 걸린 락
};

//#define THREAD_POOL_HASHMAP
class ThreadManager : public Singleton<ThreadManager>
{
public:
	~ThreadManager();

	void put(Thread *thread);
	void remove(threadId_t id);
	Thread* find(threadId_t id);

private:
	typedef std::map<threadId_t, Thread*> ThreadPool;

	ThreadPool thread_pool_;
};

#define THREAD_MANAGER ThreadManager::GetSingleton()