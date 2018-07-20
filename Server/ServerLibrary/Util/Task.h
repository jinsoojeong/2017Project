#pragma once
#include "stdafx.h"

#define TICK_INFINTY 0

class WorkObject
{
public:
	virtual void tick() = 0;
	virtual void wakeup() {};
	virtual void suspend() {};
	virtual void stop() {};
	virtual void start() {};
};

class TaskNode
{
	WorkObject		*workObject_;
	int			freqSec_;
	int			durationSec_;

	tick_t		nextTick_;
public:
	TaskNode(WorkObject *workObject, int freqSec, int durationSec);
	~TaskNode();

	void nextTick();
	bool expired();

	void tick();
};

//---------------------------------------------------------------------//
class Task
{
	std::list<TaskNode *> taskList_;
	Thread		*thread_;
	int			id_;

public:
	Task(int id);
	~Task();
	void add(TaskNode *taskNode);
	void remove(TaskNode *taskNode);

	void process();
	void run();
};

//---------------------------------------------------------------------//
class TaskManager : public Singleton <TaskManager>
{
	int                     threadCount_;
	std::vector<Task *>     taskPool_;

public:
	TaskManager();
	virtual ~TaskManager();

	void initialize(xml_t *config);

	void add(WorkObject *workObject, int freqSec, int durationSec);
};

#define TASK_MANAGER TaskManager::GetSingleton()