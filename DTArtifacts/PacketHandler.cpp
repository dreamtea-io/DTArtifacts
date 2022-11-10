#include "pch.h"
#include "PacketHandler.h"

namespace dreamtea
{
	void PacketHandler::read(EventHandler* event_handler, nlohmann::json &data)
	{
		unsigned short packet_id = -1;

		if (data.contains("pk_id"))
		{
			packet_id = data["pk_id"].get<unsigned short>();

			if (!data.contains("content"))
			{
				return;
			}

			auto packet = Packet::make_empty_one(packet_id);
			auto packet_ptr = &packet;

			if (packet.get_type() == Packet::SERVER)
			{
				auto spk = static_cast<ServerPacket*>(packet_ptr);
				spk->payload = data.at("content");
				spk->decode();

				spk->invoke(event_handler);

				delete spk;
			}

			delete packet_ptr;
		}

		//IGNORE
	}
}
