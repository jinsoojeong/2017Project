#include "stdafx.h"
#include "Server.h"

Server::Server(ContentsProcess *contentsProcess) : state_(SERVER_STOP)
{
	Log(L"# Initialze network base");
	
	contentsProcess_ = contentsProcess;

	xml_t config;
	if (!loadConfig(&config))
		return;

	initialize(&config);

	DB_MANAGER;
}

Server::~Server()
{
	shutdownServer();

	SetServerState(SERVER_STOP);
	SAFE_DELETE(contentsProcess_);

	Log(L"# End network base");
}

void Server::initialize(xml_t *config)
{
	//터미널 설정
	TERMINAL_MANAGER.run(this);

	//테스크 설정
	TASK_MANAGER;

	//서버 설정
	xmlNode_t *root = config->FirstChildElement("App")->FirstChildElement("Server");
	if (!root)
	{
		Log(L"@ not exist server setting");
		return;
	}
	
	xmlNode_t *elem = root->FirstChildElement("IP");

	char ip[16];
	strcpy_s(ip, elem->GetText());
	ip_ = ip;

	elem = root->FirstChildElement("Port");
	sscanf_s(elem->GetText(), "%d", &port_);

	elem = root->FirstChildElement("ThreadCount");
	sscanf_s(elem->GetText(), "%d", &worker_count_);

	SetServerState(SERVER_INITIALZE);
	Log(L"* IO worker thread count : %d", worker_count_);

	root = config->FirstChildElement("App");
	elem = root->FirstChildElement("Name");

	Log(L"### %S start!!! ###", elem->GetText());
}

bool Server::initialize()
{
	if (initializeModule() == false)
		return false;

	//static LowFragmentationHeap lfh;
	static WinSocket winsocket;
	static MiniDump minidump;
	static ProgramValidation programValidation;
	static SessionMonitor sessionMonitor;

	return true;
}

bool Server::initializeModule()
{
	DWORD total_heap_count = GetProcessHeaps(0, NULL);
	if (total_heap_count == 0 || total_heap_count > 8192)
	{
		//ReportLog(LOG_FATAL_FILE, L"GetProcessHeaps Failed - total:%d", total_heap_count);
		return false;
	}

	HANDLE heaps[8192] = { nullptr, };
	DWORD get_heap_count = GetProcessHeaps(total_heap_count, heaps);
	if (total_heap_count != get_heap_count)
	{
		//ReportLog(LOG_FATAL_FILE, L"GetProcessHeaps Failed - total:%d(%d)", total_heap_count, get_heap_count);
		return false;
	}

	HANDLE process_heap = GetProcessHeap();
	HANDLE crt_heap = reinterpret_cast<HANDLE>(_get_heap_handle());

	ULONG lfh_information = 2;
	DWORD total_lfh_count = 0;
	DWORD enable_lfh_count = 0;

	for (DWORD i = 0; i < total_heap_count; ++i)
	{
		HANDLE heap = heaps[i];
		ULONG heap_information = 0;
		if (!HeapQueryInformation(heap, HeapCompatibilityInformation, &heap_information, sizeof(heap_information), NULL))
		{
			//ReportLog(LOG_FATAL_FILE, L"HeapQueryInformation Failed - heap:%d", i);
			return false;
		}

		if (heap_information == HEAP_LFH)
		{
			++total_lfh_count;
			continue;
		}

		if (HeapSetInformation(heap, HeapCompatibilityInformation, &lfh_information, sizeof(lfh_information)))
		{
			++enable_lfh_count;
		}
		else
		{
			DWORD error_code = GetLastError();

			const wchar_t* heap_type = L"UNKNOWN";
			if (heap == process_heap)
				heap_type = L"PROCESS";
			else if (heap == crt_heap)
				heap_type = L"CRT";
			else
			{
				if (error_code == ERROR_INVALID_PARAMETER)
					continue;

				switch (heap_information)
				{
				case HEAP_STANDARD:
					heap_type = L"STANDARD";
					break;
				case HEAP_LAL:
					heap_type = L"LAL";
					break;
				}
			}

			Log(L"HeapSetInformation Failed - heap(%s):%d, error:%d", heap_type, i, error_code);
		}
	}

	total_lfh_count += enable_lfh_count;

	Log(L"Low-fragmentation Heap setting %d %d %d \n", total_heap_count, total_lfh_count, enable_lfh_count);

	return true;
}

bool Server::run()
{
	if (contentsProcess_->Run() == false)
		return false;

	return true;
}