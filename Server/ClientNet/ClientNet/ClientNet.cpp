// ClientTest.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"

#ifdef _DEBUG
	#pragma comment (lib, "ServerLibraryd.lib")
#else
	#pragma comment (lib, "ServerLibrary.lib")
#endif //_DEBUG


int main()
{
	ClientNet client_net;
	if (client_net.Init() == false)
		return -1;

	std::string ip = "127.0.0.1";

	client_net.Connect(ip, 9000);

	return 0;
}

