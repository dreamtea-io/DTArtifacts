#pragma once

#include "pch.h"

#include "NetworkInterface.h"
#include "PacketHandler.h"
#include "EventHandler.h"
#include "PacketPreprocessor.h"

#define WIN32_LEAN_AND_MEAN

namespace dreamtea
{
	extern const char* DREAMTEA_IP;
	extern const char* DTA_PORT;

	void connect(const char* ip, const char* port);

	void register_artifact(unsigned short id, EventHandler* handler);

	void loop();
}
