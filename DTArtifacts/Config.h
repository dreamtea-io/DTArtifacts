#pragma once

#include "pch.h"
#include <fstream>

namespace dreamtea
{
	static const char* CONFIG_NAME = "config.json";

	struct Config
	{
		nlohmann::json raw_data;

		Config() {}

		static Config load()
		{
			return load([](nlohmann::json& json)
			{
				json["id"] = -1;
				json["secret"] = "PASTE SECRET HERE";
			});
		}

		static Config load(std::function<void(nlohmann::json& json)> defaults)
		{
			std::ifstream stream(CONFIG_NAME);
			nlohmann::json json;
			Config config;

			if (!stream.is_open())
			{
				defaults(json);

				std::ofstream write(CONFIG_NAME);
				write << json.dump(4).c_str();
				write.close();

				return config;
			}

			stream >> json;
			config.raw_data = json;

			return config;
		}

		template<typename T>
		T get(std::string key)
		{
			return this->raw_data[key].get<T>();
		}
	};
}
