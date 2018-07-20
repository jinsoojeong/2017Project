#pragma once
#include "stdafx.h"

TerminalSession::TerminalSession(DWORD id) : Session(id)
{
}

bool TerminalSession::connectTo(char *ip, int port)
{
	socket_data_.socket_ = ::socket(AF_INET, SOCK_STREAM, 0);
	if (socket_data_.socket_ == INVALID_SOCKET) {
		Log(L"! terminal socket fail");
		return false;
	}
	ZeroMemory(&socket_data_.addrInfo_, sizeof(socket_data_.addrInfo_));
	socket_data_.addrInfo_.sin_family = AF_INET;
	socket_data_.addrInfo_.sin_port = htons(port);
	inet_pton(AF_INET, ip, &(socket_data_.addrInfo_.sin_addr));
	
	this->setSocketOpt();

	int ret = ::connect(socket_data_.socket_, (sockaddr *)&socket_data_.addrInfo_, sizeof(socket_data_.addrInfo_));
	if (ret == SOCKET_ERROR) {
		Log(L"! terminal socket connect fail");
		return false;
	}
	return true;
}

void TerminalSession::onSend(size_t transferSize)
{
	//Noting
}

void TerminalSession::sendPacket(Packet *packet)
{
	Stream stream;
	packet->encode(stream);

	packet_size_t offset = 0;
	array<char, SOCKET_BUF_SIZE> buffer;
	const size_t packetHeaderSize = sizeof(packet_size_t);

	//									 head size  + real data size
	packet_size_t packetLen[1] = { (packet_size_t)packetHeaderSize + (packet_size_t)stream.size(), };
	// insert packet len
	memcpy_s(buffer.data() + offset, buffer.max_size(), (void *)packetLen, packetHeaderSize);
	offset += packetHeaderSize;

	// packet obfuscation
	PacketObfuscation::GetSingleton().encodingHeader((Byte*)buffer.data(), packetHeaderSize);
	PacketObfuscation::GetSingleton().encodingData((Byte*)stream.data(), stream.size());

	// insert packet data
	memcpy_s(buffer.data() + offset, buffer.max_size(), stream.data(), packetLen[0]);
	offset += (packet_size_t)stream.size();

	::send(socket_data_.socket_, buffer.data(), offset, 0);
}

Package* TerminalSession::onRecv(size_t transferSize)
{
	array<Byte, SOCKET_BUF_SIZE> rowData;
	int ret = ::recv(socket_data_.socket_, (char *)rowData.data(), (int)rowData.size(), 0);
	if (ret <= 0) {
		return nullptr;
	}

	//패킷 길이 가지고 오기      
	packet_size_t offset = 0;
	packet_size_t packetLen[1] = { 0, };

	memcpy_s((void *)packetLen, sizeof(packetLen), (void *)rowData.data(), sizeof(packetLen));
	PacketObfuscation::GetSingleton().decodingHeader((Byte*)packetLen, sizeof(packetLen));

	while (ret < (int)packetLen[0]) {
		int len = ret;
		ret += ::recv(socket_data_.socket_, (char *)rowData.data() + len, (int)rowData.size() - len, 0);
	}

	offset += sizeof(packetLen);
	PacketObfuscation::GetSingleton().decodingData((Byte*)rowData.data() + offset, packetLen[0] - offset);

	//서버간 패킷 처리
	Packet *packet = PacketAnalyzer::GetSingleton().analyzer((char *)rowData.data() + offset, packetLen[0]);
	if (packet == nullptr) {
		return nullptr;
	}

	Package *package = new Package(this, packet);
	return package;
}
