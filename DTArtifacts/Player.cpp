#include "pch.h"
#include "Player.h"
#include "Protocol.h"

namespace dreamtea
{
	void Player::send_message(std::string message)
	{
		auto pk = MessagePacket();
		pk.playerId = this->playerId;
		pk.message = message;
		network_interface->send_packet(pk);
	}
}
