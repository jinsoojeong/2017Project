#include "stdafx.h"
#include <iomanip>
#include "Clock.h"
#include "TimeStamp.h"

TimeStamp::TimeStamp() : tick_(-1), year_(1900), month_(1), day_(1), hour_(0), min_(0), sec_(0), day_week_(DAY_MAX)
{

}

TimeStamp::TimeStamp(std::time_t tick) : year_(0), month_(0), day_(0), hour_(0), min_(0), sec_(0), day_week_(DAY_MAX)
{
	SetTime(tick);
}

void TimeStamp::SetCurrentTime()
{
	SetTime(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()));
}

void TimeStamp::SetInfinite()
{
	tick_ = -1;
	year_ = 1900;
	month_ = 1;
	day_ = 1;
	hour_ = 0;
	min_ = 0;
	sec_ = 0;
	day_week_ = DAY_MAX;
}

void TimeStamp::Add(std::time_t tick)
{
	if (IsInfinite())
		return;

	SetTime(tick_ + tick);
}

std::wstring TimeStamp::ToString()
{
	std::wstringstream wss;

	wss << std::setfill(L'0') << std::setw(4) << year_ << L"-";
	wss << std::setfill(L'0') << std::setw(2) << month_ << L"-";
	wss << std::setfill(L'0') << std::setw(2) << day_ << L" ";
	wss << std::setfill(L'0') << std::setw(2) << hour_ << L":";
	wss << std::setfill(L'0') << std::setw(2) << min_ << L":";
	wss << std::setfill(L'0') << std::setw(2) << sec_;

	return wss.str();
}

void TimeStamp::SetTime(std::time_t tick)
{
	tick_ = tick;

	tm time;
	localtime_s(&time, &tick_);

	year_ = time.tm_year + 1900;
	month_ = time.tm_mon + 1;
	day_ = time.tm_mday;
	hour_ = time.tm_hour;
	min_ = time.tm_min;
	sec_ = time.tm_sec;
	day_week_ = static_cast<DAY_WEEK>(time.tm_wday);
}