#include "pch.h"
#include "Scheduler.h"

namespace dreamtea
{
	bool Task::tick(TimePoint current_time)
	{
		if (delay - current_time > TIME_ZERO) return true;

		if (current_time - last_repeat >= repeat_time)
		{
			if (!runnable(++counter)) return false;

			// For delayed tasks
			if (repeat_time <= TIME_ZERO)
			{
				return false;
			}
			last_repeat = current_time;
		}

		return true;
	}

	void Scheduler::run_task(TaskRunnable runnable, Duration repeat)
	{
		run_task(runnable, TIME_ZERO, repeat);
	}

	void Scheduler::run_task(TaskRunnable runnable, Duration delay, Duration repeat)
	{
		auto current_time = std::chrono::system_clock::now();
		TimePoint delayedTime = std::chrono::time_point_cast<TimePoint::duration>(current_time);
		delayedTime += delay;

		tasks[last_task_id++] = Task(runnable, delayedTime, repeat);
	}

	void Scheduler::tick()
	{
		auto current_time = std::chrono::time_point_cast<TimePoint::duration>(std::chrono::system_clock::now());
		std::set<unsigned long long> deleted;

		for (auto& entry : tasks)
		{
			auto& task = entry.second;

			if (!task.tick(current_time))
			{
				deleted.insert(entry.first);
			}
		}

		for (auto& index : deleted) tasks.erase(index);
	}
}
