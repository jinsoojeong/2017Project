#include "stdafx.h"
#include <iomanip>
#include <chrono>
#include <ctime>
#include "Clock.h"
#include "TimeStamp.h"

ULONGLONG Clock::update_interval_ = 1000;

Clock::Clock() : next_update_tick_(0)
{
}

Clock::~Clock()
{
}

void Clock::Update()
{
	ULONGLONG current_tick = GetTickCount64();

	if (current_tick < next_update_tick_)
		return;

	TimeStamp current_time_stamp = Clock::GetCurrentTimeStamp();

	ProcessTimerJob(current_time_stamp);
	ProcessSchedulerJob(current_time_stamp);

	next_update_tick_ = current_tick + update_interval_;
}

void Clock::ProcessTimerJob(const TimeStamp& current_time_stamp)
{
	for (TimerJobs::iterator itor = timer_jobs_.begin(); itor != timer_jobs_.end();)
	{
		TimerJob* timer_job = (*itor);

		if (current_time_stamp.tick() >= timer_job->timer_.tick())
		{
			timer_job->callback_();
			itor = timer_jobs_.erase(itor);
			SAFE_DELETE(timer_job);
		}
		else
			++itor;
	}
}

void Clock::ProcessSchedulerJob(const TimeStamp& current_time_stamp)
{
	for (SchedulerJobs::iterator itor = wait_scheduler_jobs_.begin(); itor != wait_scheduler_jobs_.end();)
	{
		SchedulerJob* scheduler_job = *itor;
		if (scheduler_job->IsExpire())
		{
			itor = wait_scheduler_jobs_.erase(itor);
			scheduler_job->DestroyCompletion();
			SAFE_DELETE(scheduler_job);

			continue;
		}
		else
		{
			if (scheduler_job->IsActive())
			{
				itor = wait_scheduler_jobs_.erase(itor);
				scheduler_job->StartCompletion();
				activate_scheduler_jobs_.push_back(scheduler_job);

				continue;
			}
		}
			
		++itor;
	}

	for (SchedulerJobs::iterator itor = activate_scheduler_jobs_.begin(); itor != activate_scheduler_jobs_.end();)
	{
		SchedulerJob* scheduler_job = *itor;
		if (!scheduler_job->IsActive())
		{
			itor = activate_scheduler_jobs_.erase(itor);
			scheduler_job->StopCompletion();
			wait_scheduler_jobs_.push_back(scheduler_job);

			continue;
		}

		++itor;
	}
}

TimeStamp Clock::GetCurrentTimeStamp(INT diff_day, INT diff_hour, INT diff_min, INT diff_sec)
{
	std::time_t tick = 0;
	tick = GetCurrentTick();

	if (diff_day != 0) tick += diff_day * DayToTick(1);
	if (diff_hour != 0) tick += diff_hour * HourToTick(1);
	if (diff_min != 0) tick += diff_min * MinuteToTick(1);
	if (diff_sec != 0) tick += diff_sec;

	TimeStamp time_stamp(tick);
	return time_stamp;
}

DAY_WEEK Clock::GetTodayWeek()
{
	TimeStamp time_stamp(GetCurrentTick());
    return time_stamp.day_week();
}

void Clock::RegistTimerJob(TimerJob* timer_job)
{
	if (timer_job == nullptr)
		return;

	timer_jobs_.push_back(timer_job);
}
void Clock::RegistSchedulerJob(SchedulerJob* scheduler_job)
{
	if (scheduler_job == nullptr)
		return;

	wait_scheduler_jobs_.push_back(scheduler_job);
}