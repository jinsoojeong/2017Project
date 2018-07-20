#pragma once
#include "stdafx.h"

class SessionMonitor : public WorkObject
{
public :
	SessionMonitor();
	void tick();
};

static SessionMonitor sessionMonitor;