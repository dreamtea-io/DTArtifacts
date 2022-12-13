#include "pch.h"
#include "DTArtifacts.h"
#include "Config.h"

namespace dreamtea
{
	const char* DREAMTEA_IP = "dreamtea.io";
	const char* DTA_PORT = "7676";

	Config config;

	NetworkInterface* network_interface = NULL;
	PacketHandler* packet_handler = NULL;
	EventHandler* event_handler = NULL;
	Scheduler* scheduler = NULL;

	void connect(const char* ip = DREAMTEA_IP, const char* port = DTA_PORT)
	{
		network_interface = new NetworkInterface();
		packet_handler = new PacketHandler();

		network_interface->connect(ip, port);

		scheduler = new Scheduler(network_interface);
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

		config = Config::load();
		if (config.username == "null")
		{
			std::cout << "Please type your Minecraft username to the config.json around your .exe file" << std::endl;
			return;
		}

		event_handler = handler;
		PacketPreprocessor::set_event_handler(handler);

		RegisterArtifactPacket pk;
		pk.artifactId = id;
		pk.username = config.username;
		network_interface->send_packet(pk);
	}

	Scheduler* get_scheduler()
	{
		return scheduler;
	}

	void loop()
	{
		char buffer[BUFFER_LENGTH];
		std::vector<nlohmann::json> result;

		do
		{
			result = network_interface->receive_packets(buffer);

			for (auto& packet : result)
			{
				packet_handler->read(packet);
			}
		} while (!result.empty());
	}
}
