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

		std::cout << "sending packet: " << payload << std::endl;

		connection->send_string(payload);
	}

	std::optional<nlohmann::json> NetworkInterface::receive_packet(char (&buffer)[BUFFER_LENGTH])
	{
		int result = connection->receive_string(buffer, BUFFER_LENGTH);

		if (result > 0)
		{
			std::string str = buffer;
			nlohmann::json json_result = nlohmann::json::parse(str.substr(0, result));

			return { json_result };
		}
		else if (result == 0)
		{
			std::cout << "Connection closed" << std::endl;
		}
		else
		{
			std::cout << "Recv failed: " << WSAGetLastError() << std::endl;
		}

		return std::nullopt;
	}
}
