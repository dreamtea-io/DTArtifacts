#include "pch.h"
#include "Scheduler.h"

namespace dreamtea
{
	void Scheduler::run_task(int ticks, int repeat)
	{
		TimerPacket pk;
		pk.action = TimerPacket::START;
		pk.ticks = ticks;
		pk.repeat = repeat;
		network_interface->send_packet(pk);
	}

	void Scheduler::stop_task()
	{
		TimerPacket pk;
		pk.action = TimerPacket::STOP;
		network_interface->send_packet(pk);
	}
}
