#include "pch.h"
#include "Protocol.h"

namespace dreamtea
{
	Packet* Packet::make_empty_one(unsigned short id)
	{
		switch (id)
		{
		case Protocol::REGISTER_ARTIFACT:
			return new RegisterArtifactPacket();
		case Protocol::SEND_MESSAGE:
			return new SendMessagePacket();
		case Protocol::EVENT_PACKET:
			return new EventPacket();
		}

		throw;
	}

	/* CLIENT PACKETS */

	void RegisterArtifactPacket::encode()
	{
		payload["artifact_id"] = this->artifactId;
	}

	void SendMessagePacket::encode()
	{
		payload["recipient"] = this->recipient;
		payload["message"] = this->message;
	}

	/* SERVER PACKETS */

	void EventPacket::decode()
	{
		switch (payload["eventType"].get<int>())
		{
		case 0:
			this->eventType = EventType::RIGHT_CLICK;
			break;
		default:
			throw std::invalid_argument("TODO");
		}
	}

	void EventPacket::invoke(EventHandler *handler)
	{
		switch (this->eventType)
		{
		case RIGHT_CLICK:
			handler->on_right_click();
			break;
		}
	}
}
