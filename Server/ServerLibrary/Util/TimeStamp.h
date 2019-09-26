#pragma once

class TimeStamp
{
public :
	TimeStamp();
	TimeStamp(std::time_t tick);

	void SetCurrentTime();
	void SetInfinite();
	bool IsInfinite() { return (year_ == 1900); }
	void Add(std::time_t tick);
	std::wstring ToString();

	// get time 함수
	std::time_t tick() const { return tick_; }
	WORD year() const { return year_; }
	BYTE month() const { return month_; }
	BYTE day() const { return day_; }
	BYTE hour() const { return hour_; }
	BYTE minute() const { return min_; }
	BYTE sec() const { return sec_; }
	DAY_WEEK day_week() const { return day_week_; }
	WORD week_flag()
	{
		switch (day_week_)
		{
		case WEEK_SUNDAY: return DAY_SUNDAY;
		case WEEK_MONDAY: return DAY_MONDAY;
		case WEEK_TUESDAY: return DAY_TUESDAY;
		case WEEK_WEDNESDAY: return DAY_WEDNESDAY;
		case WEEK_THURSDAY: return DAY_THURSDAY;
		case WEEK_FRIDAY: return DAY_FRIDAY;
		case WEEK_SATURDAY: return DAY_SATURDAY;
		}

		return DAY_NONE;
	}

private:
	void SetTime(std::time_t tick);

	std::time_t tick_;
	WORD year_;
	BYTE month_;
	BYTE day_;
	BYTE hour_;
	BYTE min_;
	BYTE sec_;
	DAY_WEEK day_week_; // 요일
};