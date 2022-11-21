#pragma once

#include "NetworkInterface.h"
#include "EventHandler.h"
#include "Player.h"

namespace dreamtea
{
	class PacketPreprocessor
	{
		static NetworkInterface* network_interface;
		static EventHandler* event_handler;
	public:
		static void set_network_interface(NetworkInterface* network);
		static void set_event_handler(EventHandler* events);

		static Player* retrieve_player(std::string id);
		static EventHandler* retrieve_event_handler();
	};
}
