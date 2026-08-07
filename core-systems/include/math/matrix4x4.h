#pragma once
#include "vector3.h"
#include "vector4.h"
#include <cmath>

struct alignas(16) Matrix4x4
{
	Vector4 columns[4];

	static inline constexpr Matrix4x4 Identity() noexcept
	{
		return Matrix4x4
		{
			{1.0f, 0.0f, 0.0f, 0.0f},
			{0.0f, 1.0f, 0.0f, 0.0f},
			{0.0f, 0.0f, 1.0f, 0.0f},
			{0.0f, 0.0f, 0.0f, 1.0f}
		};
	}

	static inline Matrix4x4 Model(const Vector3 position, const Vector3 rotation, const Vector3 scale) noexcept
	{
		return (
			Matrix4x4::Translation(position) *
			Matrix4x4::RotationZ(rotation.z) *
			Matrix4x4::RotationY(rotation.y) *
			Matrix4x4::RotationX(rotation.x) *
			Matrix4x4::Scaling(scale)
		);
	}

	static inline Matrix4x4 View(const Vector3 position, const Vector3 rotation) noexcept
	{
		return (
			Matrix4x4::RotationX(rotation.x) *
			Matrix4x4::RotationY(rotation.y) *
			Matrix4x4::RotationZ(rotation.z) *
			Matrix4x4::Translation(position)
		);
	}

	static inline Matrix4x4 Perspective(float aspectRatio, float vFOV, float zNear, float zFar) noexcept
	{
		const float& ar = aspectRatio;
		const float& sf = std::tanf(vFOV / 2.0f);
		const float& zn = zNear;
		const float& zf = zFar;

		return Matrix4x4
		{
			{ 1.0f / (ar * sf),      0.0f,                         0.0f,  0.0f },
			{             0.0f, 1.0f / sf,                         0.0f,  0.0f },
			{             0.0f,      0.0f,        (zf + zn) / (zn - zf), -1.0f },
			{             0.0f,      0.0f, (2.0f * zf * zn) / (zn - zf),  0.0f }
		};
	}

	static inline constexpr Matrix4x4 Translation(const Vector3& t) noexcept
	{
		return Matrix4x4
		{
			{1.0f, 0.0f, 0.0f, 0.0f},
			{0.0f, 1.0f, 0.0f, 0.0f},
			{0.0f, 0.0f, 1.0f, 0.0f},
			{ t.x,  t.y,  t.z, 1.0f}
		};
	}

	static inline Matrix4x4 RotationX(float radians) noexcept
	{
		const float c = std::cosf(radians);
		const float s = std::sinf(radians);

		return Matrix4x4{
			{1.0f, 0.0f, 0.0f, 0.0f},
			{0.0f,    c,    s, 0.0f},
			{0.0f,   -s,    c, 0.0f},
			{0.0f, 0.0f, 0.0f, 1.0f}
		};
	}

	static inline Matrix4x4 RotationY(float radians) noexcept
	{
		const float c = std::cosf(radians);
		const float s = std::sinf(radians);

		return Matrix4x4
		{
			{   c, 0.0f,   -s, 0.0f},
			{0.0f, 1.0f, 0.0f, 0.0f},
			{   s, 0.0f,    c, 0.0f},
			{0.0f, 0.0f, 0.0f, 1.0f}
		};
	}

	static inline Matrix4x4 RotationZ(float radians) noexcept
	{
		const float c = std::cosf(radians);
		const float s = std::sinf(radians);

		return Matrix4x4
		{
			{   c,    s, 0.0f, 0.0f},
			{  -s,    c, 0.0f, 0.0f},
			{0.0f, 0.0f, 1.0f, 0.0f},
			{0.0f, 0.0f, 0.0f, 1.0f}
		};
	}

	static inline constexpr Matrix4x4 Scaling(const Vector3& s) noexcept
	{
		return Matrix4x4
		{
			{ s.x, 0.0f, 0.0f, 0.0f},
			{0.0f,  s.y, 0.0f, 0.0f},
			{0.0f, 0.0f,  s.z, 0.0f},
			{0.0f, 0.0f, 0.0f, 1.0f}
		};
	}

