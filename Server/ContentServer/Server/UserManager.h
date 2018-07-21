#pragma once

class User;
class Session;

class UserManager : public Singleton <UserManager>
{
public:
	UserManager() {};
	~UserManager() {};

	void Update();

	bool Regist(User* user);
	void UnRegist(DWORD id);
	User* Find(DWORD id);
	DWORD CurrentCount() { return static_cast<DWORD>(users_.size()); }

private:
	typedef unordered_map<DWORD, User*> Users;
	Users users_;
};

#define USER_MANAGER UserManager::GetSingleton()