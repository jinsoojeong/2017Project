// DBAgent.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "DBAgentProcess.h"

void serverProcess()
{
	shared_ptr<Server> server(new IOCPServer(new DBAgentProcess()));
	//std::shared_ptr<Server> server(new ServerASIO(2000));
	if (!server->run()) {
		Log(L"! error: server start fail");
		return;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	// DB 매니저 초기화
	DB_MANAGER.run();

	shared_ptr<Thread> serverThread(new Thread(new std::thread(serverProcess), L"DBAgent"));
	return 0;
}

