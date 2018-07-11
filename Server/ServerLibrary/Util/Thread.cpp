#include "stdafx.h"
#include "Thread.h"
#include "Lock.h"

Thread::Thread(thread_t *thread, wstr_t name)
{
	name_ = name;
	thread_ = thread;
	id_ = thread_->get_id();

	THREAD_MANAGER.put(this);
}

Thread::~Thread()
{
	thread_->join();
	SAFE_DELETE(thread_);
	SAFE_DELETE(lock_);
}

threadId_t Thread::id()
{
	return id_;
}

wstr_t &Thread::name()
{
	return name_;
}

void Thread::setLock(Lock *lock)
{
	lock_ = lock;
}

Lock* Thread::lock()
{
	return lock_;
}

//--------------------------------------------------//
ThreadManager::~ThreadManager()
{
	for (ThreadPool::iterator itor = thread_pool_.begin() ; itor != thread_pool_.end() ; ++itor)
	{
		SAFE_DELETE((*itor).second);
	}
}

void ThreadManager::put(Thread *thread)
{
	thread_pool_.insert(ThreadPool::value_type(thread->id(), thread));

#ifdef _DEBUG
	Log(L"* create thread : id[0x%X] name[%s], pool size[%d]", thread->id(), thread->name().c_str(), thread_pool_.size());
#endif //_DEBUG
}

void ThreadManager::remove(threadId_t id)
{
	ThreadPool::iterator itor = thread_pool_.find(id);

	if (itor == thread_pool_.end())
		return;

	Thread* thread = itor->second;

	// 현재는 바로 제거 하지만 해당 스레드 동작 중일 것 이므로 스레드 작업을 정상 종료 시켜줄 기능이 필요함
	SAFE_DELETE(thread); 

	thread_pool_.erase(itor);
}

Thread* ThreadManager::find(threadId_t id)
{
	if (thread_pool_.empty())
		return nullptr;
	
	ThreadPool::iterator itor = thread_pool_.find(id);
	if (itor == thread_pool_.end())
		return nullptr;
	
	return (*itor).second;
}
