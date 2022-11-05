#include "pch.h"
#include "PacketHandler.h"

namespace dreamtea
{
	void PacketHandler::read(nlohmann::json &data)
	{
		int packet_id = -1;

		if (data.contains("pk_id"))
		{
			packet_id = data["pk_id"].get<int>();

			if (!data.contains("content"))
			{
				return;
			}


		}

		//IGNORE
	}

	void PacketHandler::handle(int pk, nlohmann::json content)
	{
		switch (pk)
		{
		case 0:

			break;
		}
	}
}
