#pragma once

#include "pch.h"

#include "Protocol.h"
#include "EventHandler.h"

namespace dreamtea
{
	class PacketHandler
	{
		NetworkInterface* network_interface = NULL;
	public:
		EventHandler* event_handler = NULL;

		PacketHandler(NetworkInterface& network, EventHandler* event_handler)
		{
			this->network_interface = &network;
			this->event_handler = event_handler;
		}

		static ServerPacket* read(nlohmann::json& data);

		void invoke(ServerPacket* server_pk);

		void handleEvent(std::shared_ptr<Player>& player, EventPacket& packet);

		void handleEntityResponse(std::shared_ptr<Player>& player, EntityResponsePacket& packet);
	};
}
