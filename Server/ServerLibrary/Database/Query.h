#pragma once

// Query 클래스는 QueryStatement, QueryRecord 를 통해 쿼리를 질의하고 콜백을 받는 작업을 수행하는 클래스 이다.

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
		
	// 원래는 가상함수로 호출해서 뒷처리를 시키는게 맞는데... 그러면 h, cpp 파일 둘다 만들어야 함.
	// 그냥 소멸자에 후처리를 하도록 처리
//protected:
//	virtual void doRespon() = 0;
};