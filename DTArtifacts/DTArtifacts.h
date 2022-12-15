#pragma once

#include "pch.h"

#include "NetworkInterface.h"
#include "PacketHandler.h"
#include "EventHandler.h"
#include "Scheduler.h"

#define WIN32_LEAN_AND_MEAN

namespace dreamtea
{
	extern const char* DREAMTEA_IP;
	extern const char* DTA_PORT;
	extern Player player;

	void connect(const char* ip, const char* port);

	void register_artifact(unsigned short id, EventHandler* handler);

	Scheduler& get_scheduler();

	void loop();
}
