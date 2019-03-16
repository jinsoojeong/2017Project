#pragma once
#include "stdafx.h"
#include "TimeStamp.h"
#include "TimerJob.h"
#include "SchedulerJob.h"

#define JS_MINUTE (60)
#define JS_HOUR (JS_MINUTE * 60)
#define JS_DAY (JS_HOUR * 24)

class Clock : public Singleton<Clock>
{
public:
    Clock();
    ~Clock();
	
	void Update(ULONGLONG current_tick);

	std::time_t	GetServerStatckTick() { return server_start_tick_; }
	std::time_t	GetCurrentTick() { return std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()); }
	std::wstring GetNowMilliSec();
    TimeStamp GetToday(INT diff_day = 0);
	DAY_WEEK GetTodayWeek();

	inline BYTE TickToMinute(std::time_t tick) { return static_cast<BYTE>(tick / JS_MINUTE); }
	inline BYTE TickToHour(std::time_t tick) { return static_cast<BYTE>(tick / JS_HOUR); }
	inline BYTE TickToDay(std::time_t tick) { return static_cast<BYTE>(tick / JS_DAY); }
	inline std::time_t MinuteToTick(BYTE minute) { return (minute * JS_MINUTE); }
	inline std::time_t HourToTick(BYTE hour) { return (hour * JS_HOUR); }
	inline std::time_t DayToTick(BYTE day) { return (day * JS_DAY); }

	void RegistTimerJob(TimerJob* timer_job);
	void RegistSchedulerJob(SchedulerJob* scheduler_job);

private:
	typedef std::list<TimerJob*> TimerJobs;
	typedef std::list<SchedulerJob*> SchedulerJobs;

	void ProcessTimerJob(const TimeStamp& current_time_stamp);
	void ProcessSchedulerJob(const TimeStamp& current_time_stamp);

	static ULONGLONG update_interval_;
	std::time_t	server_start_tick_;
	TimerJobs timer_jobs_;
	SchedulerJobs activate_scheduler_jobs_;
	SchedulerJobs wait_scheduler_jobs_;
	ULONGLONG next_update_tick_;
};

#define JS_CLOCK Clock::GetSingleton()