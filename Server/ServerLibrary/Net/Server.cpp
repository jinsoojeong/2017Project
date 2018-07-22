#include "stdafx.h"
#include "Server.h"

Server::Server(ContentsProcess *contentsProcess)
{
	Log(L"# Initialze network base");
	
	contentsProcess_ = contentsProcess;
	status_ = SERVER_STOP;

	xml_t config;
	if (!loadConfig(&config))
		return;

	initialize(&config);

	DB_MANAGER;
}

Server::~Server()
{
	shutdownServer();

	status_ = SERVER_STOP;
	SAFE_DELETE(contentsProcess_);

	Log(L"# End network base");
}

void Server::initialize(xml_t *config)
{
	//�͹̳� ����
	TERMINAL_MANAGER.run(this);

	//�׽�ũ ����
	TASK_MANAGER;

	//���� ����
	xmlNode_t *root = config->FirstChildElement("App")->FirstChildElement("Server");
	if (!root)
	{
		Log(L"@ not exist server setting");
		return;
	}
	
	xmlNode_t *elem = root->FirstChildElement("IP");
	strcpy_s(ip_, elem->GetText());

	elem = root->FirstChildElement("Port");
	sscanf_s(elem->GetText(), "%d", &port_);

	elem = root->FirstChildElement("ThreadCount");
	sscanf_s(elem->GetText(), "%d", &workerThreadCount_);

	status_ = SERVER_INITIALZE;
	Log(L"* IO worker thread count : %d", workerThreadCount_);

	root = config->FirstChildElement("App");
	elem = root->FirstChildElement("Name");

	Log(L"### %S start!!! ###", elem->GetText());
}

void Server::initialize()
{
	static LowFragmentationHeap lfh;
	static WinSocket winsocket;
	static MiniDump minidump;
	static ProgramValidation programValidation;
	static SessionMonitor sessionMonitor;
}

bool Server::run()
{
	if (contentsProcess_->Run() == false)
		return false;

	return true;
}

SERVER_STATUS &Server::status()
{
	return status_;
}

void Server::putPackage(Package *package)
{
	contentsProcess_->putPackage(package);
}