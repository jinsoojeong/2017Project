#include "stdafx.h"
#include "SessionMonitor.h"

SessionMonitor::SessionMonitor() 
{
	static bool init = false;
	if (init) {
		return;
	}
	init = true;

	const int MONITOR_REPORTING_SEC = 1;
	TaskManager::GetSingleton().add(this, MONITOR_REPORTING_SEC, TICK_INFINTY);
}

void SessionMonitor::tick()
{
	//15초간 반응 없으면 끊기
	const int MAX_HEART_BEAT = 15 * 1000;
	auto list = SESSION_MANAGER.sessionList();
	tick_t now = CLOCK.systemTick();

	for (auto session : list) {
		if (session->type() != SESSION_TYPE_CLIENT) {
			continue;
		}

		tick_t lastTick = session->heartBeat();
		if (now - lastTick > MAX_HEART_BEAT) {
			Log(L"* [%s] Closing by heartBeat", session->clientAddress().c_str());
			session->onClose(true);
		}
	}
}