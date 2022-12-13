#include "pch.h"
#include "Player.h"
#include "Protocol.h"

namespace dreamtea
{
	void Player::fix_position()
	{
		PositionPacket pk;
		pk.action = PositionPacket::FIX;
		pk.reset = true;
		network_interface->send_packet(pk);
	}

	void Player::reset_position()
	{
		PositionPacket pk;
		pk.action = PositionPacket::RESET;
		pk.reset = true;
		network_interface->send_packet(pk);
	}

	void Player::send_message(std::string message)
	{
		MessagePacket pk;
		pk.message = message;
		network_interface->send_packet(pk);
	}

	void Player::set_velocity(Vector3 motion)
	{
		VelocityPacket pk;
		pk.motion = motion;
		network_interface->send_packet(pk);
	}
}
