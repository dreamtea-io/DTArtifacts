#include "pch.h"
#include "DTArtifacts.h"

#define BUFFER_LENGTH 1024

namespace dreamtea
{
	const char* DREAMTEA_IP = "dreamtea.io";
	const char* DTA_PORT = "7676";

	SOCKET connection = INVALID_SOCKET;
	EventHandler* event_handler = NULL;

	void connect(const char* ip = DREAMTEA_IP, const char* port = DTA_PORT)
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

		i_result = getaddrinfo(ip, port, &hints, &result);

		for (ptr = result; ptr != NULL; ptr = ptr->ai_next)
		{
			connection = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
			if (connection == INVALID_SOCKET)
			{
				std::cout << "1" << std::endl;
				WSACleanup();
				return;
			}

			i_result = connect(connection, ptr->ai_addr, (int)ptr->ai_addrlen);
			if (i_result == SOCKET_ERROR)
			{
				std::cout << "2" << std::endl;
				closesocket(connection);
				connection = INVALID_SOCKET;
				return;
			}
			break;
		}

		freeaddrinfo(result);

		if (connection == INVALID_SOCKET)
		{
			std::cout << "3" << std::endl;
			WSACleanup();
			return;
		}
	}

	void disconnect()
	{
		closesocket(connection);
		WSACleanup();
	}

	void register_artifact(EventHandler* handler)
	{
		event_handler = handler;
	}

	void send_data(const char* data)
	{
		int result = send(connection, data, (int)strlen(data), 0);
		if (result == SOCKET_ERROR)
		{
			disconnect();
		}
	}

	void loop()
	{
		int result;
		char buffer[BUFFER_LENGTH];

		do
		{
			result = recv(connection, buffer, BUFFER_LENGTH, 0);
			if (result > 0)
			{
				std::cout << result << " : " << buffer << std::endl;
			}
			else if (result == 0)
			{
				std::cout << "Connection closed" << std::endl;
			}
			else
			{
				std::cout << "Recv failed: " << WSAGetLastError() << std::endl;
			}
		} while (result > 0);
	}

	void EventHandler::on_right_click()
	{
		// EMPTY
	}
}
