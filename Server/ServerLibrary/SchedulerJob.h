#pragma once

typedef std::function<void()> SchedulerStartCallback;
typedef std::function<void()> SchedulerStopCallback;
typedef std::function<void()> SchedulerDestroyCallback;

class SchedulerJob
{
public:
	SchedulerJob(std::wstring name, TimeStamp start_time, TimeStamp end_time);
	SchedulerJob(std::wstring name, TimeStamp start_time, TimeStamp end_time, WORD start_hms, WORD end_hms, WORD active_week);
	void SetStartCompletion(SchedulerStartCallback start_callback) { start_callback_ = start_callback; }
	void SetStopCompletion(SchedulerStopCallback stop_callback) { stop_callback_ = stop_callback; }
	void SetDestroyCompletion(SchedulerDestroyCallback destroy_callback) { destroy_callback_ = destroy_callback; }
	std::wstring GetName() { return name_; }

private:
	friend class Clock;
	SchedulerJob() {};

	bool IsActiveWeek(WORD day_week);
	bool IsAllwayActive();
	bool IsActive();
	bool IsExpire();
	void StartCompletion();
	void StopCompletion();
	void DestroyCompletion();

	std::wstring name_;
	TimeStamp start_time_;
	BYTE repeat_start_hour_;
	BYTE repeat_start_min_;
	BYTE repeat_start_sec_;
	TimeStamp end_time_;
	BYTE repeat_end_hour_;
	BYTE repeat_end_min_;
	BYTE repeat_end_sec_;
	WORD active_week_;
	SchedulerStartCallback start_callback_;
	SchedulerStopCallback stop_callback_;
	SchedulerDestroyCallback destroy_callback_;
};
