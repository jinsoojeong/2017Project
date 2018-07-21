#pragma once
#include "stdafx.h"
#include "User.h"

class User
{
public:
	User(Session *session);
	void Update();
	
	const Session& GetSession() { return *session_; }

	void SetNick(const std::wstring& nick) { nick_ = nick; }
	const std::wstring& GetNick() { return nick_; }

private:
	Session* session_;
	std::wstring nick_;
};