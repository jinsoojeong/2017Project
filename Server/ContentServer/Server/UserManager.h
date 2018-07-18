#pragma once

class User;
class Session;

class UserManager : public Singleton <UserManager>
{
public:
	UserManager() {};
	~UserManager() {};

	void Update();

	void insert(User *user);
	void remove(oid_t id);
	User* at(oid_t id);
	size_t size() { return users_.size(); }

private:
	typedef unordered_map<oid_t, User*> Users;
	Users users_;
};

#define USER_MANAGER UserManager::GetSingleton()