#include "pch.h"
#include "Protocol.h"
#include "PacketPreprocessor.h"

namespace dreamtea
{
	void EventPacket::invoke()
	{
		auto handler = PacketPreprocessor::retrieve_event_handler();
		auto player = PacketPreprocessor::retrieve_player();
		player->set_direction(this->direction);

		switch (this->eventType)
		{
		case RIGHT_CLICK:
			handler->on_right_click(player);
			break;
		case TIMER:
			handler->on_timer(player);
			break;
		}

		//delete player;
	}

	void NearbyEntitiesResponsePacket::invoke()
	{
		auto player = PacketPreprocessor::retrieve_player();
		
		for (auto& entity : this->entities)
		{
			player->world->handle_nearby_entity(this->request_id, entity);
		}
	}
}
