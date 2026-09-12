#pragma once
#include "i-font-generator.h"

class DebugFontGenerator : public IFontGenerator
{
public:
	RasterizedFontData GenerateFontData() const override;
};
