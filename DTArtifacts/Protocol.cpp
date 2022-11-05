#include "pch.h"
#include "Protocol.h"

namespace dreamtea
{
	void RightClickPacket::decode()
	{

	}

	void RightClickPacket::encode()
	{

	}

	void RightClickPacket::invoke(EventHandler *handler)
	{
		handler->on_right_click();
	}
}
