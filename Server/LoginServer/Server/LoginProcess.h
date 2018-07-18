#pragma once

// 로그인 서버의 MainProcess

#include "stdafx.h"

class LoginProcess : public ContentsProcess
{
public:
	LoginProcess();

private:
	void RegistPacketFunc();

	static void C_REQ_ID_PW(Session *session, Packet *packet);
	static void I_DB_ANS_ID_PW(Session *session, Packet *packet);
	static void I_LOGIN_NOTIFY_ID_LOADED(Session *session, Packet *packet);
};