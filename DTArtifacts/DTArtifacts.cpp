#include "pch.h"
#include "DTArtifacts.h"

#define BUFFER_LENGTH 2048

namespace dreamtea
{
	const char* DREAMTEA_IP = "dreamtea.io";
	const char* DTA_PORT = "7676";

	Connection* connection = NULL;

	PacketHandler* packet_handler = NULL;
	EventHandler* event_handler = NULL;

	void connect(const char* ip = DREAMTEA_IP, const char* port = DTA_PORT)
	{
		packet_handler = new PacketHandler();

		connection = new Connection(ip, port);
		connection->try_connect();
	}

	void disconnect()
	{
		delete packet_handler;
		delete event_handler;

		connection->disconnect();
	}

	void register_artifact(unsigned short id, EventHandler* handler)
	{
		if (!connection->is_connected())
		{
			std::cout << "You are not connected to the Spigot server!" << std::endl;
			return;
		}

		event_handler = handler;

		RegisterArtifactPacket pk;
		pk.artifactId = id;
		send_packet(pk);
	}

	void send_packet(ClientPacket &pk)
	{
		pk.encode();
		const char* payload = pk.payload.dump().c_str();
		
		connection->send_string(payload);

		delete[] payload;
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

				packet_handler->read(event_handler, json_result);
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
