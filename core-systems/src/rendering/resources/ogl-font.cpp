#include "ogl-font.h"
#include <logging/log-macros.h>
#include <ogl.h>
#include <algorithm>
#include <bit>

OGLFont::OGLFont(OGLRenderer& renderer, RasterizedFontData&& fontData) :
    OGLRendererUser(renderer),
    m_glyphAtlas(0U),
    m_cachedFontData(std::move(fontData))
{}

bool OGLFont::IsValid() const
{
    return m_glyphAtlas != 0U;
}

void OGLFont::Bind()
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_glyphAtlas);
}

void OGLFont::Create()
{
    LOG_WARNING("Chance texture unit to GL_TEXTURE1 later.");
    LOG_DEBUG("Creating OpenGL font texture atlas.");
    glGenTextures(1, &m_glyphAtlas);
    glBindTexture(GL_TEXTURE_2D, m_glyphAtlas);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    Dimensions d;
    FixedArray<uint8_t> pixels = GenerateTextureAtlasPixels(d);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, d.width, d.height, 0, GL_RED, GL_UNSIGNED_BYTE, pixels.GetData());
    glGenerateMipmap(GL_TEXTURE_2D);
}

void OGLFont::Destroy()
{
    LOG_DEBUG("Destroying OpenGL font texture atlas.");
    glDeleteTextures(1, &m_glyphAtlas);
}

FixedArray<uint8_t> OGLFont::GenerateTextureAtlasPixels(Dimensions& out_resolution)
{
    Dimensions cellResolution;
    Dimensions gridSize;
    out_resolution = CalculateUnpackedAtlasDimensions(gridSize, cellResolution);
    const FixedArray<Glyph>& glyphs = m_cachedFontData.GetGlyphs();

    FixedArray<uint8_t> result = FixedArray<uint8_t>(out_resolution.width * out_resolution.height);

    std::memset(result.GetData(), 0, result.GetElementCount());

    for (int y = 0; y < gridSize.height; y++)
    {
        for (int x = 0; x < gridSize.width; x++)
        {
            size_t glyphIndex = x + y * gridSize.width;
            if (glyphIndex >= glyphs.GetElementCount())
                continue; // Probably should break instead, but nevermind for now
            const ByteMap& gBytes = glyphs[glyphIndex].byteMap;
            for (int gY = 0; gY < gBytes.GetDimensions().height; gY++)
            {
                for (int gX = 0; gX < gBytes.GetDimensions().width; gX++)
                {
                    size_t writeIndex =
                        (x * cellResolution.width + gX) +
                        ((gridSize.height - 1 - y) * cellResolution.height +
                            (gBytes.GetDimensions().height - 1 - gY)) * out_resolution.width;
                    if (writeIndex >= result.GetElementCount())
                    {
                        continue;
                    }
                    result[writeIndex] = gBytes.Byte({ gX, gY });
                }
            }
        }
    }
    
    return result;
}

Dimensions OGLFont::CalculateUnpackedAtlasDimensions(Dimensions& out_gridSize, Dimensions& out_cellResolution)
{
    const FixedArray<Glyph>& glyphs = m_cachedFontData.GetGlyphs();
    const size_t& numGlyphs = glyphs.GetElementCount();

    if (numGlyphs == 0ULL)
        return {};

    int& columns = out_gridSize.width;
    int& rows = out_gridSize.height;

    columns = (int)std::ceil(std::sqrt(numGlyphs));
    rows = (int)std::ceil(float(numGlyphs) / columns);

    int& cellWidth = out_cellResolution.width;
    int& cellHeight = out_cellResolution.height;

    for (int i = 0; i < numGlyphs; i++)
    {
        cellWidth = std::max(cellWidth, glyphs[i].byteMap.GetDimensions().width);
        cellHeight = std::max(cellHeight, glyphs[i].byteMap.GetDimensions().height);
    }

    return {
        cellWidth * columns,
        cellHeight * rows
    };
}
