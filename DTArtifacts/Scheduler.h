#pragma once

#include "NetworkInterface.h"

namespace dreamtea
{
	class Scheduler
	{
	private:
		NetworkInterface* network_interface = NULL;
	public:
		Scheduler(NetworkInterface* network)
		{
			this->network_interface = network;
		}

		void run_task(int ticks, int repeat = 1);
		
		void stop_task();
	};
}
