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
		case Protocol::POSITION:
			return new PositionPacket();
		case Protocol::VELOCITY:
			return new VelocityPacket();
		case Protocol::ADD_PARTICLE:
			return new AddParticlePacket();
		case Protocol::TIMER:
			return new TimerPacket();
		case Protocol::NEARBY_ENTITIES:
			return new NearbyEntitiesPacket();
		case Protocol::NEARBY_ENTITIES_RESPONSE:
			return new NearbyEntitiesResponsePacket();
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
		
		if (this->options.has_value())
		{
			if (this->options->color.has_value())
			{
				auto& color = this->options->color.value();

				payload["options"]["color"]["r"] = color.r;
				payload["options"]["color"]["g"] = color.g;
				payload["options"]["color"]["b"] = color.b;
			}

			payload["options"]["fixed_position"] = this->options->fixed_position;
		}
	}

	void TimerPacket::encode()
	{
		payload["action"] = this->action;

		if (this->action == TimerPacket::START)
		{
			payload["ticks"] = this->ticks;
			payload["repeat"] = this->repeat;
		}
	}

	void NearbyEntitiesPacket::encode()
	{
		payload["request_id"] = this->request_id;
		payload["position"]["x"] = this->position.x;
		payload["position"]["y"] = this->position.y;
		payload["position"]["z"] = this->position.z;
		payload["radius"] = this->radius;
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
		case 1:
			this->eventType = EventType::TIMER;
			break;
		default:
			throw std::invalid_argument("TODO");
		}
	}

	void NearbyEntitiesResponsePacket::decode()
	{
		this->request_id = payload["request_id"].get<unsigned long long>();
		
		for (auto& entry : payload["entities"])
		{
			auto& position = entry["position"];

			this->entities.push_back(Entity(
				entry["id"].get<unsigned long long>(),
				entry["type"].get<EntityType>(),
				Vector3(
					position["x"].get<double>(),
					position["y"].get<double>(),
					position["z"].get<double>()
				)
			));
		}
	}
}
