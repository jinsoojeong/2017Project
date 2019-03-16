#pragma once

typedef std::function<void()> SchedulerStartCallback;
typedef std::function<void()> SchedulerStopCallback;

class SchedulerJob
{
public:
	SchedulerJob(std::wstring name, TimeStamp start_time, TimeStamp end_time, SchedulerStartCallback start_callback, SchedulerStopCallback stop_callback)
		: name_(name), start_time_(start_time), end_time_(end_time), start_callback_(start_callback), stop_callback_(stop_callback), repeat_start_hour_(0), repeat_start_min_(0), repeat_start_sec_(0), repeat_end_hour_(0), repeat_end_min_(0), repeat_end_sec_(0)
	{
		active_week_.insert(DAY_SUNDAY);
		active_week_.insert(DAY_MONDAY);
		active_week_.insert(DAY_TUESDAY);
		active_week_.insert(DAY_WEDNESDAY);
		active_week_.insert(DAY_THURSDAY);
		active_week_.insert(DAY_FRIDAY);
		active_week_.insert(DAY_SATURDAY);
	}

	SchedulerJob(std::wstring name, TimeStamp start_time, TimeStamp end_time, WORD start_hms, WORD end_hms, std::set<DAY_WEEK>& active_week, SchedulerStartCallback start_callback, SchedulerStopCallback stop_callback)
		: name_(name), start_time_(start_time), end_time_(end_time), start_callback_(start_callback), stop_callback_(stop_callback), active_week_(std::move(active_week))
	{
	}

	std::wstring GetName() { return name_; }
	bool IsActiveWeek(DAY_WEEK day_week)
	{
		if (active_week_.find(day_week) != active_week_.end())
			return true;

		return false;
	}

	bool IsAllwayActiveHour()
	{
		if (repeat_start_hour_ == 0 && repeat_end_hour_ == 0 
			&& repeat_start_min_ == 0 && repeat_end_min_ == 0
			&& repeat_start_sec_ == 0 && repeat_end_sec_ == 0)
			return true;

		return false;
	}

private:
	friend class Clock;

	SchedulerJob() {};

	std::wstring name_;
	TimeStamp start_time_;
	BYTE repeat_start_hour_;
	BYTE repeat_start_min_;
	BYTE repeat_start_sec_;
	TimeStamp end_time_;
	BYTE repeat_end_hour_;
	BYTE repeat_end_min_;
	BYTE repeat_end_sec_;
	std::set<DAY_WEEK> active_week_;
	SchedulerStartCallback start_callback_;
	SchedulerStopCallback stop_callback_;
};
