#include "pch.h"
#include "Protocol.h"

namespace dreamtea
{
	Packet Packet::make_empty_one(unsigned short id)
	{
		switch (id)
		{
		case Protocol::REGISTER_ARTIFACT:
			return RegisterArtifactPacket();
		case Protocol::SEND_MESSAGE:
			return SendMessagePacket();
		case Protocol::RIGHT_CLICK_EVENT:
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
