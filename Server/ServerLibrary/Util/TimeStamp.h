#pragma once

class TimeStamp
{
public :
	TimeStamp();
	TimeStamp(std::time_t tick);

	void SetCurrentTime();
	void SetInfinite();

	void Add(std::time_t tick);

	bool IsInfinite() { return (year_ == 1900); }

	std::wstring ToString();

	std::time_t tick() const { return tick_; }
	WORD year() const { return year_; }
	BYTE month() const { return month_; }
	BYTE day() const { return day_; }
	BYTE hour() const { return hour_; }
	BYTE minute() const { return min_; }
	BYTE sec() const { return sec_; }
	DAY_WEEK day_week() const { return day_week_; }

private:
	void SetTime(std::time_t tick);

	std::time_t tick_;
	WORD year_;
	BYTE month_;
	BYTE day_;
	BYTE hour_;
	BYTE min_;
	BYTE sec_;
	DAY_WEEK day_week_; // ø‰¿œ
};