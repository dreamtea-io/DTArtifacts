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
		payload["username"] = this->username;
	}

	void MessagePacket::encode()
	{
		payload["message"] = this->message;
	}

	void SetBlockPacket::encode()
	{
		payload["position"]["x"] = this->position.x;
		payload["position"]["y"] = this->position.y;
		payload["position"]["z"] = this->position.z;
		payload["block"] = this->block;
	}

	void PositionPacket::encode()
	{
		payload["action"] = this->action;
		payload["reset"] = this->reset;
	}

	void VelocityPacket::encode()
	{
		payload["motion"]["x"] = this->motion.x;
		payload["motion"]["y"] = this->motion.y;
		payload["motion"]["z"] = this->motion.z;
	}

	void AddParticlePacket::encode()
	{
		payload["position"]["x"] = this->position.x;
		payload["position"]["y"] = this->position.y;
		payload["position"]["z"] = this->position.z;
		payload["type"] = this->type;
		
		if (this->color.has_value())
		{
			auto& color = this->color.value();

			payload["color"]["r"] = color.r;
			payload["color"]["g"] = color.g;
			payload["color"]["b"] = color.b;
		}
	}

	/* SERVER PACKETS */

	void EventPacket::decode()
	{
		this->direction = Vector3(
			payload["direction"]["x"].get<double>(),
			payload["direction"]["y"].get<double>(),
			payload["direction"]["z"].get<double>()
		);

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
