#include "pch.h"
#include "DTArtifacts.h"

namespace dreamtea
{
	const char* DREAMTEA_IP = "dreamtea.io";
	const char* DTA_PORT = "7676";
	const short TICKRATE = 100;

	Config config;

	NetworkInterface network_interface;
	Scheduler scheduler(&network_interface);

	PacketHandler packet_handler(network_interface, NULL);

	std::thread network_thread(&NetworkInterface::run, &network_interface);

	void shutdown()
	{
		network_interface.stopped = true;

		std::string temp;
		std::cin >> temp;
		exit(1);
	}

	void connect(const char* ip = DREAMTEA_IP, const char* port = DTA_PORT)
	{
		network_interface.connect(ip, port);
		network_thread.detach();
	}

	void disconnect()
	{
		network_interface.disconnect();
	}

	void register_artifact(unsigned int id, std::string secret, EventHandler* handler)
	{
		if (!network_interface.is_connected())
		{
			std::cout << "You are not connected to the DreamTea server!" << std::endl;
			shutdown();
		}

		packet_handler.event_handler = handler;

		RegisterArtifactPacket pk;
		pk.artifact_id = id;
		pk.secret = secret;
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
