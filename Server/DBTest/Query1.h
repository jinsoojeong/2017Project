#pragma once
#include "stdafx.h"
#include "../ServerLibrary/ServerLibrary.h"

class QI_DB_REQ_ID_PW : public Query
{
public:
	typedef std::function<void()> Completion;

	QI_DB_REQ_ID_PW()
	{
		statement_->setQuery(const_cast<wchar_t*>(procedure().c_str()), QUERY_CALL_BACK);		// 실행할 쿼리 설정
	}

	~QI_DB_REQ_ID_PW() {}

	std::wstring procedure()
	{
		return L"p_AccountData_Select";
	}

	//bool DoWork() override
	//{

	//}

	void Commit() override
	{
		PK_I_DB_ANS_ID_PW iPacket;
		iPacket.clientId_ = (UInt64)clientId_;
		iPacket.result_ = FALSE;
		if (!record_.isEof())
			record_.moveFirst();

		while (!record_.isEof())
		{
			int oidAccount = 0;
			if (record_.get("oidAccount", oidAccount)) {
				iPacket.oidAccountId_ = oidAccount;
				iPacket.result_ = TRUE;
				break;
			}
			else {
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