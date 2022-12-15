#pragma once

#include "pch.h"
#include "Player.h"

namespace dreamtea
{
	class EventHandler
	{
	public:
		virtual void on_right_click(Player* player);
	};
}
