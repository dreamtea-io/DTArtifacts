#pragma once

#include "pch.h"

#include "Protocol.h"
#include "EventHandler.h"
#include "NetworkInterface.h"

namespace dreamtea
{
	class PacketHandler
	{
	public:
		void read(EventHandler* event_handler, NetworkInterface* network_interface, nlohmann::json &data);
	};
}
