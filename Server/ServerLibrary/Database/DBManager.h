#pragma once

// DB  쿼리의 지연 등을 해결하기 위해서는 ADODatabase 복수개가 사용되어야 한다.
// ADODatabase의 관리 목적으로 매니저 클래스를 선언한다.
// 순서 보장이 되지 않으므로, 순서가 보장되어야하는 쿼리 작업과 분리될 필요가 있어 보인다.

#include "stdafx.h"
#include "ADODatabase.h"

enum DBProcessThread
{
	SingleThread,	// only 1개의 스레드
	OptimizeThread,	// cpu * 2 개의 스레드
	ExpendThread	// 최초 cpu * 2개의 스레드, 모든 스레드 활동 중이라면 스레드 확장 최대 int_max
};

class DBManager : public Singleton<DBManager>
{
public:
	DBManager();
	virtual ~DBManager();

	bool RegistDBProcess(std::wstring process_name, DBProcessThread db_process_thread);
	bool Run(std::wstring process_name, std::wstring server_name, std::wstring db_name, std::wstring login_id, std::wstring password);
	bool Enqueue(std::wstring process_name, Query *query);
	void Finalize();
	
private:
	friend class ADODatabase;

	struct DBProcess
	{
		DBProcess(std::wstring name, DBProcessThread type) : process_name(name), db_process_thread(type)
		{
		}

		~DBProcess()
		{
			for (Database* db : database_list)
			{
				db->Disconnect();
				SAFE_DELETE(db);
			}
		}

		void Regist(Database* db)
		{
			database_list.push_back(db);
		}

		std::wstring process_name;
		DBProcessThread db_process_thread;
		std::list<Database *> database_list;
	};

	typedef ThreadJobQueue<Query *> QueryQueue;
	typedef std::map<std::wstring, QueryQueue*> QueryPool;
	typedef std::map<std::wstring, DBProcess*> DBPool;

	QueryQueue* FindQueryQueue(std::wstring process_name);
	DBProcess* FindDBProcess(std::wstring process_name);
	bool Dequeue(std::wstring process_name, Query **query);
	bool RunCount(std::wstring process_name, DWORD& size __out);

	DBPool db_pool_by_process_;
	QueryPool query_pool_by_process_;
};

#define DB_MANAGER DBManager::GetSingleton()