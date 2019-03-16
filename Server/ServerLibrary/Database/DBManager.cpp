#include "stdafx.h"

DBManager::DBManager()
{
	//xml_t config;

	//if (!loadConfig(&config))
	//	return;

	//this->initialize(&config);
}

bool DBManager::RegistDBProcess(std::wstring process_name, DBProcessThread db_process_thread)
{
	//xmlNode_t *root = config->FirstChildElement("App")->FirstChildElement("DataBase");
	//if (!root) 
	//{
	//	Log(L"@ not exist database setting");
	//	return;
	//}

	//xmlNode_t *elem = root->FirstChildElement("ThreadCount");
	//sscanf_s(elem->GetText(), "%d", &workerCount_);

	//array<WCHAR, SIZE_256> tmp;
	//elem = root->FirstChildElement("ServerName");
	//StrConvA2W((char *) elem->GetText(), tmp.data(), tmp.max_size());
	//serverName_ = tmp.data();

	//elem = root->FirstChildElement("DB");
	//StrConvA2W((char *) elem->GetText(), tmp.data(), tmp.max_size());
	//dbName_ = tmp.data();

	//elem = root->FirstChildElement("Login");
	//StrConvA2W((char *) elem->GetText(), tmp.data(), tmp.max_size());
	//login_ = tmp.data();

	//elem = root->FirstChildElement("Password");
	//StrConvA2W((char *) elem->GetText(), tmp.data(), tmp.max_size());
	//password_ = tmp.data();

	if (query_pool_by_process_.find(process_name) != query_pool_by_process_.end())
	{
		Log(L"DB Process Regist Failed Already Regist Name - %s", process_name.c_str());
		return false;
	}

	int thread_count = 0;
	DBProcess* db_process = new DBProcess(process_name, db_process_thread);

	switch (db_process_thread)
	{
		case SingleThread:
		{
			thread_count = 1;
		}
		break;
		case OptimizeThread:
		case ExpendThread:
		{
			thread_count = SYSTEM_INFO.GetNumberOfProcessors() * 2;
		}
		break;
	}

	query_pool_by_process_[process_name] = new ThreadJobQueue<Query *>(process_name.c_str());
	for (int i = 0; i < thread_count; ++i)
	{
		ADODatabase *adodb = new ADODatabase(process_name);
		db_process->Regist(adodb);	
	}

	db_pool_by_process_[process_name] = db_process;

	return true;
}

DBManager::~DBManager()
{
	Finalize();
}

void DBManager::Finalize()
{
	for each (QueryPool::value_type value in query_pool_by_process_)
	{
		QueryQueue* query_pool = value.second;
		SAFE_DELETE(query_pool);
	}

	for each (DBPool::value_type value in db_pool_by_process_)
	{
		DBProcess* db_process = value.second;
		SAFE_DELETE(db_process);
	}
}

bool DBManager::RunCount(std::wstring process_name, DWORD& size)
{
	QueryQueue* query_queue = FindQueryQueue(process_name);
	if (query_queue == nullptr)
		return false;

	size = static_cast<DWORD>(query_queue->size());

	return true;
}

bool DBManager::Enqueue(std::wstring process_name, Query *query)
{
	QueryQueue* query_queue = FindQueryQueue(process_name);
	if (query_queue == nullptr)
		return false;

	query_queue->push(query);
	return true;
}

bool DBManager::Dequeue(std::wstring process_name, Query **query)
{
	QueryQueue* query_queue = FindQueryQueue(process_name);
	if (query_queue == nullptr)
		return false;

	query_queue->pop(*query);
	return true;
}

bool DBManager::Run(std::wstring process_name, std::wstring server_name, std::wstring db_name, std::wstring login_id, std::wstring password)
{
	DBProcess* db_process = FindDBProcess(process_name);
	if (db_process == nullptr)
		return false;

	for (auto db : db_process->database_list)
	{
		if (db->state() != DB_WAIT)
			continue;

		if (!db->Connect(server_name.c_str(), db_name.c_str(), login_id.c_str(), password.c_str()))
		{
			Log(L"! db[%s] connection error", db_name.c_str());
			return false;
		}

        db->Run();
    }

	return true;
}

DBManager::QueryQueue* DBManager::FindQueryQueue(std::wstring process_name)
{
	QueryPool::iterator itor = query_pool_by_process_.find(process_name);
	if (itor == query_pool_by_process_.end())
		return nullptr;

	return (*itor).second;
}

DBManager::DBProcess* DBManager::FindDBProcess(std::wstring process_name)
{
	DBPool::iterator itor = db_pool_by_process_.find(process_name);
	if (itor == db_pool_by_process_.end())
		return nullptr;

	return (*itor).second;
}