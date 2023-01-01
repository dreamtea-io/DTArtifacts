#include "pch.h"
#include "NetworkInterface.h"

#include "PacketHandler.h"

namespace dreamtea
{
	bool NetworkInterface::read(char(&buffer)[BUFFER_LENGTH])
	{
		int result = connection->receive_string(buffer, BUFFER_LENGTH);

		if (result > 0)
		{
			for (int i = 0; i < result; i++)
			{
				char c = buffer[i];

				if (c == '\0')
				{
					nlohmann::json json_result = nlohmann::json::parse(split_buffer);
					auto pk = PacketHandler::read(json_result);

					if (pk != NULL)
					{
						receive_mtx.lock();
						received_packets.push_back(pk);
						receive_mtx.unlock();
					}

					split_buffer.clear();
					continue;
				}

				split_buffer += c;
			}

			return true;
		}
		else if (result == 0)
		{
			std::cout << "Connection closed" << std::endl;
		}
		else
		{
			std::cout << "Recv failed: " << WSAGetLastError() << std::endl;
		}

		return false;
	}

	void NetworkInterface::connect(const char* ip, const char* port)
	{
		connection->ip = ip;
		connection->port = port;
		connection->try_connect();
	}

	bool NetworkInterface::is_connected()
	{
		return connection->is_connected();
	}

	void NetworkInterface::disconnect()
	{
		connection->disconnect();

		delete connection;
	}

	void NetworkInterface::send_packet(ClientPacket& pk)
	{
		pk.encode();

		nlohmann::json shell;
		shell["pk_id"] = pk.get_id();
		shell["content"] = pk.payload;

		auto payload = shell.dump();
		payload += '\0';

		std::cout << "sending packet: " << payload << std::endl;

		connection->send_string(payload);
	}

	std::vector<ServerPacket*> NetworkInterface::read_packets()
	{
		receive_mtx.lock();

		auto packets = received_packets;
		received_packets.clear();

		receive_mtx.unlock();

		return packets;
	}

	void NetworkInterface::run()
	{
		char buffer[BUFFER_LENGTH];

		while (!stopped)
		{
			if (connection->is_connected() && !read(buffer))
			{
				std::this_thread::sleep_for(std::chrono::seconds(5));
				connection->try_connect();
			}
		}
	}
}
