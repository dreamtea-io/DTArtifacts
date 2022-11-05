#pragma once

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

namespace dreamtea
{
	class Connection
	{
	private:
		SOCKET client;

		const char* ip;
		const char* port;
	public:
		Connection(const char* ip, const char* port);

		void try_connect();

		void send_string(const char* data);

		int receive_string(char* buffer, size_t size);

		void disconnect();
	};
}
