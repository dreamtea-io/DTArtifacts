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

	void World::add_particle(double x, double y, double z, Particle particle, std::optional<Color> color)
	{
		AddParticlePacket pk;
		pk.position = Vector3(x, y, z);
		pk.type = particle;
		pk.color = color;
		network_interface->send_packet(pk);
	}
}
