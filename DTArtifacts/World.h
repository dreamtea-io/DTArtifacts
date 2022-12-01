#pragma once

#include "NetworkInterface.h"

namespace dreamtea
{
	class World
	{
		NetworkInterface* network_interface = NULL;
	public:
		World(NetworkInterface* network)
		{
			this->network_interface = network;
		}

		void set_block(int x, int y, int z, std::string block);
	};
}
