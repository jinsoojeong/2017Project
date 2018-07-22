#include "stdafx.h"
#include "SessionMonitor.h"

SessionMonitor::SessionMonitor() 
{
	static bool init = false;

	if (init)
		return;

	init = true;

	TASK_MANAGER.add(this, 1, TICK_INFINTY);
}

SessionMonitor::~SessionMonitor()
{
}

void SessionMonitor::tick()
{
	//15�ʰ� ���� ������ ����
	const int MAX_HEART_BEAT = 15 * 1000;
	auto list = SESSION_MANAGER.sessionList();
	tick_t now = CLOCK.systemTick();

	for (auto session : list) 
	{
		if (session->GetType() != SESSION_TYPE_CLIENT)
			continue;

		tick_t lastTick = session->heartBeat();

		if (now - lastTick > MAX_HEART_BEAT) 
		{
			Log(L"* [%s] Closing by heartBeat", session->clientAddress().c_str());
			session->onClose(true);
		}
	}
}