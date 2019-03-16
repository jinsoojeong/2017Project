#pragma once

// Query Ŭ������ QueryStatement, QueryRecord �� ���� ������ �����ϰ� �ݹ��� �޴� �۾��� �����ϴ� Ŭ���� �̴�.

#include "stdafx.h"
#include "ADODatabase.h"
#include "QueryRecord.h"
#include "QueryStatement.h"
class Query
{
public:
	Query();
	virtual ~Query();
	
	void setResult(recordPtr record);
	QueryRecord &result();

	void setStatement(QueryStatement *statement);
	QueryStatement *statement();

	virtual void Commit() = 0;
	virtual void Rollback() = 0;

protected:
	QueryStatement * statement_;
	QueryRecord record_;
		
	// ������ �����Լ��� ȣ���ؼ� ��ó���� ��Ű�°� �´µ�... �׷��� h, cpp ���� �Ѵ� ������ ��.
	// �׳� �Ҹ��ڿ� ��ó���� �ϵ��� ó��
//protected:
//	virtual void doRespon() = 0;
};