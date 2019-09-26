// ClockTest.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include "../ServerLibrary/ServerLibrary.h"

#ifdef _DEBUG
	#pragma comment (lib, "ServerLibraryd.lib")
#else
	#pragma comment (lib, "ServerLibrary.lib")
#endif

#include <chrono>

int main()
{
	// get today
	{
		TimeStamp today = Clock::GetCurrentTimeStamp();
		std::wcout << (today.ToString().c_str()) << std::endl;

		TimeStamp today_1 = Clock::GetCurrentTimeStamp(+1);
		std::wcout << (today_1.ToString().c_str()) << std::endl;

		TimeStamp today_2 = Clock::GetCurrentTimeStamp(-1);
		std::wcout << (today_2.ToString().c_str()) << std::endl;
	}
	
	// infinite
	{
		TimeStamp infinite;
		if (infinite.IsInfinite())
			std::wcout << (infinite.ToString().c_str()) << std::endl;
	}

	// 
	{
		DAY_WEEK day_week = Clock::GetTodayWeek();
		std::wcout << L"today : " << day_week << std::endl;
	}
	
	// 타이머, 스케쥴러 잡을 실행하기 위한 clock 객체 선언
	Clock clock_;

	bool complete = true;
	TimerJob* job = new TimerJob(20, [&complete]()
	{
		std::wcout << "timer !!" << std::endl;
		complete = false;
	});
	
	clock_.RegistTimerJob(job);

	DWORD start_tick = GetTickCount64();
	while (complete)
	{
		ULONGLONG current_tick = GetTickCount64();
		clock_.Update(current_tick);
	}

    return 0;
}

