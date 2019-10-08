#pragma once
#include "stdafx.h"
#include <atomic>

//-------------------------------------------------------------------//
// 타입 정의
typedef UINT64					object_t;
typedef DWORD					oid_t;
typedef int32_t					packet_size_t;

typedef std::recursive_mutex	lock_t;

typedef std::string				str_t;
typedef std::wstring			wstr_t;

//-------------------------------------------------------------------//
// 크기 정의
#define SIZE_8				8
#define SIZE_64				64
#define SIZE_128			128
#define SIZE_256			256
#define SIZE_1024			1024
#define SIZE_4096			4096
#define SIZE_8192			8192

//-------------------------------------------------------------------//
#define DB_PARAM_SIZE		8192
#define SOCKET_BUF_SIZE		1024 * 10

//-------------------------------------------------------------------//
// 패킷을 type을 맞추기 위한 재정의 C# 기준
typedef unsigned char		Byte;
typedef char				Char;
typedef INT16				Int16;
typedef UINT16				UInt16;
typedef INT32				Int32;
typedef UINT32				UInt32;
typedef INT64				Int64;
typedef UINT64				UInt64;
typedef float				Float;

//for xml
typedef TiXmlDocument		xml_t;
typedef TiXmlElement		xmlNode_t;
typedef TiXmlHandle			xmlHandle_t;

// Clock
#define DAY_NONE		(BYTE) 0X00
#define DAY_SUNDAY		(BYTE) 0X01
#define DAY_MONDAY		(BYTE) 0X02
#define DAY_TUESDAY		(BYTE) 0X04
#define DAY_WEDNESDAY	(BYTE) 0X08
#define DAY_THURSDAY	(BYTE) 0X10
#define DAY_FRIDAY		(BYTE) 0X20
#define DAY_SATURDAY	(BYTE) 0X40
#define ALL_DAY_WEEK	(DAY_SUNDAY | DAY_MONDAY | DAY_TUESDAY | DAY_WEDNESDAY | DAY_THURSDAY | DAY_FRIDAY | DAY_SATURDAY)

enum DAY_WEEK : BYTE
{
	WEEK_SUNDAY,
	WEEK_MONDAY,
	WEEK_TUESDAY,
	WEEK_WEDNESDAY,
	WEEK_THURSDAY,
	WEEK_FRIDAY,
	WEEK_SATURDAY,
	DAY_MAX
};

