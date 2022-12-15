#pragma once

#include "pch.h"
#include "Connection.h"
#include "Protocol.h"

#define BUFFER_LENGTH 2048

namespace dreamtea
{
	class NetworkInterface
	{
	private:
		Connection* connection = NULL;

		// TCP can divide packets into several buffers
		// to connect them we will store incomplete data in this variable
		std::string split_buffer;

		std::mutex receive_mtx;
		std::vector<ServerPacket*> received_packets;

		bool read(char(&buffer)[BUFFER_LENGTH]);
	public:
		void connect(const char* ip, const char* port);

		bool is_connected();

		void disconnect();

		void send_packet(ClientPacket& pk);

		std::vector<ServerPacket*> read_packets();

		void run();
	};
}
