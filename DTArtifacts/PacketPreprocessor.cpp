#include "pch.h"
#include "PacketPreprocessor.h"

/*
* Created to reduce problems with recursive use of some classes
*/
namespace dreamtea
{
	NetworkInterface* PacketPreprocessor::network_interface = NULL;
	EventHandler* PacketPreprocessor::event_handler = NULL;

	void PacketPreprocessor::set_network_interface(NetworkInterface* network)
	{
		network_interface = network;
	}

	void PacketPreprocessor::set_event_handler(EventHandler* events)
	{
		event_handler = events;
	}

	Player* PacketPreprocessor::retrieve_player()
	{
		auto player = new Player(network_interface);

		return player;
	}

	EventHandler* PacketPreprocessor::retrieve_event_handler()
	{
		return event_handler;
	}
}
