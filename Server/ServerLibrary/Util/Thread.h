#pragma once
#include "stdafx.h"

#define MAKE_THREAD(className, process)	(new Thread(new std::thread(&className##::##process, this), L#className))
#define GET_CURRENT_THREAD_ID		std::this_thread::get_id
class Lock;
typedef std::function<void(void *)> ThreadFunction;

class Thread
{
public:
	Thread(std::thread *thread, wstr_t name);
	~Thread();	

	std::thread::id id();
	wstr_t &name();

	void setLock(Lock *lock);
	Lock *lock();

private:
	std::thread::id id_;
	wstr_t name_;
	std::thread *thread_;
	Lock *lock_;			//지금 걸린 락
};

//#define THREAD_POOL_HASHMAP
class ThreadManager : public Singleton<ThreadManager>
{
public:
	~ThreadManager();

	void put(Thread *thread);
	void remove(std::thread::id id);
	Thread* find(std::thread::id id);

private:
	typedef std::map<std::thread::id, Thread*> ThreadPool;

	ThreadPool thread_pool_;
};

#define THREAD_MANAGER ThreadManager::GetSingleton()