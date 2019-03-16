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
	DB_MANAGER.RegistDBProcess(L"DBProcess", SingleThread);

	std::wstring server_name = L"DESKTOP-DE04DVM\\SQLEXPRESS";
	std::wstring db_name = L"GAME_DB";
	std::wstring login = L"JJS";
	std::wstring pwd = L"dkTM37571@34";

	if (DB_MANAGER.Run(L"DBProcess", server_name, db_name, login, pwd) == false)
	{
		printf("db manager run failed");
		DB_MANAGER.Finalize();
		return -1;
	}

	QI_DB_REQ_ID_PW* query = new QI_DB_REQ_ID_PW();

	QueryStatement* statement = query->statement();
	statement->addParam((char *)"test-01");					// 파라메터 계속 붙여나가기
	statement->addParam((char *)"1q2w3e");

	DB_MANAGER.Enqueue(L"ModifyProcess", query);

	while (true)
	{
		if (false)
			break;
	}

	DB_MANAGER.Finalize();

    return 0;
}

