#pragma once

struct Point2D
{
	int x = 0;
	int y = 0;

	inline Point2D() noexcept :
		x(0), y(0)
	{}

	inline Point2D(int x, int y) noexcept :
		x(x), y(y)
	{}
};
