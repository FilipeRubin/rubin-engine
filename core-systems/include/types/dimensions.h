#pragma once
#include <cstdint>

struct Dimensions
{
	int32_t width = 0;
	int32_t height = 0;

	inline Dimensions() noexcept :
		width(0), height(0)
	{
	}

	inline Dimensions(int32_t width, int32_t height) noexcept :
		width(width), height(height)
	{
	}
};
