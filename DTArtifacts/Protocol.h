#pragma once

#include "pch.h"

#include "EventHandler.h"

namespace dreamtea
{
	class Packet
	{
	protected:
		nlohmann::json payload;
	public:
		virtual void decode() = 0;

		virtual void encode() = 0;

		virtual void invoke(EventHandler *handler) = 0;
	};

	class RightClickPacket : public Packet
	{
		void decode();

		void encode();

		void invoke(EventHandler *handler);
	};
}
