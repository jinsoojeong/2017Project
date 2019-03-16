#include "stdafx.h"
#include "MainProcess.h"

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
	//std::wstring server_name = L"DESKTOP-DE04DVM\\SQLEXPRESS";
	//std::wstring db_name = L"GAME_DB";
	//std::wstring login = L"JJS";
	//std::wstring pwd = L"dkTM37571@34";

	//DB_MANAGER.RegistDBProcess(L"ModifyProcess", SingleThread);
	//if (DB_MANAGER.Run(L"ModifyProcess", server_name, db_name, login, pwd) == false)
	//{
	//	Log(L"! error: db process start fail");
	//	return false;
	//}

	Server::initialize(); // 서버 기본 라이브러리 로드

	//TASK_MANAGER.add(new SystemReport(), 1, TICK_INFINTY);

	Server* server = new IOCPServer(new ContentServer());
	if (!server->run())
	{
		Log(L"! error: server start fail");
		return false;
	}

	return true;
}

int _tmain(int argc, _TCHAR* argv[])
{
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