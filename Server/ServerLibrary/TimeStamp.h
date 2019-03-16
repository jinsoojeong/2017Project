#pragma once

class TIMESTAMP
{
	TIMESTAMP() : tick_(-1), year_(1900), month_(1), day_(1), hour_(0), min_(0), sec_(0), millisec_(0)
	{
	}

	TIMESTAMP(std::time_t tick) : tick_(tick), year_(0), month_(0), day_(0), hour_(0), min_(0), sec_(0), millisec_(0)
	{
		SetTime(tick_);
	}

	void SetCurrentTick()
	{
		tick_ = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		SetTime(tick_);
	}

	void SetInfinite()
	{
		tick_ = -1;
		year_ = 1900;
		month_ = 1;
		day_ = 1;
		hour_ = 0;
		min_ = 0;
		sec_ = 0;
	}

	bool IsInfinite()
	{
		return (year_ == 1900);
	}

	std::wstring ToString()
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

private:
	void SetTime(std::time_t tick)
	{
		tm time;
		localtime_s(&time, &tick_);

		year_ = time.tm_year + 1900;
		month_ = time.tm_mon + 1;
		day_ = time.tm_mday;
		hour_ = time.tm_mday;
		min_ = time.tm_min;
		sec_ = time.tm_sec;
	}

	std::time_t tick_;
	WORD year_;
	BYTE month_;
	BYTE day_;
	BYTE hour_;
	BYTE min_;
	BYTE sec_;
	BYTE millisec_;
};