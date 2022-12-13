#pragma once

#include "pch.h"
#include "Model.h"

namespace dreamtea
{
	interface Protocol
	{
		static const unsigned short REGISTER_ARTIFACT = 0;
		static const unsigned short MESSAGE = 1;
		static const unsigned short EVENT_PACKET = 2;
		static const unsigned short SET_BLOCK = 3;
		static const unsigned short POSITION = 4;
		static const unsigned short VELOCITY = 5;
		static const unsigned short ADD_PARTICLE = 6;
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

		virtual void invoke() = 0;
	};

	/* CLIENT PACKETS */

	class RegisterArtifactPacket : public ClientPacket
	{
	public:
		unsigned short get_id() { return Protocol::REGISTER_ARTIFACT; }

		unsigned short artifactId;
		std::string username;

		void encode();
	};

	class MessagePacket : public ClientPacket
	{
	public:
		unsigned short get_id() { return Protocol::MESSAGE; }

		std::string message;

		void encode();
	};

	class SetBlockPacket : public ClientPacket
	{
	public:
		unsigned short get_id() { return Protocol::SET_BLOCK; }

		Vector3 position;
		std::string block;

		void encode();
	};

	class PositionPacket : public ClientPacket
	{
	public:
		unsigned short get_id() { return Protocol::POSITION; }

		enum ActionType
		{
			FIX = 0x00,
			RESET = 0x01
		};

		ActionType action;
		bool reset;

		void encode();
	};

	class VelocityPacket : public ClientPacket
	{
	public:
		unsigned short get_id() { return Protocol::VELOCITY; }

		Vector3 motion;

		void encode();
	};

	class AddParticlePacket : public ClientPacket
	{
	public:
		unsigned short get_id() { return Protocol::ADD_PARTICLE; }

		Vector3 position;
		Particle type;
		std::optional<Color> color;

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
		Vector3 direction;

		void decode();

		void invoke();
	};
}
