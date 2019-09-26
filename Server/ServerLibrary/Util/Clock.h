#pragma once
#include "stdafx.h"
#include "TimeStamp.h"
#include "TimerJob.h"
#include "SchedulerJob.h"

#define JS_MINUTE (60)
#define JS_HOUR (JS_MINUTE * 60)
#define JS_DAY (JS_HOUR * 24)

class Clock
{
public:
    Clock();
    ~Clock();

	void Update(ULONGLONG current_tick);
	void RegistTimerJob(TimerJob* timer_job);
	void RegistSchedulerJob(SchedulerJob* scheduler_job);

	static std::time_t GetCurrentTick() { return std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()); }
	static TimeStamp GetCurrentTimeStamp(INT diff_day = 0, INT diff_hour = 0, INT diff_min = 0, INT diff_sec = 0);
	static DAY_WEEK GetTodayWeek();
	static inline BYTE TickToMinute(std::time_t tick) { return static_cast<BYTE>(tick / JS_MINUTE); }
	static inline BYTE TickToHour(std::time_t tick) { return static_cast<BYTE>(tick / JS_HOUR); }
	static inline BYTE TickToDay(std::time_t tick) { return static_cast<BYTE>(tick / JS_DAY); }
	static inline std::time_t MinuteToTick(BYTE minute) { return (minute * JS_MINUTE); }
	static inline std::time_t HourToTick(BYTE hour) { return (hour * JS_HOUR); }
	static inline std::time_t DayToTick(BYTE day) { return (day * JS_DAY); }

private:
	typedef std::list<TimerJob*> TimerJobs;
	typedef std::list<SchedulerJob*> SchedulerJobs;

	void ProcessTimerJob(const TimeStamp& current_time_stamp);
	void ProcessSchedulerJob(const TimeStamp& current_time_stamp);

	static ULONGLONG update_interval_;
	
	TimerJobs timer_jobs_;
	SchedulerJobs activate_scheduler_jobs_;
	SchedulerJobs wait_scheduler_jobs_;
	ULONGLONG next_update_tick_;
};