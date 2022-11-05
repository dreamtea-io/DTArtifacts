#include "pch.h"
#include "DTArtifacts.h"

#define BUFFER_LENGTH 1024

namespace dreamtea
{
	const char* DREAMTEA_IP = "dreamtea.io";
	const char* DTA_PORT = "7676";

	Connection* connection = NULL;

	PacketHandler* packet_handler = new PacketHandler();
	EventHandler* event_handler = NULL;

	void connect(const char* ip = DREAMTEA_IP, const char* port = DTA_PORT)
	{
		connection = new Connection(ip, port);
		connection->try_connect();
	}

	void disconnect()
	{
		connection->disconnect();
	}

	void register_artifact(EventHandler* handler)
	{
		event_handler = handler;
	}

	void send_packet()
	{

	}

	void loop()
	{
		int result;
		char buffer[BUFFER_LENGTH];

		do
		{
			result = connection->receive_string(buffer, BUFFER_LENGTH);
			
			if (result > 0)
			{
				nlohmann::json json_result = result;

				packet_handler->read(json_result);
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
}
