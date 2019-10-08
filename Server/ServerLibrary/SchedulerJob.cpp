#include "stdafx.h"
#include "SchedulerJob.h"
#include "./Util/Clock.h"
#include "./Util/TimeStamp.h"

SchedulerJob::SchedulerJob(std::wstring name, TimeStamp start_time, TimeStamp end_time)
	: name_(name), start_time_(start_time), end_time_(end_time), start_callback_(nullptr), stop_callback_(nullptr), destroy_callback_(nullptr), active_week_(ALL_DAY_WEEK),
	repeat_start_hour_(0), repeat_start_min_(0), repeat_start_sec_(0), repeat_end_hour_(0), repeat_end_min_(0), repeat_end_sec_(0)

{
}

SchedulerJob::SchedulerJob(std::wstring name, TimeStamp start_time, TimeStamp end_time, WORD active_week, BYTE repeat_start_hour, BYTE repeat_end_hour, BYTE repeat_start_min, BYTE repeat_end_min, BYTE repeat_start_sec, BYTE repeat_end_sec)
	: name_(name), start_time_(start_time), end_time_(end_time), start_callback_(nullptr), stop_callback_(nullptr), destroy_callback_(nullptr), active_week_(active_week),
	repeat_start_hour_(repeat_start_hour), repeat_end_hour_(repeat_end_hour), repeat_start_min_(repeat_start_min), repeat_end_min_(repeat_end_min), repeat_start_sec_(repeat_start_sec), repeat_end_sec_(repeat_end_sec)
{		
}

bool SchedulerJob::IsActiveDayWeek(WORD today_week) 
{
	if (active_week_ & today_week)
		return true;

	return false;
}
bool SchedulerJob::IsAllwayActive()
{
	if (repeat_start_hour_ == 0 && repeat_end_hour_ == 0
		&& repeat_start_min_ == 0 && repeat_end_min_ == 0
		&& repeat_start_sec_ == 0 && repeat_end_sec_ == 0
		&& IsActiveDayWeek(ALL_DAY_WEEK))
		return true;

	return false;
}
bool SchedulerJob::IsActive()
{
	if (IsExpire())
		return false;

	TimeStamp current_time_stamp = Clock::GetCurrentTimeStamp();
	if (current_time_stamp.tick() < start_time_.tick())
		return false;

	if (!IsAllwayActive())
	{
		if ((repeat_start_hour_ <= current_time_stamp.hour() && current_time_stamp.hour() <= repeat_end_hour_)
			&& (repeat_start_min_ <= current_time_stamp.minute() && current_time_stamp.minute() <= repeat_end_min_)
			&& (repeat_start_sec_ <= current_time_stamp.sec() && current_time_stamp.sec() <= repeat_end_sec_)
			&& IsActiveDayWeek(current_time_stamp.week_flag()))
		{
			return false;
		}
	}

	return true;
}
bool SchedulerJob::IsExpire()
{
	TimeStamp current_time_stamp = Clock::GetCurrentTimeStamp();
	if (current_time_stamp.tick() < end_time_.tick())
		return false;

	return true;
}

void SchedulerJob::StartCompletion()
{
	if (start_callback_ == nullptr)
		return;

	start_callback_();
}
void SchedulerJob::StopCompletion()
{
	if (stop_callback_ == nullptr)
		return;

	stop_callback_();
}
void SchedulerJob::DestroyCompletion()
{
	if (destroy_callback_ == nullptr)
		return;

	destroy_callback_();
}