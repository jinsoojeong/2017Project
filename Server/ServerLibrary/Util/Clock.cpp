#include "stdafx.h"
#include <iomanip>
#include <chrono>
#include <ctime>
#include "Clock.h"
#include "TimeStamp.h"

ULONGLONG Clock::update_interval_ = 1000;

Clock::Clock() : server_start_tick_(GetCurrentTick()), next_update_tick_(0)
{
}

Clock::~Clock()
{
}

void Clock::Update(ULONGLONG current_tick)
{
	if (current_tick < next_update_tick_)
		return;

	TimeStamp current_time_stamp = JS_CLOCK.GetToday();

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
		}
		else
			++itor;
	}
}

void Clock::ProcessSchedulerJob(const TimeStamp& current_time_stamp)
{
	SchedulerJobs destroy_jobs;
	SchedulerJobs activate_jobs;
	for (SchedulerJobs::iterator itor = wait_scheduler_jobs_.begin(); itor != wait_scheduler_jobs_.end();++itor)
	{
		SchedulerJob* scheduler_job = *itor;

		if (current_time_stamp.tick() >= scheduler_job->end_time_.tick())
		{
			Log(L"Destroy Scheduler Job : %s", scheduler_job->GetName().c_str());
			destroy_jobs.push_back(scheduler_job);
			continue;
		}

		if (current_time_stamp.tick() >= scheduler_job->start_time_.tick())
		{
			if (scheduler_job->IsAllwayActiveHour())
				activate_jobs.push_back(scheduler_job);
			else
			{
				if ((scheduler_job->repeat_start_hour_ <= current_time_stamp.hour() && current_time_stamp.hour() <= scheduler_job->repeat_end_hour_)
					&& (scheduler_job->repeat_start_min_ <= current_time_stamp.minute() && current_time_stamp.minute() <= scheduler_job->repeat_end_min_)
					&& (scheduler_job->repeat_start_sec_ <= current_time_stamp.sec() && current_time_stamp.sec() <= scheduler_job->repeat_end_sec_))
				{
					if (scheduler_job->IsActiveWeek(current_time_stamp.day_week()))
						activate_jobs.push_back(scheduler_job);
				}
			}
		}
	}

	if (!destroy_jobs.empty())
	{
		for each (SchedulerJobs::value_type value in destroy_jobs)
		{
			wait_scheduler_jobs_.remove(value);
			SAFE_DELETE(value);
		}
		
		destroy_jobs.clear();
	}

	if (!activate_jobs.empty())
	{
		for each (const SchedulerJobs::value_type& value in activate_jobs)
		{
			SchedulerJob* scheduler_job = value;
			scheduler_job->start_callback_();
			activate_scheduler_jobs_.push_back(scheduler_job);
		}

		activate_jobs.clear();
	}

	// 수정중.. 활성화 되어있는 스케쥴 잡 체크
	for (SchedulerJobs::iterator itor = activate_scheduler_jobs_.begin(); itor != activate_scheduler_jobs_.end(); ++itor)
	{
	}
}

std::wstring Clock::GetNowMilliSec()
{
	std::chrono::high_resolution_clock::time_point point = std::chrono::high_resolution_clock::now();
	std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(point.time_since_epoch());

	std::chrono::seconds s = std::chrono::duration_cast<std::chrono::seconds>(ms);
	std::time_t t = s.count();
	std::size_t fractional_seconds = ms.count() % 1000;

	array<WCHAR, SIZE_8> milli_str;
	snwprintf(milli_str, L"%03d", (int)(fractional_seconds));

	TimeStamp time_stamp(GetCurrentTick());
	std::wstring timeString = time_stamp.ToString();

    return time_stamp.ToString() + milli_str.data();
}

TimeStamp Clock::GetToday(INT diff_day)
{
	std::time_t tick = 0;
	tick = GetCurrentTick();

	if (diff_day != 0)
		tick += diff_day * DayToTick(1);

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