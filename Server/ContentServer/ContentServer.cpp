// ContentServer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ContentServer.h"

class SystemReport : public WorkObject
{
	void tick()
	{
		double cpu_usage = SYSTEM_INFO.GetCpuUsage();
		size_t mem_usage = SYSTEM_INFO.GetMemUsage();

		Log(L"### cpu usage : %2.2f%%, memory usage : %uByte", cpu_usage, mem_usage);
	}
};

bool ServerProcess()
{
	Server::initialize(); // 서버 기본 라이브러리 로드

	TASK_MANAGER.add(new SystemReport(), 1, TICK_INFINTY);

	Server* server = new IOCPServer(new ContentServer());
	if (!server->run()) 
	{
		Log(L"! error: server start fail");
		return false;
	}

	return true;
}

int _tmain(int argc, _TCHAR* argv[])
{
	if (ServerProcess() == false)
	{
		_shutdown = true;
		return -1;
	}
	
	while (true)
	{
		std::wstring cmd;
		std::getline(std::wcin, cmd);

		if (cmd.compare(L"x"))
			continue;

		_shutdown = true;
		break;
	}

	return 0;
}

ContentServer::ContentServer() : ContentsProcess()
{
	RegistPacketFunc();
}

void ContentServer::RegistPacketFunc()
{
	REGIST_PACKET_PROCESS(ContentServer, I_CHTTING_NOTIFY_ID);
	REGIST_PACKET_PROCESS(ContentServer, I_DB_ANS_PARSE_DATA);
	REGIST_PACKET_PROCESS(ContentServer, C_REQ_REGIST_CHATTING_NAME);
	REGIST_PACKET_PROCESS(ContentServer, C_REQ_CHATTING);
	REGIST_PACKET_PROCESS(ContentServer, C_REQ_EXIT);
}

void ContentServer::Update()
{
	USER_MANAGER.Update();
}

//---------------------------------------------------------------//
//패킷 처리 정의
void ContentServer::I_CHTTING_NOTIFY_ID(Session *session, Packet *rowPacket)
{
	PK_I_CHTTING_NOTIFY_ID *packet = (PK_I_CHTTING_NOTIFY_ID *)rowPacket;

	PK_I_DB_REQ_LOAD_DATA dbPacket;
	dbPacket.clientId_ = packet->clientId_;
	dbPacket.oidAccountId_ = packet->oidAccountId_;

	Terminal *terminal = TERMINAL_MANAGER.get(L"DBAgent");
	terminal->sendPacket(&dbPacket);
}

void ContentServer::I_DB_ANS_PARSE_DATA(Session *session, Packet *rowPacket)
{
	PK_I_DB_ANS_PARSE_DATA *packet = (PK_I_DB_ANS_PARSE_DATA  *)rowPacket;

	PK_I_LOGIN_NOTIFY_ID_LOADED iPacket;
	iPacket.clientId_ = packet->clientId_;
	iPacket.name_ = packet->name_;
	iPacket.result_ = packet->result_;

	Log(L"* [%S] name load from db", iPacket.name_.c_str());
	Terminal *terminal = TERMINAL_MANAGER.get(L"LoginServer");
	terminal->sendPacket(&iPacket);
}

void ContentServer::C_REQ_REGIST_CHATTING_NAME(Session *session, Packet *rowPacket)
{
	PK_C_REQ_REGIST_CHATTING_NAME *packet = (PK_C_REQ_REGIST_CHATTING_NAME *)rowPacket;

	User *user = USER_MANAGER.Find(session->GetID());
	if (user != nullptr)
	{
		Log(L"! try duplicate regist : %s, name : %S", session->clientAddress().c_str(), packet->name_.c_str());
		session->onClose();
		return;
	}

	user = new User(session);

	array<WCHAR, SIZE_64> userName;
	StrConvA2W((CHAR *)packet->name_.c_str(), userName.data(), userName.size());
	user->SetNick(userName.data());

	USER_MANAGER.Regist(user);

	Log(L"* user [%s] created from [%S]", userName.data(), session->clientAddress().c_str());
}

void ContentServer::C_REQ_CHATTING(Session *session, Packet *rowPacket)
{
	PK_C_REQ_CHATTING *packet = (PK_C_REQ_CHATTING *)rowPacket;

	User *user = USER_MANAGER.Find(session->GetID());
	if (user == nullptr) {
		Log(L"! not registed : %s", session->clientAddress().c_str());
		session->onClose();
		return;
	}

	PK_S_ANS_CHATTING retPacket;
	array<char, SIZE_64> name;
	StrConvW2A((WCHAR *)user->GetNick().c_str(), name.data(), name.size());
	retPacket.name_ = name.data();
	retPacket.text_ = "-> : ";
	retPacket.text_ += packet->text_;

	Log(L"* send message %S, %S", retPacket.name_.c_str(), retPacket.text_.c_str());
	session->sendPacket(&retPacket);
}

void ContentServer::C_REQ_EXIT(Session *session, Packet *rowPacket)
{
	//클라이언트 read thread 를 종료시켜 주기 위해 처리
	PK_C_REQ_EXIT *packet = (PK_C_REQ_EXIT *)rowPacket;
	User *user = USER_MANAGER.Find(session->GetID());

	if (user == nullptr)
	{
		Log(L"! not registed : %s", session->clientAddress().c_str());
		session->onClose();
		return;
	}

	USER_MANAGER.UnRegist(session->GetID());

	PK_S_ANS_EXIT ansPacket;
	Log(L"* recv exit packet by [%s]", session->clientAddress().c_str());
	session->sendPacket(&ansPacket);
}
