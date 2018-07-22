#include "stdafx.h"
#include "UserManager.h"

void UserManager::Update()
{
	std::for_each(users_.begin(), users_.end(), [](Users::value_type itor) { (itor).second->Update(); });
}

bool UserManager::Regist(User* user)
{
	DWORD uid = user->GetSession().GetID();

	if (users_.find(uid) != users_.end())
	{
		Log(L"user login failed - already user login id:[%d]", uid);
		return false;
	}

	users_.insert(Users::value_type(uid, user));

	return true;
}

void UserManager::UnRegist(DWORD uid)
{
	users_.erase(uid);
}

User* UserManager::Find(DWORD uid)
{
	Users::iterator itor = users_.find(uid);

	if (itor == users_.end())
		return nullptr;
	
	return (*itor).second;
}
