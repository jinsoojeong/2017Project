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

bool ServerProcess()
{
	Server::initialize(); // 서버 기본 라이브러리 로드

	//TASK_MANAGER.add(new SystemReport(), 1, TICK_INFINTY);

	Server* server  = new IOCPServer(new LoginProcess());
	if (!server->run()) 
	{
		Log(L"! error: server start fail");
		return false;
	}

	return true;
}

int _tmain(int argc, _TCHAR* argv[])
{
	std::wstring server_name = L"DESKTOP-DE04DVM\\SQLEXPRESS";
	std::wstring db_name = L"GAME_DB";
	std::wstring login = L"JJS";
	std::wstring pwd = L"dkTM37571@34";

	DB_MANAGER.RegistDBProcess(L"DBProcess", SingleThread);
	if (DB_MANAGER.Run(L"DBProcess", server_name, db_name, login, pwd) == false)
	{
		_shutdown = true;
		return -1;
	}

	if (ServerProcess() == false)
	{
		_shutdown = true;
		return -1;
	}

	while (true)
	{
		std::wstring cmd;
		std::getline(std::wcin, cmd);

		if (cmd.compare(L"x"))
			continue;

		_shutdown = true;
		break;
	}

	return 0;
}
