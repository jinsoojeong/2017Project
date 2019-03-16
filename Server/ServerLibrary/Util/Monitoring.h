#pragma once
#include "stdafx.h"
#include "psapi.h"

class SystemInfo : public Singleton<SystemInfo>
{
public:
	SystemInfo()
	{
		SYSTEM_INFO sysInfo;
		FILETIME ftime, fsys, fuser;

		GetSystemInfo(&sysInfo);
		num_processors_ = sysInfo.dwNumberOfProcessors;

		GetSystemTimeAsFileTime(&ftime);
		memcpy(&last_cpu_, &ftime, sizeof(FILETIME));

		self_ = GetCurrentProcess();
		GetProcessTimes(self_, &ftime, &ftime, &fsys, &fuser);
		memcpy(&last_sys_cpu_, &fsys, sizeof(FILETIME));
		memcpy(&last_user_cpu_, &fuser, sizeof(FILETIME));
	}

	double GetCpuUsage() 
	{
		FILETIME ftime, fsys, fuser;
		ULARGE_INTEGER now, sys, user;
		double percent;

		GetSystemTimeAsFileTime(&ftime);
		memcpy(&now, &ftime, sizeof(FILETIME));

		GetProcessTimes(self_, &ftime, &ftime, &fsys, &fuser);
		memcpy(&sys, &fsys, sizeof(FILETIME));
		memcpy(&user, &fuser, sizeof(FILETIME));
		percent = (double)((sys.QuadPart - last_sys_cpu_.QuadPart) + (user.QuadPart - last_user_cpu_.QuadPart));
		percent /= (now.QuadPart - last_cpu_.QuadPart);
		percent /= num_processors_;
//		lastCPU = now;
//		lastUserCPU = user;
//		lastSysCPU = sys;
		percent = percent * 100;
		return fixInRange(0, percent, 100);
	}

	SIZE_T GetMemUsage()
	{
		PROCESS_MEMORY_COUNTERS pmc;
		GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
		return (size_t) pmc.WorkingSetSize;
	}

	SIZE_T GetPhysyicMemUsage()
	{
		MEMORYSTATUSEX memInfo;
		memInfo.dwLength = sizeof(MEMORYSTATUSEX);
		GlobalMemoryStatusEx(&memInfo);

		return (size_t) memInfo.ullTotalPhys - memInfo.ullAvailPhys;
	}

	DWORD GetNumberOfProcessors() { return num_processors_; }

private:
	ULARGE_INTEGER last_cpu_;
	ULARGE_INTEGER last_sys_cpu_;
	ULARGE_INTEGER last_user_cpu_;
	int num_processors_;
	HANDLE self_;
};

#define SYSTEM_INFO SystemInfo::GetSingleton()