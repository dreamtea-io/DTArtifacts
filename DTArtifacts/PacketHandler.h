#pragma once

#include "pch.h"

#include "Protocol.h"

namespace dreamtea
{
	class PacketHandler
	{
	public:
		void read(EventHandler* event_handler, nlohmann::json &data);
	};
}
