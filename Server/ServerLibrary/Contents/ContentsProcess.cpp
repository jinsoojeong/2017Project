#pragma once
#include "stdafx.h"
#include "ContentsProcess.h"

ContentsProcess::ContentsProcess()
{
	xml_t config;
	if (!loadConfig(&config)) {
		return;
	}
	this->initialize(&config);
}

ContentsProcess::~ContentsProcess()
{
	SAFE_DELETE(msg_queue_);

	for (Thread* thread : threadPool_)
		SAFE_DELETE(thread);
	
	runFuncTable_.clear();
}

void ContentsProcess::initialize(xml_t *config)
{
	msg_queue_ = new ThreadJobQueue<Package *> (L"ContentsProcessQueue");
	threadPool_[0] = MAKE_THREAD(ContentsProcess, process);
	registDefaultPacketFunc();
}

void ContentsProcess::registDefaultPacketFunc()
{
	runFuncTable_.insert(make_pair(E_C_NOTIFY_HEARTBEAT, &ContentsProcess::Packet_HeartBeat));
	runFuncTable_.insert(make_pair(E_I_NOTIFY_TERMINAL, &ContentsProcess::Packet_Notify_Terminal));
	runFuncTable_.insert(make_pair(E_C_REQ_EXIT, &ContentsProcess::C_REQ_EXIT));
}

void ContentsProcess::putPackage(Package *package)
{
	msg_queue_->push(package);
}

void ContentsProcess::MsgHandler(Package *package)
{
	PacketType type = package->packet_->type();

	auto itr = runFuncTable_.find(type);
	if (itr == runFuncTable_.end()) 
	{
		Log(L"! invaild packet runFunction. type[%d]", type);
		package->session_->onClose();
		return;
	}

	RunFunc runFunction = itr->second;

#ifdef _DEBUG
	Log(L"*** [%d] packet run ***", type);
#endif //_DEBUG

	runFunction(package->session_, package->packet_);
}

void ContentsProcess::TryPopMsgCmd()
{
	Package *msg = nullptr;

	while (msg_queue_->pop(msg))
	{
		MsgHandler(msg);
		SAFE_DELETE(msg);
	}

}

void ContentsProcess::process()
{
	while (_shutdown == false) 
	{
		TryPopMsgCmd();

		Update();
	}
}

//--------------------------------------------------------------//
// 기본 패킷 기능 구현
void ContentsProcess::Packet_HeartBeat(Session *session, Packet *rowPacket)
{
	if (session->GetType() != SESSION_TYPE_CLIENT)
		return;
	
	session->updateHeartBeat();
}

void ContentsProcess::Packet_Notify_Terminal(Session *session, Packet *rowPacket)
{
	session->SetType(SESSION_TYPE_TERMINAL);
	Log(L"* [%s] Terminal accepted.", session->clientAddress().c_str());
}

void ContentsProcess::C_REQ_EXIT(Session *session, Packet *rowPacket)
{
	//클라이언트 read thread 를 종료시켜 주기 위해 처리
	PK_C_REQ_EXIT *packet = (PK_C_REQ_EXIT *)rowPacket;
	PK_S_ANS_EXIT ansPacket;
	Log(L"* recv exit packet by [%s]", session->clientAddress().c_str());
	session->sendPacket(&ansPacket);
}