#pragma once
#include <math/vector2i.h>

struct GlyphMetrics
{
	Vector2i size;
	Vector2i bearing;
	uint32_t advance;
};
