#pragma once

#include "stdafx.h"

class ClientNet
{
public:
	ClientNet();
	virtual ~ClientNet();

	bool Init();
	bool Connect(std::string& ip, WORD port);
	bool Run();
	bool Recv(CHAR* buffer);
	bool Send();

private:
	SOCKET socket_;
};