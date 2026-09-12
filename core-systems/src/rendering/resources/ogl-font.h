#pragma once
#include <rendering/resources/i-font.h>
#include <rendering/i-renderer-managed.h>
#include <rendering/ogl-renderer-user.h>
#include <containers/rasterized-font-data.h>

class OGLFont : public IFont, public IRendererManaged, public OGLRendererUser
{
public:
	OGLFont(OGLRenderer& renderer, RasterizedFontData&& fontData);
	bool IsValid() const override;
	void Bind() override;
	void Create() override;
	void Destroy() override;
private:
	unsigned int m_glyphAtlas;

	RasterizedFontData m_cachedFontData;

	FixedArray<uint8_t> GenerateTextureAtlasPixels(Dimensions& out_resulution);
	Dimensions CalculateUnpackedAtlasDimensions(Dimensions& out_gridSize, Dimensions& out_cellResolution);
};
