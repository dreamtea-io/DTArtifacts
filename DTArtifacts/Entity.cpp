#include "pch.h"
#include "Entity.h"

namespace dreamtea
{
	void Entity::set_velocity(Vector3 motion)
	{
		VelocityPacket pk;
		pk.motion = motion;
		network_interface->send_packet(pk);
	}
}
