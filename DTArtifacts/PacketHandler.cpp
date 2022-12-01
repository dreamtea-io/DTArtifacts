#include "pch.h"
#include "PacketHandler.h"

namespace dreamtea
{
	void PacketHandler::read(nlohmann::json &data)
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
			auto spk = dynamic_cast<ServerPacket*>(packet);

			if (spk != nullptr)
			{
				spk->payload = data.at("content");
				spk->decode();

				spk->invoke();
			}

			delete spk;
		}

		//IGNORE
	}
}
