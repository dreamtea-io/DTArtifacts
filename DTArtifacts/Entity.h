#pragma once

#include "NetworkInterface.h"
#include "Model.h"

namespace dreamtea
{
	class Entity : public EntityModel
	{
	protected:
		NetworkInterface* network_interface = NULL;

		Vector3 direction;
	public:
		Entity(NetworkInterface* network, EntityModel model) : EntityModel(model)
		{
			this->network_interface = network;
		}

		void set_velocity(Vector3 motion);

		Vector3& get_direction()
		{
			return this->direction;
		}

		void set_direction(Vector3 direction)
		{
			this->direction = direction;
		}
	};
}
