#pragma once
#include <types/dimensions.h>

struct Vector2
{
	float x;
	float y;

	inline constexpr Vector2() noexcept :
		x(0.0f), y(0.0f)
	{}

	inline constexpr Vector2(float x, float y) noexcept :
		x(x), y(y)
	{}

	explicit inline constexpr Vector2(const Dimensions& dimensions) noexcept :
		x(static_cast<float>(dimensions.width)), y(static_cast<float>(dimensions.height))
	{
	}

	inline constexpr Vector2 operator+(const Vector2& other) const noexcept
	{
		return Vector2(x + other.x, y + other.y);
	}

	inline constexpr Vector2 operator+(const float& value) const noexcept
	{
		return Vector2(x + value, y + value);
	}

	inline constexpr Vector2 operator-(const Vector2& other) const noexcept
	{
		return Vector2(x - other.x, y - other.y);
	}

	inline constexpr Vector2 operator-(const float& value) const noexcept
	{
		return Vector2(x - value, y - value);
	}

	inline constexpr Vector2 operator*(const Vector2& other) const noexcept
	{
		return Vector2(x * other.x, y * other.y);
	}

	inline constexpr Vector2 operator*(const float& value) const noexcept
	{
		return Vector2(x * value, y * value);
	}

	inline constexpr Vector2 operator/(const Vector2& other) const noexcept
	{
		return Vector2(x / other.x, y / other.y);
	}

	inline constexpr Vector2 operator/(const float& value) const noexcept
	{
		return Vector2(x / value, y / value);
	}

	inline constexpr Vector2& operator+=(const Vector2& other) noexcept
	{
		x += other.x;
		y += other.y;
		return *this;
	}

	inline constexpr Vector2& operator-=(const Vector2& other) noexcept
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}

	inline constexpr Vector2 operator-() const noexcept
	{
		return Vector2(-x, -y);
	}
};
