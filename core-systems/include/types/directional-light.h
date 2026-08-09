#pragma once
#include "color.h"
#include <math/vector3.h>

struct DirectionalLight
{
	Color diffuse;
	Vector3 direction = Vector3(0.0f, -1.0f, 0.0f);
	float intensity = 1.0f;
};
