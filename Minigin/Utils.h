#pragma once

namespace dae
{
	enum class PickupType
	{
		Undefined,
		Candy,
		Pill
	};

	enum Direction
	{
		IDLE = 0,
		DOWN = 1,
		RIGHT = 2,
		LEFT = 3,
		UP = 4
	};

	//rectangle overlap detection
	inline bool isOverlapping(const Rect& r1, const Rect& r2)
	{
		if ((r1.x + r1.w) < r2.x ||
			(r2.x + r2.w) < r1.x)
			return false;
		if ((r1.y + r1.h) < r2.y ||
			(r2.y + r2.h) < r1.y)
			return false;
		return true;
	}
}

