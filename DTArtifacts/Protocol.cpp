#include "pch.h"
#include "Protocol.h"

namespace dreamtea
{
	Packet PacketFactory::make_empty_one(unsigned short id)
	{
		switch (id)
		{
		case REGISTER_ARTIFACT:
			return RegisterArtifactPacket();
		case SEND_MESSAGE:
			return SendMessagePacket();
		case RIGHT_CLICK_EVENT:
			return RightClickEventPacket();
		}

		throw;
	}

	Packet::TYPE Packet::get_type()
	{
		return Packet::UNKNOWN;
	}

	Packet::TYPE ClientPacket::get_type()
	{
		return Packet::CLIENT;
	}

	Packet::TYPE ServerPacket::get_type()
	{
		return Packet::SERVER;
	}

	/* CLIENT PACKETS */

	void RegisterArtifactPacket::encode()
	{
		payload["artifact_id"] = this->artifactId;
	}

	void SendMessagePacket::encode()
	{
		payload["recipient"] = this->recipient;
		payload["message"] = this->message;
	}

	/* SERVER PACKETS */

	void RightClickEventPacket::decode()
	{

	}

	void RightClickEventPacket::invoke(EventHandler *handler)
	{
		handler->on_right_click();
	}
}
