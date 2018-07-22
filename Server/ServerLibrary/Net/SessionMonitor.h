#pragma once
#include "stdafx.h"

class SessionMonitor : public WorkObject
{
public :
	SessionMonitor();
	~SessionMonitor();
	void tick();
};