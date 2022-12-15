#include "pch.h"
#include "DTArtifacts.h"
#include "Config.h"

namespace dreamtea
{
	const char* DREAMTEA_IP = "dreamtea.io";
	const char* DTA_PORT = "7676";
	const short TICKRATE = 100;

	Config config;

	NetworkInterface network_interface;
	Scheduler scheduler(&network_interface);

	Player player(network_interface);

	PacketHandler packet_handler(player, NULL);

	std::thread network_thread(&NetworkInterface::run, &network_interface);

	void connect(const char* ip = DREAMTEA_IP, const char* port = DTA_PORT)
	{
		network_interface.connect(ip, port);
		network_thread.detach();
	}

	void disconnect()
	{
		network_interface.disconnect();
	}

	void register_artifact(unsigned short id, EventHandler* handler)
	{
		if (!network_interface.is_connected())
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

		packet_handler.event_handler = handler;

		RegisterArtifactPacket pk;
		pk.artifactId = id;
		pk.username = config.username;
		network_interface.send_packet(pk);
	}

	Scheduler& get_scheduler()
	{
		return scheduler;
	}

	void loop()
	{
		std::vector<ServerPacket*> result;

		do
		{
			auto start = std::chrono::high_resolution_clock().now();

			result = network_interface.read_packets();

			for (auto packet : result)
			{
				packet_handler.invoke(packet);
				delete packet;
			}

			scheduler.tick();

			auto end = std::chrono::high_resolution_clock().now();

			std::chrono::duration<float> duration = end - start;
			float time = (1.0f / TICKRATE) - duration.count();

			if (time > 0)
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(int(time * 1000)));
			}
		} while (true);
	}
}
