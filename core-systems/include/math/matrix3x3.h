#pragma once
#include "vector2.h"
#include "vector3.h"
#include <types/dimensions.h>

struct alignas(4) Matrix3x3
{
	Vector3 columns[3];

	static inline constexpr Matrix3x3 Identity() noexcept
	{
		return Matrix3x3
		{
			{ 1.0f, 0.0f, 0.0f },
			{ 0.0f, 1.0f, 0.0f },
			{ 0.0f, 0.0f, 1.0f }
		};
	}

	static inline constexpr Matrix3x3 Model(const Vector2 position, const float rotation, const Vector2 scale) noexcept
	{
		return (
			Translation(position) *
			Rotation(rotation) *
			Scaling(scale)
		);
	}

	static inline constexpr Matrix3x3 Viewport(const Vector2& size) noexcept
	{
		return Matrix3x3
		{
			{ 2.0f / size.x, 0.0f,           0.0f },
			{ 0.0f,          -2.0f / size.y, 0.0f },
			{ -1.0f,          1.0f,           1.0f }
		};
	}

	static inline constexpr Matrix3x3 Translation(const Vector2& t) noexcept
	{
		return Matrix3x3
		{
			{ 1.0f, 0.0f, 0.0f },
			{ 0.0f, 1.0f, 0.0f },
			{  t.x,  t.y, 1.0f }
		};
	}

	static inline Matrix3x3 Rotation(float angle) noexcept
	{
		const float c = std::cos(angle);
		const float s = std::sin(angle);

		return Matrix3x3
		{
			{    c,    s, 0.0f },
			{   -s,    c, 0.0f },
			{ 0.0f, 0.0f, 1.0f }
		};
	}

	static inline constexpr Matrix3x3 Scaling(const Vector2& s) noexcept
	{
		return Matrix3x3
		{
			{  s.x, 0.0f, 0.0f },
			{ 0.0f,  s.y, 0.0f },
			{ 0.0f, 0.0f, 1.0f }
		};
	}

	inline constexpr Matrix3x3() noexcept :
		columns{ Vector3(), Vector3(), Vector3() }
	{
	}

	inline constexpr Matrix3x3(const Vector3& column0, const Vector3& column1, const Vector3& column2) noexcept :
		columns{ column0, column1, column2 }
	{
	}

	inline constexpr const float* Data() const noexcept
	{
		return static_cast<const float*>(static_cast<const void*>(columns));
	}

	inline constexpr Vector3& operator[](size_t index) noexcept
	{
		return columns[index];
	}

	inline constexpr const Vector3& operator[](size_t index) const noexcept
	{
		return columns[index];
	}

	inline constexpr Vector3 operator*(const Vector3& vector) const noexcept
	{
		const Vector3(&a)[3] = columns;
		const Vector3& b = vector;

		return Vector3
		{
			a[0][0] * b[0] + a[1][0] * b[1] + a[2][0] * b[2],
			a[0][1] * b[0] + a[1][1] * b[1] + a[2][1] * b[2],
			a[0][2] * b[0] + a[1][2] * b[1] + a[2][2] * b[2]
		};
	}

	inline constexpr Matrix3x3 operator*(const Matrix3x3& other) const noexcept
	{
		const Vector3(&a)[3] = columns;
		const Vector3(&b)[3] = other.columns;

		return Matrix3x3
		{
			// Colummn 0
			{
				a[0][0] * b[0][0] + a[1][0] * b[0][1] + a[2][0] * b[0][2],
				a[0][1] * b[0][0] + a[1][1] * b[0][1] + a[2][1] * b[0][2],
				a[0][2] * b[0][0] + a[1][2] * b[0][1] + a[2][2] * b[0][2]
			},
			// Column 1
			{
				a[0][0] * b[1][0] + a[1][0] * b[1][1] + a[2][0] * b[1][2],
				a[0][1] * b[1][0] + a[1][1] * b[1][1] + a[2][1] * b[1][2],
				a[0][2] * b[1][0] + a[1][2] * b[1][1] + a[2][2] * b[1][2]
			},
			// Column 2
			{
				a[0][0] * b[2][0] + a[1][0] * b[2][1] + a[2][0] * b[2][2],
				a[0][1] * b[2][0] + a[1][1] * b[2][1] + a[2][1] * b[2][2],
				a[0][2] * b[2][0] + a[1][2] * b[2][1] + a[2][2] * b[2][2]
			}
		};
	}
};
