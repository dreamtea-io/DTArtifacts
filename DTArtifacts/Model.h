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
		DUST = 0x00,
		CLOUD = 0x01,
		HEART = 0x02,
		VILLAGER_HAPPY = 0x03
	};
}
