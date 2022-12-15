#include "pch.h"
#include "PacketHandler.h"

namespace dreamtea
{
	ServerPacket* PacketHandler::read(nlohmann::json& data)
	{
		if (data.contains("pk_id"))
		{
			auto packet_id = data["pk_id"].get<unsigned short>();

			if (!data.contains("content"))
			{
				return NULL;
			}

			auto packet = Packet::make_empty_one(packet_id);
			auto spk = dynamic_cast<ServerPacket*>(packet);

			if (spk != nullptr)
			{
				spk->payload = data.at("content");
				spk->decode();

				return spk;
			}
		}

		return NULL;
	}

	void PacketHandler::invoke(ServerPacket* server_pk)
	{
		switch (server_pk->get_id())
		{
		case Protocol::EVENT_PACKET:
			handleEvent(*dynamic_cast<EventPacket*>(server_pk));
			break;
		case Protocol::NEARBY_ENTITIES_RESPONSE:
			handleNearbyEntitiesResponse(*dynamic_cast<NearbyEntitiesResponsePacket*>(server_pk));
			break;
		}
	}

	void PacketHandler::handleEvent(EventPacket& packet)
	{
		player->set_direction(packet.direction);

		switch (packet.eventType)
		{
		case EventPacket::RIGHT_CLICK:
			event_handler->on_right_click(player);
			break;
		}
	}

	void PacketHandler::handleNearbyEntitiesResponse(NearbyEntitiesResponsePacket& packet)
	{
		for (auto& entity : packet.entities)
		{
			player->world->handle_nearby_entity(packet.request_id, entity);
		}
	}
}
