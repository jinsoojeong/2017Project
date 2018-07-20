#pragma once
#include "stdafx.h"
class Session;
class SessionManager;
class Package;

enum IO_OPERATION
{
	IO_READ,
	IO_WRITE,
	IO_ERROR
};

#define IO_DATA_MAX     (2)

class IoData
{
	OVERLAPPED		overlapped_;
	IO_OPERATION	ioType_;
    size_t  		totalBytes_;
	size_t			currentBytes_;
	array<char, SOCKET_BUF_SIZE> buffer_;

public:
	IoData();

	void clear();

	bool needMoreIO(size_t transferSize);
	int32_t setupTotalBytes();
	size_t totalByte();

	IO_OPERATION &type();
	void setType(IO_OPERATION type);

	WSABUF wsabuf();
	char *data();
	bool setData(Stream &stream);
	LPWSAOVERLAPPED overlapped();
};

//-----------------------------------------------------------------//
class IOCPSession : public Session
{
public:
	IOCPSession(DWORD id);
	~IOCPSession();

	void			initialize();
	void			checkErrorIO(DWORD ret);
	void			recv(WSABUF wsaBuf);
	bool			isRecving(size_t transferSize);
	void			send(WSABUF wsaBuf);
	void			onSend(size_t transferSize);
	void		    sendPacket(Packet *packet);
	void ClearIoData(IO_OPERATION io_operation) { ioData_[io_operation].clear(); }
	void			recvStandBy();
	Package*		onRecv(size_t transferSize);

private:
	array<IoData, IO_DATA_MAX> ioData_;
	
};
