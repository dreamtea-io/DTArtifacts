#pragma once

#include <unordered_map>
#include "NetworkInterface.h"

namespace dreamtea
{
	typedef std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds> TimePoint;
	typedef std::chrono::duration<long long, std::milli> Duration;
	typedef std::function<bool(int)> TaskRunnable;

	const static std::chrono::milliseconds TIME_ZERO(0);

	class Task
	{
		TimePoint delay;
		TimePoint last_repeat;
		Duration repeat_time;

		TaskRunnable runnable;

		int counter = 0;
	public:
		Task() : repeat_time(Duration(0)) {}

		Task(
			TaskRunnable callback,
			TimePoint delay_point,
			Duration repeat
		) : delay(delay_point), runnable(callback), repeat_time(repeat) {}

		bool tick(TimePoint current_time);
	};

	class Scheduler
	{
		NetworkInterface* network_interface = NULL;

		unsigned long long last_task_id = 0;
		std::unordered_map<unsigned long long, Task> tasks;
	public:
		Scheduler(NetworkInterface* network)
		{
			this->network_interface = network;
		}

		void tick();

		void run_task(TaskRunnable runnable, Duration repeat);

		void run_task(TaskRunnable runnable, Duration delay, Duration repeat);
	};
}
