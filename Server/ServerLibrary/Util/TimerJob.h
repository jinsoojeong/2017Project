#pragma once

typedef std::function<void()> TimerCallback;

class TimerJob
{
public:
	TimerJob(std::time_t timer_tick, TimerCallback callback) : callback_(callback)
	{
		timer_.SetCurrentTime();
		timer_.Add(timer_tick);
	}

private:
	friend class Clock;

	TimerJob() {};

	TimeStamp timer_;
	TimerCallback callback_;
};
