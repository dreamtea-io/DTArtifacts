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
		case Protocol::MESSAGE:
			return new MessagePacket();
		case Protocol::EVENT_PACKET:
			return new EventPacket();
		case Protocol::SET_BLOCK:
			return new SetBlockPacket();
		}

		throw;
	}

	/* CLIENT PACKETS */

	void RegisterArtifactPacket::encode()
	{
		payload["artifact_id"] = this->artifactId;
	}

	void MessagePacket::encode()
	{
		payload["player_id"] = this->playerId;
		payload["message"] = this->message;
	}

	void SetBlockPacket::encode()
	{
		payload["player_id"] = this->playerId;
		payload["position"]["x"] = this->position.x;
		payload["position"]["y"] = this->position.y;
		payload["position"]["z"] = this->position.z;
		payload["block"] = this->block;
	}

	/* SERVER PACKETS */

	void EventPacket::decode()
	{
		this->playerId = payload["player_id"].get<std::string>();

		switch (payload["event_type"].get<int>())
		{
		case 0:
			this->eventType = EventType::RIGHT_CLICK;
			break;
		default:
			throw std::invalid_argument("TODO");
		}
	}
}
