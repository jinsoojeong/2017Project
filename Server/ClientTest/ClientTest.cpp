// ClientTest.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"

int main()
{
	ClientNet client_net;
	if (client_net.Init() == false)
		return -1;

	std::string ip = "127.0.0.1";

	client_net.Connect(ip, 9000);

    return 0;
}

