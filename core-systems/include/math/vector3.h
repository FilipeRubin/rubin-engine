#pragma once
#include <cmath>

struct Vector3
{
	float x;
	float y;
	float z;

	inline constexpr Vector3() noexcept :
		x(0.0f), y(0.0f), z(0.0f)
	{
	}

	inline constexpr Vector3(float x, float y, float z) noexcept :
		x(x), y(y), z(z)
	{
	}

	inline constexpr Vector3 operator+(const Vector3& other) const noexcept
	{
		return Vector3(x + other.x, y + other.y, z + other.z);
	}

	inline constexpr Vector3 operator+(const float& value) const noexcept
	{
		return Vector3(x + value, y + value, z + value);
	}

	inline constexpr Vector3 operator-(const Vector3& other) const noexcept
	{
		return Vector3(x - other.x, y - other.y, z - other.z);
	}

	inline constexpr Vector3 operator-(const float& value) const noexcept
	{
		return Vector3(x - value, y - value, z - value);
	}

	inline constexpr Vector3 operator*(const Vector3& other) const noexcept
	{
		return Vector3(x * other.x, y * other.y, z * other.z);
	}

	inline constexpr Vector3 operator*(const float& value) const noexcept
	{
		return Vector3(x * value, y * value, z * value);
	}

	inline constexpr Vector3 operator/(const Vector3& other) const noexcept
	{
		return Vector3(x / other.x, y / other.y, z / other.z);
	}

	inline constexpr Vector3 operator/(const float& value) const noexcept
	{
		return Vector3(x / value, y / value, z / value);
	}

	inline constexpr Vector3& operator+=(const Vector3& other) noexcept
	{
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}

	inline constexpr Vector3& operator-=(const Vector3& other) noexcept
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}

	inline Vector3 Normalized() const noexcept
	{
		const float l = Length();
		return l == 0.0f ? Vector3() : Vector3(
			x / l,
			y / l,
			z / l
		);
	}

	inline float Length() const noexcept
	{
		return std::sqrtf(LengthSquared());
	}

	inline constexpr float LengthSquared() const noexcept
	{
		return x * x + y * y + z * z;
	}
};
