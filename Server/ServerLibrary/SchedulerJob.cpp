#include "stdafx.h"
#include "SchedulerJob.h"
#include "./Util/Clock.h"
#include "./Util/TimeStamp.h"

SchedulerJob::SchedulerJob(std::wstring name, TimeStamp start_time, TimeStamp end_time)
	: name_(name), start_time_(start_time), end_time_(end_time), start_callback_(nullptr), stop_callback_(nullptr), destroy_callback_(nullptr), repeat_start_hour_(0), repeat_start_min_(0), repeat_start_sec_(0), repeat_end_hour_(0), repeat_end_min_(0), repeat_end_sec_(0),
	active_week_(DAY_SUNDAY | DAY_MONDAY | DAY_TUESDAY | DAY_WEDNESDAY | DAY_THURSDAY | DAY_FRIDAY | DAY_SATURDAY)
{
}

SchedulerJob::SchedulerJob(std::wstring name, TimeStamp start_time, TimeStamp end_time, WORD start_hms, WORD end_hms, WORD active_week)
	: name_(name), start_time_(start_time), end_time_(end_time), start_callback_(nullptr), stop_callback_(nullptr), destroy_callback_(nullptr), active_week_(active_week)
{
}


bool SchedulerJob::IsActiveWeek(WORD day_week) 
{
	if (active_week_ & day_week)
		return true;

	return false;
}
bool SchedulerJob::IsAllwayActive()
{
	if (repeat_start_hour_ == 0 && repeat_end_hour_ == 0
		&& repeat_start_min_ == 0 && repeat_end_min_ == 0
		&& repeat_start_sec_ == 0 && repeat_end_sec_ == 0
		&& IsActiveWeek(DAY_SUNDAY | DAY_MONDAY | DAY_TUESDAY | DAY_WEDNESDAY | DAY_THURSDAY | DAY_FRIDAY | DAY_SATURDAY))
		return true;

	return false;
}
bool SchedulerJob::IsActive()
{
	if (IsExpire() == false)
		return false;

	TimeStamp current_time_stamp = Clock::GetCurrentTimeStamp();
	if (current_time_stamp.tick() >= start_time_.tick())
		return false;

	if (!IsAllwayActive())
	{
		if ((repeat_start_hour_ <= current_time_stamp.hour() && current_time_stamp.hour() <= repeat_end_hour_)
			&& (repeat_start_min_ <= current_time_stamp.minute() && current_time_stamp.minute() <= repeat_end_min_)
			&& (repeat_start_sec_ <= current_time_stamp.sec() && current_time_stamp.sec() <= repeat_end_sec_)
			&& IsActiveWeek(current_time_stamp.week_flag()))
			return false;
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