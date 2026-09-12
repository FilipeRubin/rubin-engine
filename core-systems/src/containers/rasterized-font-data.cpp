#include <containers/rasterized-font-data.h>

RasterizedFontData::RasterizedFontData(
	FixedArray<Glyph>&& glyphs,
	std::unordered_map<CodePoint, GlyphIndex>&& glyphMap
) :
	m_glyphs(glyphs),
	m_glyphMap(glyphMap)
{}

RasterizedFontData::RasterizedFontData(RasterizedFontData&& other) noexcept :
	m_glyphs(std::move(other.m_glyphs)),
	m_glyphMap(std::move(other.m_glyphMap))
{
}

RasterizedFontData& RasterizedFontData::operator=(RasterizedFontData && other) noexcept
{
	if (&other != this)
	{
		m_glyphs = std::move(other.m_glyphs);
		m_glyphMap = std::move(other.m_glyphMap);
	}

	return *this;
}

const FixedArray<Glyph> RasterizedFontData::GetGlyphs() const
{
	return m_glyphs;
}

const std::unordered_map<CodePoint, GlyphIndex> RasterizedFontData::GetGlyphMap() const
{
	return m_glyphMap;
}