	inline constexpr Matrix4x4() noexcept :
		columns{ Vector4(), Vector4(), Vector4(), Vector4() }
	{
	}

	inline constexpr Matrix4x4(const Vector4& column0, const Vector4& column1, const Vector4& column2, const Vector4& column3) noexcept :
		columns{ column0, column1, column2, column3 }
	{
	}

	inline constexpr const float* Data() const noexcept
	{
		return static_cast<const float*>(static_cast<const void*>(columns));
	}

	inline constexpr Vector4& operator[](size_t index) noexcept
	{
		return columns[index];
	}

	inline constexpr const Vector4& operator[](size_t index) const noexcept
	{
		return columns[index];
	}

	inline constexpr Vector4 operator*(const Vector4& vector) const noexcept
	{
		const Vector4(&a)[4] = columns;
		const Vector4& b = vector;
		
		return Vector4
		{
			a[0][0] * b[0] + a[1][0] * b[1] + a[2][0] * b[2] + a[3][0] * b[3],
			a[0][1] * b[0] + a[1][1] * b[1] + a[2][1] * b[2] + a[3][1] * b[3],
			a[0][2] * b[0] + a[1][2] * b[1] + a[2][2] * b[2] + a[3][2] * b[3],
			a[0][3] * b[0] + a[1][3] * b[1] + a[2][3] * b[2] + a[3][3] * b[3]
		};
	}

	inline constexpr Matrix4x4 operator*(const Matrix4x4& other) const noexcept
	{
		const Vector4(&a)[4] = columns;
		const Vector4(&b)[4] = other.columns;

		return Matrix4x4
		{
			// Colummn 0
			{
				a[0][0] * b[0][0] + a[1][0] * b[0][1] + a[2][0] * b[0][2] + a[3][0] * b[0][3],
				a[0][1] * b[0][0] + a[1][1] * b[0][1] + a[2][1] * b[0][2] + a[3][1] * b[0][3],
				a[0][2] * b[0][0] + a[1][2] * b[0][1] + a[2][2] * b[0][2] + a[3][2] * b[0][3],
				a[0][3] * b[0][0] + a[1][3] * b[0][1] + a[2][3] * b[0][2] + a[3][3] * b[0][3]
			},
			// Column 1
			{
				a[0][0] * b[1][0] + a[1][0] * b[1][1] + a[2][0] * b[1][2] + a[3][0] * b[1][3],
				a[0][1] * b[1][0] + a[1][1] * b[1][1] + a[2][1] * b[1][2] + a[3][1] * b[1][3],
				a[0][2] * b[1][0] + a[1][2] * b[1][1] + a[2][2] * b[1][2] + a[3][2] * b[1][3],
				a[0][3] * b[1][0] + a[1][3] * b[1][1] + a[2][3] * b[1][2] + a[3][3] * b[1][3]
			},
			// Column 2
			{
				a[0][0] * b[2][0] + a[1][0] * b[2][1] + a[2][0] * b[2][2] + a[3][0] * b[2][3],
				a[0][1] * b[2][0] + a[1][1] * b[2][1] + a[2][1] * b[2][2] + a[3][1] * b[2][3],
				a[0][2] * b[2][0] + a[1][2] * b[2][1] + a[2][2] * b[2][2] + a[3][2] * b[2][3],
				a[0][3] * b[2][0] + a[1][3] * b[2][1] + a[2][3] * b[2][2] + a[3][3] * b[2][3]
			},
			// Column 3
			{
				a[0][0] * b[3][0] + a[1][0] * b[3][1] + a[2][0] * b[3][2] + a[3][0] * b[3][3],
				a[0][1] * b[3][0] + a[1][1] * b[3][1] + a[2][1] * b[3][2] + a[3][1] * b[3][3],
				a[0][2] * b[3][0] + a[1][2] * b[3][1] + a[2][2] * b[3][2] + a[3][2] * b[3][3],
				a[0][3] * b[3][0] + a[1][3] * b[3][1] + a[2][3] * b[3][2] + a[3][3] * b[3][3]
			}
		};
	}
};
