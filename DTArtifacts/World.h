#pragma once

#include "NetworkInterface.h"

namespace dreamtea
{
	class World
	{
		std::string playerId;

		NetworkInterface* network_interface = NULL;
	public:
		World(std::string playerId, NetworkInterface* network)
		{
			this->playerId = playerId;
			this->network_interface = network;
		}

		void set_block(int x, int y, int z, std::string block);
	};
}
