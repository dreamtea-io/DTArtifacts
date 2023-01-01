#pragma once

#include "pch.h"

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

namespace dreamtea
{
	class Connection
	{
	private:
		SOCKET client = INVALID_SOCKET;
		bool isConnected = false;
	public:
		std::string ip;
		std::string port;

		void try_connect();

		bool is_connected();

		void send_string(std::string data);

		int receive_string(char* buffer, size_t size);

		void disconnect();
	};
}
