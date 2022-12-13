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
		}

		delete player;
	}
}
