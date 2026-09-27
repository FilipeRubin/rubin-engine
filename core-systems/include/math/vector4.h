#pragma once

struct alignas(16) Vector4
{
	float x;
	float y;
	float z;
	float w;

	inline constexpr Vector4() noexcept :
		x(0.0f), y(0.0f), z(0.0f), w(0.0f)
	{
	}

	inline constexpr Vector4(float x, float y, float z, float w) noexcept :
		x(x), y(y), z(z), w(w)
	{
	}

	inline constexpr float Dot(Vector4 other) const noexcept
	{
		return x * other.x + y * other.y + z * other.z + w * other.w;
	}

	inline float Length() const noexcept
	{
		return std::sqrtf(LengthSquared());
	}

	inline constexpr float LengthSquared() const noexcept
	{
		return x * x + y * y + z * z + w * w;
	}

	inline Vector4 Normalized() const noexcept
	{
		const float l = Length();
		return l == 0.0f ? Vector4() : Vector4(
			x / l,
			y / l,
			z / l,
			w / l
		);
	}

	inline constexpr float& operator[](size_t index) noexcept
	{
		return static_cast<float*>(&x)[index];
	}

	inline constexpr const float& operator[](size_t index) const noexcept
	{
		return static_cast<const float*>(&x)[index];
	}

	inline constexpr Vector4 operator+(Vector4 other) const noexcept
	{
		return Vector4(x + other.x, y + other.y, z + other.z, w + other.w);
	}

	inline constexpr Vector4 operator+(float value) const noexcept
	{
		return Vector4(x + value, y + value, z + value, w + value);
	}

	inline constexpr Vector4 operator-(Vector4 other) const noexcept
	{
		return Vector4(x - other.x, y - other.y, z - other.z, w - other.w);
	}

	inline constexpr Vector4 operator-(float value) const noexcept
	{
		return Vector4(x - value, y - value, z - value, w - value);
	}

	inline constexpr Vector4 operator*(Vector4 other) const noexcept
	{
		return Vector4(x * other.x, y * other.y, z * other.z, w * other.w);
	}

	inline constexpr Vector4 operator*(float value) const noexcept
	{
		return Vector4(x * value, y * value, z * value, w * value);
	}

	inline constexpr Vector4 operator/(Vector4 other) const noexcept
	{
		return Vector4(x / other.x, y / other.y, z / other.z, w / other.w);
	}

	inline constexpr Vector4 operator/(float value) const noexcept
	{
		return Vector4(x / value, y / value, z / value, w / value);
	}

	inline constexpr Vector4 operator-() const noexcept
	{
		return Vector4(-x, -y, -z, -w);
	}

	inline constexpr Vector4& operator+=(Vector4 other) noexcept
	{
		x += other.x;
		y += other.y;
		z += other.z;
		w += other.w;
		return *this;
	}

	inline constexpr Vector4& operator+=(float value) noexcept
	{
		x += value;
		y += value;
		z += value;
		w += value;
		return *this;
	}

	inline constexpr Vector4& operator-=(Vector4 other) noexcept
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		w -= other.w;
		return *this;
	}

	inline constexpr Vector4& operator-=(float value) noexcept
	{
		x -= value;
		y -= value;
		z -= value;
		w -= value;
		return *this;
	}

	inline constexpr Vector4& operator*=(Vector4 other) noexcept
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;
		w *= other.w;
		return *this;
	}

	inline constexpr Vector4& operator*=(float value) noexcept
	{
		x *= value;
		y *= value;
		z *= value;
		w *= value;
		return *this;
	}

	inline constexpr Vector4& operator/=(Vector4 other) noexcept
	{
		x /= other.x;
		y /= other.y;
		z /= other.z;
		w /= other.w;
		return *this;
	}

	inline constexpr Vector4& operator/=(float value) noexcept
	{
		x /= value;
		y /= value;
		z /= value;
		w /= value;
		return *this;
	}
};
