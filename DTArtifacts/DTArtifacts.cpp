#include "pch.h"
#include "DTArtifacts.h"

namespace dreamtea
{
	const char* DREAMTEA_IP = "dreamtea.io";
	const char* DTA_PORT = "7676";

	NetworkInterface* network_interface = NULL;
	PacketHandler* packet_handler = NULL;
	EventHandler* event_handler = NULL;

	void connect(const char* ip = DREAMTEA_IP, const char* port = DTA_PORT)
	{
		network_interface = new NetworkInterface();
		packet_handler = new PacketHandler();

		network_interface->connect(ip, port);

		PacketPreprocessor::set_network_interface(network_interface);
	}

	void disconnect()
	{
		network_interface->disconnect();

		delete packet_handler;
		delete event_handler;
		delete network_interface;
	}

	void register_artifact(unsigned short id, EventHandler* handler)
	{
		if (!network_interface->is_connected())
		{
			std::cout << "You are not connected to the DreamTea server!" << std::endl;
			return;
		}

		event_handler = handler;
		PacketPreprocessor::set_event_handler(handler);

		RegisterArtifactPacket pk;
		pk.artifactId = id;
		network_interface->send_packet(pk);
	}

	void loop()
	{
		char buffer[BUFFER_LENGTH];
		std::optional<nlohmann::json> result;

		do
		{
			result = network_interface->receive_packet(buffer);

			if (result)
			{
				packet_handler->read(event_handler, network_interface, *result);
			}
		} while (result != std::nullopt);
	}
}
