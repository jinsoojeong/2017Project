#pragma once

// DB  ������ ���� ���� �ذ��ϱ� ���ؼ��� ADODatabase �������� ���Ǿ�� �Ѵ�.
// ADODatabase�� ���� �������� �Ŵ��� Ŭ������ �����Ѵ�.
// ���� ������ ���� �����Ƿ�, ������ ����Ǿ���ϴ� ���� �۾��� �и��� �ʿ䰡 �־� ���δ�.

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