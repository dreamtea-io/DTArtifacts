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
	public:
		void connect(const char* ip, const char* port);

		bool is_connected();

		void disconnect();

		void send_packet(ClientPacket& pk);

		std::optional<nlohmann::json> receive_packet(char (&buffer)[BUFFER_LENGTH]);
	};
}
