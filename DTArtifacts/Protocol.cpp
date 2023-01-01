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
		case Protocol::NEARBY_ENTITIES:
			return new NearbyEntitiesPacket();
		case Protocol::ENTITY_RESPONSE:
			return new EntityResponsePacket();
		case Protocol::ENTITY_INTERACTION:
			return new EntityInteractionPacket();
		}

		throw;
	}

	/* CLIENT PACKETS */

	void RegisterArtifactPacket::encode()
	{
		payload["artifact_id"] = this->artifact_id;
		payload["secret"] = this->secret;
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
		if (this->entity_id.has_value())
		{
			payload["entity_id"] = this->entity_id.value();
		}
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

	void NearbyEntitiesPacket::encode()
	{
		payload["request_id"] = this->request_id;
		payload["position"]["x"] = this->position.x;
		payload["position"]["y"] = this->position.y;
		payload["position"]["z"] = this->position.z;
		payload["radius"] = this->radius;
	}

	void EntityInteractionPacket::encode()
	{
		payload["entity_id"] = this->entity_id;
		payload["type"] = this->type;
		payload["data"] = this->data;
	}

	void SpawnEntityPacket::encode()
	{
		payload["request_id"] = this->request_id;
		payload["position"]["x"] = this->position.x;
		payload["position"]["y"] = this->position.y;
		payload["position"]["z"] = this->position.z;
		payload["type"] = this->type;

		if (this->motion.has_value()) {
			payload["motion"]["x"] = this->motion.value().x;
			payload["motion"]["y"] = this->motion.value().y;
			payload["motion"]["z"] = this->motion.value().z;
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

	void EntityResponsePacket::decode()
	{
		this->request_id = payload["request_id"].get<unsigned long long>();
		
		for (auto& entry : payload["entities"])
		{
			auto& position = entry["position"];

			this->entities.push_back(EntityModel(
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
