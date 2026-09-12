#pragma once
#include <containers/rasterized-font-data.h>

class IFontGenerator
{
public:
	virtual ~IFontGenerator() = default;
	virtual RasterizedFontData GenerateFontData() const = 0;
};
