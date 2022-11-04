#include "pch.h"
#include "framework.h"

#define BUFFER_LENGTH 1024

void connect(const char* ip, const char* port)
{
	WSADATA wsa_data;
	SOCKET connection = INVALID_SOCKET;
	struct addrinfo 
		*result = NULL,
		*ptr = NULL,
		hints;

	WSAStartup(MAKEWORD(2, 2), &wsa_data);

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	int i_result = getaddrinfo(ip, port, &hints, &result);

	for (ptr = result; ptr != NULL; ptr = ptr->ai_next)
	{
		connection = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
		if (connection == INVALID_SOCKET)
		{
			std::cout << "1" << std::endl;
			WSACleanup();
			return;
		}

		i_result = connect(connection, ptr->ai_addr, (int) ptr->ai_addrlen);
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

	const char* data = "Hello, bae :)";

	i_result = send(connection, data, (int) strlen(data), 0);
	if (i_result == SOCKET_ERROR)
	{
		std::cout << "4" << std::endl;
		closesocket(connection);
		WSACleanup();
	}

	char buffer[BUFFER_LENGTH];

	do
	{
		i_result = recv(connection, buffer, BUFFER_LENGTH, 0);
		if (i_result > 0)
		{
			std::cout << i_result << " : " << buffer << std::endl;
		}
		else if (i_result == 0)
		{
			std::cout << "Connection closed" << std::endl;
		}
		else
		{
			std::cout << "Recv failed: " << WSAGetLastError() << std::endl;
		}
	} while (i_result > 0);

	closesocket(connection);
	WSACleanup();
}
