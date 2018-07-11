#pragma once

// 
#include "stdafx.h"

class LoginProcess : public ContentsProcess
{
public:
	LoginProcess();
private:
	void registSubPacketFunc(); // 해당 프로세스에서 사용될 패킷 ID 등록
	static void C_REQ_ID_PW(Session *session, Packet *rowPacket);
	static void I_DB_ANS_ID_PW(Session *session, Packet *rowPacket);
	static void I_LOGIN_NOTIFY_ID_LOADED(Session *session, Packet *rowPacket);
};