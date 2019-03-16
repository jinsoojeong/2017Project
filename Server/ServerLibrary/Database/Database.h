#pragma once

// DB ÀÛ¾÷À» ÃÑ°ýÇÏ´Â Å¬·¡½º
// 

#include "stdafx.h"

typedef enum
{
    DB_WAIT,
    DB_READY,
	DB_RUNNING,
}DB_STATE;

class Database
{
public:
    Database() {}
	virtual ~Database() {}

    virtual bool Connect(const WCHAR *serverName, const WCHAR *dbName, const WCHAR *id, const WCHAR *password) = 0;
    virtual bool Connect() = 0;
    virtual bool Connected() = 0;
    virtual bool Disconnect() = 0;

    virtual void Run() = 0;
    DB_STATE &state() { return state_; }

protected:
	DB_STATE state_;
};
