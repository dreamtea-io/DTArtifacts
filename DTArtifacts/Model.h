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
}
