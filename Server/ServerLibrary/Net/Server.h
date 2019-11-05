#pragma once
#include "stdafx.h"
#include "SessionManager.h"

// 서버의 공통 모듈 처리

enum SERVER_STATUS 
{
	SERVER_STOP,
	SERVER_INITIALZE,
	SERVER_READY,
	SERVER_OPERATION
};

#define HEAP_STANDARD 0
#define HEAP_LAL 1
#define HEAP_LFH 2

class Server
{
public:
	Server(ContentsProcess *contentsProcess);
	virtual ~Server();

	virtual void initialize(xml_t *config);
	virtual bool run();

	bool static initialize();
	SERVER_STATUS state() { return state_; }
	void EnqueueMsg(Package *package) { contentsProcess_->putPackage(package); }

protected:
	int port() { return port_; }
	std::string ip() { return ip_; }
	int worker_count() { return worker_count_; }
	void SetServerState(SERVER_STATUS state) { state_ = state; }

private:
	bool static initializeModule();
	bool static initializeWinSock();

	std::string ip_;
	int port_;
	int worker_count_;
	SERVER_STATUS state_;
	ContentsProcess *contentsProcess_;

};