#include "stdafx.h"
#include "ContentProcess.h"

ContentServer::ContentServer()
{
	this->registSubPacketFunc();
}

void ContentServer::registSubPacketFunc()
{
#define INSERT_PACKET_PROCESS(type)		runFuncTable_.insert(make_pair(E_##type, &ContentServer::##type))

	INSERT_PACKET_PROCESS(I_CHTTING_NOTIFY_ID);
	INSERT_PACKET_PROCESS(I_DB_ANS_PARSE_DATA);
	INSERT_PACKET_PROCESS(C_REQ_REGIST_CHATTING_NAME);
	INSERT_PACKET_PROCESS(C_REQ_CHATTING);
	INSERT_PACKET_PROCESS(C_REQ_EXIT);
}

//---------------------------------------------------------------//
//패킷 처리 정의
void ContentServer::I_CHTTING_NOTIFY_ID(Session *session, Packet *rowPacket)
{
	PK_I_CHTTING_NOTIFY_ID *packet = (PK_I_CHTTING_NOTIFY_ID *)rowPacket;

	PK_I_DB_REQ_LOAD_DATA dbPacket;
	dbPacket.clientId_ = packet->clientId_;
	dbPacket.oidAccountId_ = packet->oidAccountId_;

	Terminal *terminal = _terminal.get(L"DBAgent");
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
	Terminal *terminal = _terminal.get(L"LoginServer");
	terminal->sendPacket(&iPacket);
}

void ContentServer::C_REQ_REGIST_CHATTING_NAME(Session *session, Packet *rowPacket)
{
	PK_C_REQ_REGIST_CHATTING_NAME *packet = (PK_C_REQ_REGIST_CHATTING_NAME *)rowPacket;
	User *user = UserManager::GetSingleton().at(session->id());
	if (user != nullptr) {
		Log(L"! try duplicate regist : %s, name : %S", session->clientAddress().c_str(), packet->name_.c_str());
		session->onClose();
		return;
	}
	user = new User(session);

	array<WCHAR, SIZE_64> userName;
	StrConvA2W((CHAR *)packet->name_.c_str(), userName.data(), userName.size());
	user->setName(userName.data());
	UserManager::GetSingleton().insert(user);
	
	Log(L"* user [%s] created from [%S]", userName.data(), session->clientAddress().c_str());
}

void ContentServer::C_REQ_CHATTING(Session *session, Packet *rowPacket)
{
	PK_C_REQ_CHATTING *packet = (PK_C_REQ_CHATTING *)rowPacket;
	
	User *user = UserManager::GetSingleton().at(session->id());
	if (user == nullptr) {
		Log(L"! not registed : %s", session->clientAddress().c_str());
		session->onClose();
		return;
	}
	
	PK_S_ANS_CHATTING retPacket;
	array<char, SIZE_64> name;
	StrConvW2A((WCHAR *)user->name().c_str(), name.data(), name.size());
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
	User *user = UserManager::GetSingleton().at(session->id());
	if (user == nullptr) {
		Log(L"! not registed : %s", session->clientAddress().c_str());
		session->onClose();
		return;
	}
	UserManager::GetSingleton().remove(session->id());

	PK_S_ANS_EXIT ansPacket;
	Log(L"* recv exit packet by [%s]", session->clientAddress().c_str());
	session->sendPacket(&ansPacket);
}