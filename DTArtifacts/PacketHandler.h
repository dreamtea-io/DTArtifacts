#pragma once

#include "pch.h"

#include "Protocol.h"

namespace dreamtea
{
	class PacketHandler
	{
	public:
		void read(nlohmann::json &data);

		void handle(int pk, nlohmann::json content);
	};
}
