#include "pch.h"
#include "Connection.h"

namespace dreamtea
{
	Connection::Connection(const char* ip, const char* port) : client{INVALID_SOCKET}
	{
		this->ip = ip;
		this->port = port;
	}

	void Connection::try_connect()
	{
		WSADATA wsa_data;

		struct addrinfo
			* result = NULL,
			* ptr = NULL,
			hints;

		int i_result = WSAStartup(MAKEWORD(2, 2), &wsa_data);
		if (i_result != 0)
		{
			return;
		}

		ZeroMemory(&hints, sizeof(hints));
		hints.ai_family = AF_UNSPEC;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;

		i_result = getaddrinfo(this->ip, this->port, &hints, &result);

		for (ptr = result; ptr != NULL; ptr = ptr->ai_next)
		{
			this->client = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
			if (this->client == INVALID_SOCKET)
			{
				std::cout << "1" << std::endl;
				WSACleanup();
				return;
			}

			i_result = connect(this->client, ptr->ai_addr, (int)ptr->ai_addrlen);
			if (i_result == SOCKET_ERROR)
			{
				std::cout << "2" << std::endl;
				closesocket(this->client);
				this->client = INVALID_SOCKET;
				return;
			}
			break;
		}

		freeaddrinfo(result);

		if (this->client == INVALID_SOCKET)
		{
			std::cout << "3" << std::endl;
			WSACleanup();
			return;
		}

		this->isConnected = true;
	}

	bool Connection::is_connected()
	{
		return this->isConnected;
	}

	void Connection::send_string(const char* data)
	{
		int result = send(this->client, data, (int) strlen(data), 0);
		if (result == SOCKET_ERROR)
		{
			disconnect();
		}
	}

	int Connection::receive_string(char *buffer, size_t size)
	{
		return recv(this->client, buffer, size, (size_t)0);
	}

	void Connection::disconnect()
	{
		this->isConnected = false;
		closesocket(this->client);
		WSACleanup();
	}
}
