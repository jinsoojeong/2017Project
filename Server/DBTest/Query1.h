#pragma once
#include "stdafx.h"
#include "../ServerLibrary/ServerLibrary.h"

class GetQuest : public Query
{
public:
	typedef std::function<void()> Completion;

	GetQuest()
	{
		statement_->setQuery(const_cast<wchar_t*>(procedure().c_str()), QUERY_CALL_BACK);		// 실행할 쿼리 설정
	}

	~GetQuest() {}

	std::wstring procedure()
	{
		return L"USP_BS_GET_LIST_QUEST";
	}

	//bool DoWork() override
	//{

	//}

	void Commit() override
	{
		if (!record_.isEof())
			record_.moveFirst();

		while (!record_.isEof())
		{
			int quest_id = 0;
			if (record_.get("QUEST_IDX", quest_id))
			{
				Log(L"quest_id [%d]", quest_id);
			}
			else 
			{
				Log(L"* this query [%s] have error", this->procedure());
				break;
			}

			record_.moveNext();
		}
	}

	void Rollback() override
	{

	}

private:
	oid_t clientId_;
	Completion completion_;
};