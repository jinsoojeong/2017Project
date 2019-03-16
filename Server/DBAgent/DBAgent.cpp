// DBAgent.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "DBAgentProcess.h"

bool ServerProcess()
{
	Server* server = new IOCPServer(new DBAgentProcess());
	//std::shared_ptr<Server> server(new ServerASIO(2000));
	if (!server->run()) 
	{
		Log(L"! error: server start fail");
		return false;
	}

	return true;
}

int _tmain(int argc, _TCHAR* argv[])
{
	// DB 매니저 초기화
	DB_MANAGER.run();

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

