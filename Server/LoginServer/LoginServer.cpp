// LoginServer
// 계정 인증 및 컨텐츠 서버의 입장을 허가하는 작업을 수행

#include "stdafx.h"

class SystemReport : public WorkObject
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
	TASK_MANAGER.add(new SystemReport(), 1, TICK_INFINTY);

	shared_ptr<Server> server(new IOCPServer(new LoginProcess()));
	if (server->run()) 
	{
		Log(L"! error: server start fail");
		return;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	shared_ptr<Thread> server_main_thread(new Thread(new std::thread(ServerProcess), L"Server"));

	return 0;
}
