#pragma once
#include <types/dimensions.h>
#include <cmath>

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

	constexpr bool operator==(const Vector2i& other) const noexcept = default;

	inline constexpr Vector2i operator+(Vector2i other) const noexcept
	{
		return Vector2i(x + other.x, y + other.y);
	}

	inline constexpr Vector2i operator+(int32_t value) const noexcept
	{
		return Vector2i(x + value, y + value);
	}

	inline constexpr Vector2i operator-(Vector2i other) const noexcept
	{
		return Vector2i(x - other.x, y - other.y);
	}

	inline constexpr Vector2i operator-(int32_t value) const noexcept
	{
		return Vector2i(x - value, y - value);
	}

	inline constexpr Vector2i operator*(Vector2i other) const noexcept
	{
		return Vector2i(x * other.x, y * other.y);
	}

	inline constexpr Vector2i operator*(int32_t value) const noexcept
	{
		return Vector2i(x * value, y * value);
	}

	inline constexpr Vector2i operator/(Vector2i other) const noexcept
	{
		return Vector2i(x / other.x, y / other.y);
	}

	inline constexpr Vector2i operator/(int32_t value) const noexcept
	{
		return Vector2i(x / value, y / value);
	}

	inline constexpr Vector2i operator-() const noexcept
	{
		return Vector2i(-x, -y);
	}

	inline constexpr Vector2i& operator+=(Vector2i other) noexcept
	{
		x += other.x;
		y += other.y;
		return *this;
	}

	inline constexpr Vector2i& operator+=(int32_t value) noexcept
	{
		x += value;
		y += value;
		return *this;
	}

	inline constexpr Vector2i& operator-=(Vector2i other) noexcept
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}

	inline constexpr Vector2i& operator-=(int32_t value) noexcept
	{
		x -= value;
		y -= value;
		return *this;
	}

	inline constexpr Vector2i& operator*=(Vector2i other) noexcept
	{
		x *= other.x;
		y *= other.y;
		return *this;
	}

	inline constexpr Vector2i& operator*=(int32_t value) noexcept
	{
		x *= value;
		y *= value;
		return *this;
	}

	inline constexpr Vector2i& operator/=(Vector2i other) noexcept
	{
		x /= other.x;
		y /= other.y;
		return *this;
	}

	inline constexpr Vector2i& operator/=(int32_t value) noexcept
	{
		x /= value;
		y /= value;
		return *this;
	}
};
