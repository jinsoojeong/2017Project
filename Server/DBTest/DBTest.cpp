// DBTest.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include "Query1.h"
#include "../ServerLibrary/ServerLibrary.h"

#ifdef _DEBUG
#pragma comment (lib, "ServerLibraryd.lib")
#else
#pragma comment (lib, "ServerLibrary.lib")
#endif

int main()
{
	DB_MANAGER.RegistDBProcess(L"DBJob", SingleThread);

	std::wstring server_name = L"192.168.10.19";
	std::wstring db_name = L"BS_JJS_GAME";
	std::wstring login = L"sa";
	std::wstring pwd = L"NSDev1234^^";

	if (DB_MANAGER.Run(L"DBJob", server_name, db_name, login, pwd) == false)
	{
		printf("db manager run failed");
		DB_MANAGER.Finalize();
		return -1;
	}

	GetQuest* query = new GetQuest();
	QueryStatement* statement = query->statement();
	statement->addParam((int)10086);					// 파라미터 계속 붙여나가기
	//statement->addParam((char *)"1q2w3e");

	DB_MANAGER.Enqueue(L"DBJob", query);

	while (true)
	{
		if (false)
			break;
	}

	DB_MANAGER.Finalize();

    return 0;
}

