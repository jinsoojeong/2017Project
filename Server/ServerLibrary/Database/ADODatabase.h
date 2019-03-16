#pragma once

// ADODB 는 MS 종속적 개념
// ADO는 OLEDB를 좀 더 편하게 랩핑한 인터페이스

#include "stdafx.h"
#include <ole2.h>
#include <comdef.h>
#include <comutil.h>
#include <conio.h>

#import "c:\Program Files\Common Files\System\ADO\msado15.dll"  rename("EOF", "EndOfFile")
#include "Database.h"

typedef ADODB::_ConnectionPtr           dbConnectionPtr;
typedef ADODB::_CommandPtr				commandPtr;
typedef ADODB::_RecordsetPtr			recordPtr;

class ADODatabase : public Database
{
public:
	ADODatabase(std::wstring process_name);
	virtual ~ADODatabase();

	HRESULT	setConnectTimeOut(long second);
	void comError(const WCHAR *actionName, _com_error &e);

    bool Connect(const WCHAR *provider, const WCHAR *serverName, const WCHAR *dbName, const WCHAR *id, const WCHAR *password);

    bool Connect(const WCHAR *serverName, const WCHAR *dbName, const WCHAR *id, const WCHAR *password) override;
    bool Connect() override;
    bool Connected() override;
    bool Disconnect() override;
    
	void Run() override;

private:
    void execute();
    void process();

	dbConnectionPtr dbConnection_;
	wstr_t connectionStr_;
	wstr_t dbName_;

	Thread *thread_;
	std::wstring process_name_;
};
