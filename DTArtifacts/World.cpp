#include "pch.h"
#include "World.h"
#include "Protocol.h"

namespace dreamtea
{
	void World::set_block(int x, int y, int z, std::string block)
	{
		auto pk = SetBlockPacket();
		pk.position = Vector3(x, y, z);
		pk.block = block;
		network_interface->send_packet(pk);
	}
}
