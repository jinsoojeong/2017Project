#pragma once

// DB  ������ ���� ���� �ذ��ϱ� ���ؼ��� ADODatabase �������� ���Ǿ�� �Ѵ�.
// ADODatabase�� ���� �������� �Ŵ��� Ŭ������ �����Ѵ�.
// ���� ������ ���� �����Ƿ�, ������ ����Ǿ���ϴ� ���� �۾��� �и��� �ʿ䰡 �־� ���δ�.

#include "stdafx.h"
#include "ADODatabase.h"

enum DBProcessThread
{
	SingleThread,	// only 1���� ������
	OptimizeThread,	// cpu * 2 ���� ������
	ExpendThread	// ���� cpu * 2���� ������, ��� ������ Ȱ�� ���̶�� ������ Ȯ�� �ִ� int_max
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