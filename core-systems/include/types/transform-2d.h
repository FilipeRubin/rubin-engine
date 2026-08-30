#pragma once
#include <math/vector2.h>

struct Transform2D
{
	Vector2 position = Vector2(0.0f, 0.0f);
	float rotation = 0.0f;
	Vector2 scale = Vector2(1.0f, 1.0f);
};
