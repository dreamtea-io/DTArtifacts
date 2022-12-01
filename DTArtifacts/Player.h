#pragma once

#include "pch.h"
#include "NetworkInterface.h"
#include "World.h"

namespace dreamtea
{
	class Player
	{
	private:
		NetworkInterface* network_interface = NULL;
	public:
		World* world = NULL;

		Player(NetworkInterface* network)
		{
			this->network_interface = network;

			this->world = new World(network);
		}

		~Player()
		{
			delete world;
		}

		void fix_position();

		void reset_position();

		void send_message(std::string message);

		void set_velocity(Vector3 motion);
	};
}
