#include "pch.h"
#include "NetworkInterface.h"

namespace dreamtea
{
	void NetworkInterface::connect(const char* ip, const char* port)
	{
		connection = new Connection(ip, port);
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

	std::vector<nlohmann::json> NetworkInterface::receive_packets(char (&buffer)[BUFFER_LENGTH])
	{
		int result = connection->receive_string(buffer, BUFFER_LENGTH);
		std::vector<nlohmann::json> packets;

		if (result > 0)
		{
			for (int i = 0; i < result; i++)
			{
				char c = buffer[i];

				if (c == '\0')
				{
					nlohmann::json json_result = nlohmann::json::parse(split_buffer);
					packets.push_back(json_result);

					split_buffer.clear();
					continue;
				}

				split_buffer += c;
			}

			return packets;
		}
		else if (result == 0)
		{
			std::cout << "Connection closed" << std::endl;
		}
		else
		{
			std::cout << "Recv failed: " << WSAGetLastError() << std::endl;
		}

		return packets;
	}
}
