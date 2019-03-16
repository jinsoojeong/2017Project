#pragma once
#include "stdafx.h"
// 유저 세션 구조체
// PC 온라인 게임 기준으로 작성하여서, 모바일 환경시 수정이 필요함.

struct SOCKET_DATA 
{
	SOCKET				socket_;
	SOCKADDR_IN			addrInfo_;
};

enum 
{
	SESSION_TYPE_TERMINAL,
	SESSION_TYPE_CLIENT,
};

class Session
{
public:
    Session(UINT64 id);
    virtual ~Session();

	virtual bool onAccept(SOCKET socket, SOCKADDR_IN addrInfo);

	virtual void onSend(size_t transferSize) = 0;
	virtual void sendPacket(Packet *packet) = 0;
	
	virtual Package* onRecv(size_t transferSize) = 0;
	virtual void recvStandBy() {};

    virtual void onClose(bool force = false);

	SOCKET& socket();
    wstr_t clientAddress();

	UINT64 GetID() const { return id_; }

	BYTE GetType() { return type_; }
	void SetType(BYTE type) { type_ = type; };

	std::time_t heartBeat();
	void updateHeartBeat();

protected:
	bool setSocketOpt();
	SOCKET_DATA socket_data_;

private:
	UINT64 id_;
	BYTE type_;
	std::time_t last_heart_beat_;
};
