#pragma once

#include "pch.h"
#include <fstream>

namespace dreamtea
{
	static const char* CONFIG_NAME = "config.json";

	struct Config
	{
		std::string username;

		Config() {}

		Config(std::string username)
		{
			this->username = username;
		}

		static void from_json(const nlohmann::json& json, Config& config)
		{
			json.at("username").get_to(config.username);
		}

		static Config load()
		{
			std::ifstream stream(CONFIG_NAME);
			nlohmann::json json;
			Config config("null");

			if (!stream.is_open())
			{
				json["username"] = config.username;

				std::ofstream write(CONFIG_NAME);
				write << json.dump(4).c_str();
				write.close();

				return config;
			}

			stream >> json;
			from_json(json, config);

			return config;
		}
	};
}
