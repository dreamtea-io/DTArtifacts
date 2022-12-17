#pragma once

namespace dreamtea
{
	struct Vector3
	{
		double x = 0;
		double y = 0;
		double z = 0;

		Vector3() {}

		Vector3(double x, double y, double z)
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}
	};

	struct Color
	{
		int r = 0;
		int g = 0;
		int b = 0;

		Color() {}

		Color(int r, int g, int b)
		{
			this->r = r;
			this->g = g;
			this->b = b;
		}
	};

	enum Particle
	{
		DUST = 0,
		CLOUD = 1,
		HEART = 2,
		VILLAGER_HAPPY = 3
	};

	struct ParticleOptions
	{
		std::optional<Color> color;
		bool fixed_position;

		ParticleOptions(Color color, bool fixed_position = false)
		{
			this->color = color;
			this->fixed_position = fixed_position;
		}

		ParticleOptions(bool fixed_position = false)
		{
			this->fixed_position = fixed_position;
		}
	};

	enum EntityType
	{
		OTHER = 0,
		PLAYER = 1
	};

	struct EntityModel
	{
		unsigned long long id;
		EntityType type;
		Vector3 position;

		EntityModel(unsigned long long id, EntityType type, Vector3 position)
		{
			this->id = id;
			this->type = type;
			this->position = position;
		}
	};

	NLOHMANN_JSON_SERIALIZE_ENUM(EntityType, {
		{OTHER, 0},
		{PLAYER, 1}
	})
}
