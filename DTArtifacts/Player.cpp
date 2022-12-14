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

	void Player::attack(Entity& entity, int damage)
	{
		EntityInteractionPacket pk;
		pk.entity_id = entity.id;
		pk.type = EntityInteractionPacket::DAMAGE;
		pk.data = damage;
		network_interface->send_packet(pk);
	}

	void Player::burn(Entity& entity, int ticks)
	{
		EntityInteractionPacket pk;
		pk.entity_id = entity.id;
		pk.type = EntityInteractionPacket::BURN;
		pk.data = ticks;
		network_interface->send_packet(pk);
	}
}
