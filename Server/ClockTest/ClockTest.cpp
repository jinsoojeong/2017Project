// ClockTest.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include "../ServerLibrary/ServerLibrary.h"

#ifdef _DEBUG
	#pragma comment (lib, "ServerLibraryd.lib")
#else
	#pragma comment (lib, "ServerLibrary.lib")
#endif

int main()
{
	// get today
	{
		TimeStamp today = JS_CLOCK.GetToday();
		std::wcout << (today.ToString().c_str()) << std::endl;

		TimeStamp today_1 = JS_CLOCK.GetToday(+1);
		std::wcout << (today_1.ToString().c_str()) << std::endl;

		TimeStamp today_2 = JS_CLOCK.GetToday(-1);
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
		DAY_WEEK day_week = JS_CLOCK.GetTodayWeek();
		std::wcout << L"today : " << day_week << std::endl;
	}
	
	TimerJob* job = new TimerJob(20, [](){
		std::wcout << "timer !!" << std::endl;
	});

	JS_CLOCK.RegistTimerJob(job);

	DWORD start_tick = GetTickCount64();
	while (true)
	{
		ULONGLONG current_tick = GetTickCount64();
		JS_CLOCK.Update(current_tick);

		if (current_tick >= start_tick + 3000)
			break;
	}

    return 0;
}

