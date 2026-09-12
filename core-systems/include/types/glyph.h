#pragma once
#include "glyph-metrics.h"
#include <containers/byte-map.h>
#include <utils/shared.h>

struct Glyph
{
	GlyphMetrics metrics;
	Shared<ByteMap> byteMap;
};
