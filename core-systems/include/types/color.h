#pragma once

struct Color8;

struct alignas(16) Color
{
	float r, g, b, a;

	inline constexpr Color() noexcept :
		r(0.0f), g(0.0f), b(0.0f), a(0.0f)
	{
	}

	inline constexpr Color(float r, float g, float b, float a) noexcept :
		r(r), g(g), b(b), a(a)
	{
	}

	inline constexpr Color(float r, float g, float b) noexcept :
		r(r), g(g), b(b), a(1.0f)
	{
	}

	explicit operator Color8() const noexcept;
};
