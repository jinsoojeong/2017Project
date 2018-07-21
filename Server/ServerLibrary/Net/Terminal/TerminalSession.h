#pragma once
#include "stdafx.h"

class TerminalSession : public Session
{
public:
	TerminalSession(DWORD id);

	bool		connectTo(char *ip, int port);
	void		onSend(size_t transferSize);
	void		sendPacket(Packet *packet);

	Package*	onRecv(size_t transferSize);
};