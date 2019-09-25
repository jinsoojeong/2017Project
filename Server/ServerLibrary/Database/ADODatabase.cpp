#include "stdafx.h"
#include "ADODatabase.h"
#include "QueryStatement.h"
#include "DBManager.h"

ADODatabase::ADODatabase(std::wstring process_name) : process_name_(process_name)
{
	::CoInitialize(NULL);
    state_ = DB_WAIT;

	dbConnection_.CreateInstance(__uuidof(ADODB::Connection));
	if (dbConnection_ == NULL) 
	{
		Log(L"! Database init fail");
	}

    const int TIME_OUT = 30;
    setConnectTimeOut(TIME_OUT);
}

ADODatabase::~ADODatabase()
{
    Disconnect();

    if (dbConnection_)
        dbConnection_.Release();
    
	SAFE_DELETE(thread_);
	::CoUninitialize();
}

HRESULT	ADODatabase::setConnectTimeOut(long second)
{
	if (!dbConnection_){
		return S_FALSE;
	}
	return dbConnection_->put_ConnectionTimeout(second);
}

void ADODatabase::comError(const WCHAR *actionName, _com_error &e)
{
    Log(L"! [%s]DB [%s] fail [%s]", dbName_.c_str(), actionName, (WCHAR *)e.Description());
}

bool ADODatabase::Connect()
{
	if (!dbConnection_) {
		return false;
	}

	try {
		HRESULT hr = dbConnection_->Open(connectionStr_.c_str(), _T(""), _T(""), NULL);
		if (SUCCEEDED(hr)) {
			dbConnection_->PutCursorLocation(ADODB::adUseClient);
			Log(L"* [%s]DB connection success", dbName_.c_str());
			state_ = DB_READY;
			return true;
		}
	}
	catch (_com_error &e) {
		this->comError(L"connction", e);
	}

	return false;
}

bool ADODatabase::Connect(const WCHAR *provider, const WCHAR *serverName, const WCHAR *dbName, const WCHAR *id, const WCHAR *password)
{
	array<WCHAR, SIZE_128> buffer;
	snwprintf(buffer, L"Provider=%s;Server=%s;Database=%s;Uid=%s;Pwd=%s;", provider, serverName, dbName, id, password);
    connectionStr_ = buffer.data();
    Log(L"* [%s]DB try connection provider = %s", dbName_.c_str(), provider);

	return this->Connect();
}

bool ADODatabase::Connect(const WCHAR *serverName, const WCHAR *dbName, const WCHAR *id, const WCHAR *password)
{
    dbName_ = dbName;
	Log(L"* connect try: %s, %s, %s", dbName, id, password);

	for (int index = 10; index < 20; ++index) {
		array<WCHAR, SIZE_64> mssqlName;
		snwprintf(mssqlName, L"SQLNCLI%d", index);
		if (this->Connect(mssqlName.data(), serverName, dbName, id, password)) 
		{
			Log(L"* database %s : %s connect", mssqlName, dbName);
			return true;
		}
	}

	//mssql 2005, 2008로 접속시
	if (this->Connect(L"SQLNCLI", serverName, dbName, id, password)) 
	{
		Log(L"* database SQLNCLI : %s connect",  dbName);
		return true;
	}

	return false;
}

bool ADODatabase::Connected()
{
    return dbConnection_->State != ADODB::adStateClosed ? true : false;
}

bool ADODatabase::Disconnect()
{
	if (!dbConnection_) {
		return false;
	}
    if (state_ == DB_WAIT) {
        return true;
    }
	try {
        this->execute();

        if (!dbConnection_) {
            return true;
        }
		dbConnection_->Close();
        state_ = DB_WAIT;

        connectionStr_.clear();
        dbName_.clear();
        Log(L"* database close");
		return true;
	} catch (...) {
        Log(L"! Database[%s] disconnect fail", dbName_.c_str());
	}
	return false;
}

void ADODatabase::execute()
{
	DWORD run_count = 0;
	if (DB_MANAGER.RunCount(process_name_, run_count) == false || run_count == 0)
		return;

	Query *query = nullptr;
	if (DB_MANAGER.Dequeue(process_name_, &query) == false)
		return;
	
	QueryStatement *statement = query->statement();

	const WCHAR *sqlQuery = statement->query();
	try 
	{
		state_ = DB_RUNNING;
		QueryRecord record;

		ADODB::_CommandPtr command;
		command.CreateInstance(__uuidof(ADODB::Command));
		command->ActiveConnection = dbConnection_;
		command->CommandType = ADODB::adCmdText;
		command->CommandText = sqlQuery;
		_variant_t resultVal;

		switch (statement->type()) {
		case QUERY_NOT_RETURN:
			record = command->Execute(&resultVal, NULL, ADODB::adCmdText | ADODB::adExecuteNoRecords);
			break;
		case QUERY_WAIT_RETURN:
			record = command->Execute(&resultVal, NULL, ADODB::adCmdText | ADODB::adExecuteRecord);
			break;
		case QUERY_CALL_BACK:
			record = command->Execute(&resultVal, NULL, ADODB::adCmdText | ADODB::adAsyncFetchNonBlocking);
			break;
		}

		if (record.isEof()) 
		{
			int quertResultVal = atol((char*)((_bstr_t)resultVal));
			
			if (quertResultVal < 1)
			{
				Log(L"* query : [%s] have error code [%d] ", sqlQuery, quertResultVal);
			}
			else
				record.setResultVal(quertResultVal);
		}
		
		query->result() = record;
		state_ = DB_READY;

		if (query->result().resultVal() == 0)
			query->Commit();
		else
			query->Rollback();

		Log(L"* Run query [%s] result [%d]", sqlQuery, record.resultVal());
	}
	catch (_com_error &e) 
	{
		comError(L"execute", e);
	}

	SAFE_DELETE(query);
}

void ADODatabase::process()
{
    while (_shutdown == false) 
	{
		if (!this->Connected()) 
		{
			Log(L"! db[%s] connection disconnect", dbName_.c_str());
			ASSERT(FALSE);
		}
		this->execute();

		CONTEXT_SWITCH;
    }
}

void ADODatabase::Run()
{
	thread_ = MAKE_THREAD(ADODatabase, process);
}
