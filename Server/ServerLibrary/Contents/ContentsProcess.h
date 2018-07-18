#pragma once
#include "stdafx.h"

// 컨텐츠를 여기서 파생해서 구현합니다.

#define MAX_PACKET_THREAD_		SIZE_64
#define REGIST_PACKET_PROCESS(name, type) runFuncTable_.insert(make_pair(E_##type, &##name::##type))

class ContentsProcess
{
public:
	ContentsProcess();
	~ContentsProcess();

	void putPackage(Package *package);

	virtual void RegistPacketFunc() = 0;

	//--------------------------------------------------------------//
	// 기본 패킷 기능 구현
	static void Packet_HeartBeat(Session *session, Packet *rowPacket);
	static void Packet_Notify_Terminal(Session *session, Packet *rowPacket);
	static void C_REQ_EXIT(Session *session, Packet *rowPacket);

protected:
	typedef std::function<void(Session *session, Packet *rowPacket)> RunFunc;
	unordered_map<PacketType, RunFunc> runFuncTable_;

	virtual void Update() = 0;

private:
	
	void initialize(xml_t *config);
	void registDefaultPacketFunc();
	void MsgHandler(Package *package);
	void TryPopMsgCmd();

	void process();

	array<Thread *, MAX_PACKET_THREAD_> threadPool_;
	ThreadJobQueue<Package *> *msg_queue_;
};
