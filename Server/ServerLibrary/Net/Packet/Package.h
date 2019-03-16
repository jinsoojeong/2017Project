#pragma once
#include "stdafx.h"

class Session;
class Package
{
public:
	Package(Session *session, Packet *packet)
	{
		session_ = session;
		packet_ = packet;
	}

	~Package()
	{
		session_ = nullptr;
		SAFE_DELETE(packet_);
	}

	Session* GetSession() { return session_; }
	Packet* GetPacket() { return packet_; }

private:
	Session *session_;
	Packet *packet_;
};