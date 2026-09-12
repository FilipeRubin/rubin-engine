#pragma once
#include "fixed-array.h"
#include <types/glyph.h>
#include <unordered_map>

using CodePoint = uint32_t;
using GlyphIndex = size_t;

class RasterizedFontData final
{
public:
	RasterizedFontData(FixedArray<Glyph>&& glyphs, std::unordered_map<CodePoint, GlyphIndex>&& glyphMap);
	RasterizedFontData(const RasterizedFontData& other) = delete;
	RasterizedFontData(RasterizedFontData&& other) noexcept;
	RasterizedFontData& operator=(const RasterizedFontData& other) = delete;
	RasterizedFontData& operator=(RasterizedFontData&& other) noexcept;

	const FixedArray<Glyph> GetGlyphs() const;
	const std::unordered_map<CodePoint, GlyphIndex> GetGlyphMap() const;
private:
	FixedArray<Glyph> m_glyphs;
	std::unordered_map<CodePoint, GlyphIndex> m_glyphMap;
};
