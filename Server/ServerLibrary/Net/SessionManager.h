#pragma once
#include "stdafx.h"
#include "Session.h"
//http://duongame.tistory.com/36  다른 이야기이긴 하나 모바일 서버 만드는데 도움은 될듯
// 세션을 관리 하는 주체

#define SESSION_CAPACITY		(5000)

class SessionManager : public Singleton<SessionManager>
{
public:
	SessionManager(int maxConnection = SESSION_CAPACITY);
	~SessionManager();
	DWORD GenerateID() { return seed_++; };

	bool addSession(Session *session);

	list<Session*> &sessionList();
	bool closeSession(Session *session);
	void forceCloseSession(Session *session);

	Session* Find(DWORD id);

    void runCommand(wstr_t cmd);
    void commandFuncInitialize();

private:
	typedef list<Session*> SessionList;

	SessionList sessionList_;
	int sessionCount_;
	int maxConnection_;
	Lock lock_;

	DWORD seed_;

	typedef std::function<void(SessionList *sessionList, wstr_t *arg)> cmdFunc;
	unordered_map<wstr_t, cmdFunc>   serverCommand_;
};

#define SESSION_MANAGER SessionManager::GetSingleton()