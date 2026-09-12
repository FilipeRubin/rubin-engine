#pragma once
#include "glyph-metrics.h"
#include <containers/byte-map.h>

struct Glyph
{
	GlyphMetrics metrics;
	ByteMap byteMap = { 0, 0 };
};
