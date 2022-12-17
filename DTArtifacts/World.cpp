#include "pch.h"
#include "World.h"
#include "Protocol.h"

namespace dreamtea
{
	void World::set_block(int x, int y, int z, std::string block)
	{
		SetBlockPacket pk;
		pk.position = Vector3(x, y, z);
		pk.block = block;
		network_interface->send_packet(pk);
	}

	void World::add_particle(double x, double y, double z, Particle particle)
	{
		add_particle(x, y, z, particle, {});
	}

	void World::add_particle(double x, double y, double z, Particle particle, std::optional<ParticleOptions> options)
	{
		AddParticlePacket pk;
		pk.position = Vector3(x, y, z);
		pk.type = particle;
		pk.options = options;
		network_interface->send_packet(pk);
	}

	void World::spawn_entity(double x, double y, double z, EntityType type)
	{
		SpawnEntityPacket pk;
		pk.request_id = last_request_id++;
		pk.position = Vector3(x, y, z);
		pk.type = type;
		network_interface->send_packet(pk);
	}

	void World::get_nearby_entities(double x, double y, double z, double radius, std::function<void(Entity)> callback)
	{
		auto request_id = last_request_id++;

		entity_callbacks[request_id] = callback;

		NearbyEntitiesPacket pk;
		pk.request_id = request_id;
		pk.position = Vector3(x, y, z);
		pk.radius = radius;
		network_interface->send_packet(pk);
	}

	void World::handle_entity_response(unsigned long long request_id, Entity entity)
	{
		if (entity_callbacks.contains(request_id))
		{
			entity_callbacks[request_id](entity);
			entity_callbacks.erase(request_id);
		}
	}
}
