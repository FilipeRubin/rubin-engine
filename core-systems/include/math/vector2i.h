#pragma once
#include <types/dimensions.h>

struct Vector2i
{
	int32_t x;
	int32_t y;

	inline constexpr Vector2i() noexcept :
		x(0), y(0)
	{}

	inline constexpr Vector2i(int32_t x, int32_t y) noexcept :
		x(x), y(y)
	{}

	explicit inline constexpr Vector2i(const Dimensions& dimensions) noexcept :
		x(dimensions.width), y(dimensions.height)
	{}

	inline constexpr Vector2i operator+(const Vector2i& other) const noexcept
	{
		return Vector2i(x + other.x, y + other.y);
	}

	inline constexpr Vector2i operator+(const int32_t& value) const noexcept
	{
		return Vector2i(x + value, y + value);
	}

	inline constexpr Vector2i operator-(const Vector2i& other) const noexcept
	{
		return Vector2i(x - other.x, y - other.y);
	}

	inline constexpr Vector2i operator-(const int32_t& value) const noexcept
	{
		return Vector2i(x - value, y - value);
	}

	inline constexpr Vector2i operator*(const Vector2i& other) const noexcept
	{
		return Vector2i(x * other.x, y * other.y);
	}

	inline constexpr Vector2i operator*(const int32_t& value) const noexcept
	{
		return Vector2i(x * value, y * value);
	}

	inline constexpr Vector2i operator/(const Vector2i& other) const noexcept
	{
		return Vector2i(x / other.x, y / other.y);
	}

	inline constexpr Vector2i operator/(const int32_t& value) const noexcept
	{
		return Vector2i(x / value, y / value);
	}

	inline constexpr Vector2i& operator+=(const Vector2i& other) noexcept
	{
		x += other.x;
		y += other.y;
		return *this;
	}

	inline constexpr Vector2i& operator-=(const Vector2i& other) noexcept
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}

	inline constexpr Vector2i operator-() const noexcept
	{
		return Vector2i(-x, -y);
	}
};
