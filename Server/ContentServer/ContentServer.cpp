// ContentServer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

class SystemReport : public Work
{
	void tick()
	{
		Monitoring &moniter = Monitoring::GetSingleton();
		Log(L"### cpu usage : %2.2f%%, memory usage : %uByte", moniter.processCpuUsage(), moniter.processMemUsage());
	}
};

void ServerProcess()
{
	shared_ptr<Server> server(new IOCPServer(new ContentServer()));
	SystemReport systemReport;
	const int MONITOR_REPORTING_SEC = 1;
	TaskManager::GetSingleton().add(&systemReport, MONITOR_REPORTING_SEC, TICK_INFINTY);
	if (!server->run()) {
		Log(L"! error: server start fail");
		return;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	shared_ptr<Thread> serverThread(new Thread(new thread_t(serverProcess), L"Server"));
	return 0;
}
