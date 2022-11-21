#pragma once

#include "pch.h"
#include "NetworkInterface.h"

namespace dreamtea
{
	class Player
	{
	private:
		std::string playerId;

		NetworkInterface* network_interface = NULL;
	public:
		Player(std::string playerId, NetworkInterface* network)
		{
			this->playerId = playerId;
			this->network_interface = network;
		}

		void send_message(std::string message);
	};
}
