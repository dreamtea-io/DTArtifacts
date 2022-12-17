#pragma once

#include "pch.h"
#include "NetworkInterface.h"
#include "World.h"
#include "Entity.h"

namespace dreamtea
{
	class Player : public Entity
	{
	public:
		World* world = NULL;

		Player(NetworkInterface& network) : Entity(&network, EntityModel(-1, EntityType::PLAYER, Vector3()))
		{
			this->network_interface = &network;
			this->world = new World(&network);
		}

		~Player()
		{
			delete this->world;
		}

		void fix_position();

		void reset_position();

		void send_message(std::string message);

		void attack(Entity& entity, int damage);

		void burn(Entity& entity, int ticks);
	};
}
