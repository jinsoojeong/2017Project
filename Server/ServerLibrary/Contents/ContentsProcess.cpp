#pragma once
#include "stdafx.h"
#include "ContentsProcess.h"

ContentsProcess::ContentsProcess()
{
	msg_queue_ = new ThreadJobQueue<Package *>(L"ContentsProcessQueue");
	registDefaultPacketFunc();
}

ContentsProcess::~ContentsProcess()
{
	SAFE_DELETE(msg_queue_);
	SAFE_DELETE(content_main_thread);
	
	runFuncTable_.clear();
}

bool ContentsProcess::Run()
{
	// main update tick
	content_main_thread = MAKE_THREAD(ContentsProcess, process);

	if (content_main_thread == nullptr)
		return false;

	return true;
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
	PacketType type = package->GetPacket()->type();

	auto itr = runFuncTable_.find(type);
	if (itr == runFuncTable_.end()) 
	{
		Log(L"! invaild packet runFunction. type[%d]", type);
		package->GetSession()->onClose();
		return;
	}

	RunFunc runFunction = itr->second;

#ifdef _DEBUG
	Log(L"*** [%d] packet run ***", type);
#endif //_DEBUG

	runFunction(package->GetSession(), package->GetPacket());
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
	while (!_shutdown)
	{
		TryPopMsgCmd();
		Update();

		CONTEXT_SWITCH;
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