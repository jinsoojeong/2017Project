// ContentServer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

class SystemReport : public Work
{
	void tick()
	{
		double cpu_usage = SYSTEM_INFO.GetCpuUsage();
		size_t mem_usage = SYSTEM_INFO.GetMemUsage();

		Log(L"### cpu usage : %2.2f%%, memory usage : %uByte", cpu_usage, mem_usage);
	}
};

void ServerProcess()
{
	Work* system_report = new SystemReport();
	TASK_MANAGER.add(system_report, 1, TICK_INFINTY);

	shared_ptr<Server> server(new IOCPServer(new ContentServer()));
	if (!server->run()) 
	{
		Log(L"! error: server start fail");
		return;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	shared_ptr<Thread> serverThread(new Thread(new thread_t(ServerProcess), L"Server"));
	return 0;
}
