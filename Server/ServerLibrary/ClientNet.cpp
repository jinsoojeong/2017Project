#include "stdafx.h"
#include "ClientNet.h"

ClientNet::ClientNet()
{

}

ClientNet::~ClientNet()
{
	WSACleanup();
	closesocket(socket_);
}

bool ClientNet::Init()
{
	WSADATA wsa;

	int error_code = WSAStartup(MAKEWORD(2, 2), &wsa);
	if (error_code)
		return false;

	socket_ = WSASocket(AF_INET, SOCK_STREAM, NULL, NULL, 0, WSA_FLAG_OVERLAPPED);
	if (socket_ == INVALID_SOCKET)
		return false;

	return true;
}

bool ClientNet::Connect(std::string& ip, WORD port)
{
	SOCKADDR_IN	sa;
	memset(&sa, 0, sizeof(SOCKADDR_IN));
	sa.sin_family = AF_INET;
	sa.sin_port = htons(port);
	inet_pton(AF_INET, ip.c_str(), &sa.sin_addr);

	int sock_err = connect(socket_, (LPSOCKADDR)&sa, sizeof(sa));
	if (sock_err == SOCKET_ERROR)
	{
		int error_code = WSAGetLastError();
		if (error_code != WSA_IO_PENDING)
			return false;
	}

	return true;
}

bool ClientNet::Run()
{
	return true;
}

bool ClientNet::Recv(CHAR* buffer)
{
	WSABUF wb;
	wb.buf = buffer, wb.len = sizeof(buffer);

	DWORD dwFlags = 0;

	OVERLAPPED ov;
	memset(&ov, 0, sizeof(ov));

	int socket_error = WSARecv(socket_, &wb, 1, NULL, &dwFlags, &ov, NULL);
	if (socket_error == SOCKET_ERROR)
	{
		int error_code = WSAGetLastError();
		if (error_code != WSA_IO_PENDING)
			return false;
	}

	return true;
}

bool ClientNet::Send()
{
	return true;
}