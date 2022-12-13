#pragma once

#include "pch.h"
#include "NetworkInterface.h"
#include "World.h"

namespace dreamtea
{
	class Player
	{
		NetworkInterface* network_interface = NULL;

		Vector3 direction;
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

		Vector3& get_direction()
		{
			return this->direction;
		}

		void set_direction(Vector3 direction)
		{
			this->direction = direction;
		}

		void fix_position();

		void reset_position();

		void send_message(std::string message);

		void set_velocity(Vector3 motion);

		void attack(Entity& entity, int damage);

		void burn(Entity& entity, int ticks);
	};
}
