#pragma once

#include "pch.h"

#include "EventHandler.h"

namespace dreamtea
{
	class Packet
	{
	public:
		nlohmann::json payload;

		enum TYPE
		{
			UNKNOWN = 0,
			CLIENT = 1,
			SERVER = 2
		};

		TYPE get_type();
	};

	class ClientPacket : public Packet
	{
	public:
		virtual void encode() = 0;

		TYPE get_type();
	};

	class ServerPacket : public Packet
	{
	public:
		virtual void decode() = 0;

		virtual void invoke(EventHandler* handler) = 0;

		TYPE get_type();
	};

	/* CLIENT PACKETS */

	class RegisterArtifactPacket : public ClientPacket
	{
	public:
		unsigned short artifactId;

		void encode();
	};

	class SendMessagePacket : public ClientPacket
	{
	public:
		unsigned int recipient;
		const char* message;

		void encode();
	};

	/* SERVER PACKETS */

	class RightClickEventPacket : public ServerPacket
	{
		void decode();

		void invoke(EventHandler *handler);
	};

	class PacketFactory
	{
	public:
		static const unsigned short REGISTER_ARTIFACT = 0;
		static const unsigned short SEND_MESSAGE = 1;
		static const unsigned short RIGHT_CLICK_EVENT = 2;

		static Packet make_empty_one(unsigned short id);
	};
}
