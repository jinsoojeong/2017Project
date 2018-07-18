#include "stdafx.h"
#include "UserManager.h"

void UserManager::Update()
{
	//std::for_each(users_.begin(), users_.end(), [](Users::iterator itor) { (*itor).second->Update(); });
}

void UserManager::insert(User* user)
{
	oid_t key = user->session()->id();
	users_.insert(make_pair(key, user));
}

void UserManager::remove(oid_t id)
{
	users_.erase(id);
}

User* UserManager::at(oid_t id)
{
	auto itr = users_.lower_bound(id);
	
	if (itr == users_.end())
		return nullptr;
	
	return itr->second;
}
