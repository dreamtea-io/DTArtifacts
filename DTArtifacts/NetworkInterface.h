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

		std::string split_buffer;
	public:
		void connect(const char* ip, const char* port);

		bool is_connected();

		void disconnect();

		void send_packet(ClientPacket& pk);

		std::vector<nlohmann::json> receive_packets(char (&buffer)[BUFFER_LENGTH]);
	};
}
