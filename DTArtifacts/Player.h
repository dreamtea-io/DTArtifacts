#pragma once

#include "pch.h"
#include "NetworkInterface.h"
#include "World.h"

namespace dreamtea
{
	class Player
	{
	private:
		std::string playerId;

		NetworkInterface* network_interface = NULL;
	public:
		World* world = NULL;

		Player(std::string playerId, NetworkInterface* network)
		{
			this->playerId = playerId;
			this->network_interface = network;

			this->world = new World(playerId, network);
		}

		~Player()
		{
			delete world;
		}

		void send_message(std::string message);
	};
}
