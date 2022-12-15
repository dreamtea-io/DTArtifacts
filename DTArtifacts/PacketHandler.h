#pragma once

#include "pch.h"

#include "Protocol.h"
#include "EventHandler.h"

namespace dreamtea
{
	class PacketHandler
	{
		Player* player = NULL;
	public:
		EventHandler* event_handler = NULL;

		PacketHandler(Player& player, EventHandler* event_handler)
		{
			this->player = &player;
			this->event_handler = event_handler;
		}

		static ServerPacket* read(nlohmann::json& data);

		void invoke(ServerPacket* server_pk);

		void handleEvent(EventPacket& packet);

		void handleNearbyEntitiesResponse(NearbyEntitiesResponsePacket& packet);
	};
}
