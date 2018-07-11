#pragma once

// DB  쿼리의 지연 등을 해결하기 위해서는 ADODatabase 복수개가 사용되어야 한다.
// ADODatabase의 관리 목적으로 매니저 클래스를 선언한다.
// 순서 보장이 되지 않으므로, 순서가 보장되어야하는 쿼리 작업과 분리될 필요가 있어 보인다.

#include "stdafx.h"
#include "ADODatabase.h"

class DBManager : public Singleton < DBManager >
{
	int                                 workerCount_;
	std::vector<Database *>             dbPool_;

	wstr_t								serverName_;
	wstr_t								dbName_;
	wstr_t								login_;
	wstr_t								password_;
	ThreadJobQueue<Query *>				*queryPool_;

public:
	DBManager();
	virtual ~DBManager();

	void initialize(xml_t *config);

	size_t runQueryCount();
	void pushQuery(Query *query);
	bool popQuery(Query **query);

	void run();
};

#define DB_MANAGER DBManager::GetSingleton()