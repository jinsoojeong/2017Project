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
	TimerJob* job = new TimerJob(10, [&complete]()
	{
		std::wcout << "timer !!" << std::endl;
		complete = false;
	});
	
	clock_.RegistTimerJob(job);
	while (complete)
	{
		clock_.Update();
	}

	TimeStamp start_time = Clock::GetCurrentTimeStamp(0, 0, 0, +10);
	TimeStamp end_time = Clock::GetCurrentTimeStamp(0, 0, 0, +20);

	// 10초후 시작, 20초후 종료 (10초 동안 active)
	SchedulerJob* scheduler_job = new SchedulerJob(L"Temp Job", start_time, end_time);

	// 주말 오후 2~ 6시 까지 활성화되는 스케쥴러
	SchedulerJob* scheduler_job2 = new SchedulerJob(L"Temp Job2", start_time, end_time, (DAY_SATURDAY|DAY_SUNDAY), 14, 18, 0, 0, 0, 0);

	scheduler_job->SetStartCompletion([]() { std::wcout << "Scheduler Job Start !!" << std::endl; });
	scheduler_job->SetStopCompletion([]() { std::wcout << "Scheduler Job Stop !!" << std::endl; });
	scheduler_job->SetDestroyCompletion([&complete]() { std::wcout << "Scheduler Job Destroy !!" << std::endl; complete = false; });
	
	clock_.RegistSchedulerJob(scheduler_job);

	complete = true;
	while (complete)
	{
		clock_.Update();
	}

    return 0;
}

