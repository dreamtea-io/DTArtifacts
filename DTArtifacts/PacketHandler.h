#pragma once

#include "pch.h"

#include "Protocol.h"
#include "EventHandler.h"

namespace dreamtea
{
	class PacketHandler
	{
		Player* player = NULL;
		NetworkInterface* network_interface = NULL;
	public:
		EventHandler* event_handler = NULL;

		PacketHandler(Player& player, NetworkInterface& network, EventHandler* event_handler)
		{
			this->player = &player;
			this->network_interface = &network;
			this->event_handler = event_handler;
		}

		static ServerPacket* read(nlohmann::json& data);

		void invoke(ServerPacket* server_pk);

		void handleEvent(EventPacket& packet);

		void handleEntityResponse(EntityResponsePacket& packet);
	};
}
