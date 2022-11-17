#pragma once

#include "pch.h"

#include "EventHandler.h"

namespace dreamtea
{
	interface Protocol
	{
		static const unsigned short REGISTER_ARTIFACT = 0;
		static const unsigned short SEND_MESSAGE = 1;
		static const unsigned short EVENT_PACKET = 2;
	};

	class Packet
	{
	public:
		nlohmann::json payload;

		virtual unsigned short get_id() { return -1; }

		static Packet* make_empty_one(unsigned short id);
	};

	class ClientPacket : public Packet
	{
	public:
		virtual void encode() = 0;
	};

	class ServerPacket : public Packet
	{
	public:
		virtual void decode() = 0;

		virtual void invoke(EventHandler* handler) = 0;
	};

	/* CLIENT PACKETS */

	class RegisterArtifactPacket : public ClientPacket
	{
	public:
		unsigned short get_id() { return Protocol::REGISTER_ARTIFACT; }

		unsigned short artifactId;

		void encode();
	};

	class SendMessagePacket : public ClientPacket
	{
	public:
		unsigned short get_id() { return Protocol::SEND_MESSAGE; }

		unsigned int recipient;
		const char* message;

		void encode();
	};

	/* SERVER PACKETS */

	class EventPacket : public ServerPacket
	{
	public:
		unsigned short get_id() { return Protocol::EVENT_PACKET; }

		enum EventType
		{
			RIGHT_CLICK = 0x00
		};

		EventType eventType;

		void decode();

		void invoke(EventHandler *handler);
	};
}
