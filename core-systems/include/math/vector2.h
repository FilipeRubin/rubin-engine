#pragma once
#include <types/dimensions.h>
#include <cmath>

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

	inline constexpr float Cross(Vector2 other) const noexcept
	{
		return x * other.y - y * other.x;
	}

	inline constexpr float Dot(Vector2 other) const noexcept
	{
		return x * other.x + y * other.y;
	}

	inline float Length() const noexcept
	{
		return std::sqrtf(LengthSquared());
	}

	inline constexpr float LengthSquared() const noexcept
	{
		return x * x + y * y;
	}

	inline Vector2 Normalized() const noexcept
	{
		const float l = Length();
		return l == 0.0f ? Vector2() : Vector2(
			x / l,
			y / l
		);
	}

	constexpr bool operator==(const Vector2& other) const noexcept = default;

	inline constexpr Vector2 operator+(Vector2 other) const noexcept
	{
		return Vector2(x + other.x, y + other.y);
	}

	inline constexpr Vector2 operator+(float value) const noexcept
	{
		return Vector2(x + value, y + value);
	}

	inline constexpr Vector2 operator-(Vector2 other) const noexcept
	{
		return Vector2(x - other.x, y - other.y);
	}

	inline constexpr Vector2 operator-(float value) const noexcept
	{
		return Vector2(x - value, y - value);
	}

	inline constexpr Vector2 operator*(Vector2 other) const noexcept
	{
		return Vector2(x * other.x, y * other.y);
	}

	inline constexpr Vector2 operator*(float value) const noexcept
	{
		return Vector2(x * value, y * value);
	}

	inline constexpr Vector2 operator/(Vector2 other) const noexcept
	{
		return Vector2(x / other.x, y / other.y);
	}

	inline constexpr Vector2 operator/(float value) const noexcept
	{
		return Vector2(x / value, y / value);
	}
	
	inline constexpr Vector2 operator-() const noexcept
	{
		return Vector2(-x, -y);
	}

	inline constexpr Vector2& operator+=(Vector2 other) noexcept
	{
		x += other.x;
		y += other.y;
		return *this;
	}

	inline constexpr Vector2& operator+=(float value) noexcept
	{
		x += value;
		y += value;
		return *this;
	}

	inline constexpr Vector2& operator-=(Vector2 other) noexcept
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}

	inline constexpr Vector2& operator-=(float value) noexcept
	{
		x -= value;
		y -= value;
		return *this;
	}

	inline constexpr Vector2& operator*=(Vector2 other) noexcept
	{
		x *= other.x;
		y *= other.y;
		return *this;
	}

	inline constexpr Vector2& operator*=(float value) noexcept
	{
		x *= value;
		y *= value;
		return *this;
	}

	inline constexpr Vector2& operator/=(Vector2 other) noexcept
	{
		x /= other.x;
		y /= other.y;
		return *this;
	}

	inline constexpr Vector2& operator/=(float value) noexcept
	{
		x /= value;
		y /= value;
		return *this;
	}
};
