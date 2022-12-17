#pragma once

#include "NetworkInterface.h"
#include "Entity.h"

namespace dreamtea
{
	class World
	{
		NetworkInterface* network_interface = NULL;

		unsigned long long last_request_id = 0;
		std::unordered_map<unsigned long long, std::function<void(Entity)>> entity_callbacks;
	public:
		World(NetworkInterface* network)
		{
			this->network_interface = network;
		}

		void set_block(int x, int y, int z, std::string block);

		void add_particle(double x, double y, double z, Particle particle);

		void add_particle(double x, double y, double z, Particle particle, std::optional<ParticleOptions> options);

		void spawn_entity(double x, double y, double z, EntityType type);

		void get_nearby_entities(double x, double y, double z, double radius, std::function<void(Entity)> callback);

		void handle_entity_response(unsigned long long request_id, Entity entity);
	};
}
