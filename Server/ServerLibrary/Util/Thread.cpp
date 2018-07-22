#include "stdafx.h"
#include "Thread.h"
#include "Lock.h"

Thread::Thread(std::thread *thread, wstr_t name)
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

std::thread::id Thread::id()
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

void ThreadManager::remove(std::thread::id id)
{
	ThreadPool::iterator itor = thread_pool_.find(id);

	if (itor == thread_pool_.end())
		return;

	Thread* thread = itor->second;

	// ����� �ٷ� ���� ������ �ش� ������ ���� ���� �� �̹Ƿ� ������ �۾��� ���� ���� ������ ����� �ʿ���
	SAFE_DELETE(thread); 

	thread_pool_.erase(itor);
}

Thread* ThreadManager::find(std::thread::id id)
{
	if (thread_pool_.empty())
		return nullptr;
	
	ThreadPool::iterator itor = thread_pool_.find(id);
	if (itor == thread_pool_.end())
		return nullptr;
	
	return (*itor).second;
}
