#include <rendering/data-generation/texture-2d/checkerboard-texture-2d-generator.h>

CheckerboardTexture2DGenerator::CheckerboardTexture2DGenerator(Dimensions dimensions, Color color1, Color color2) :
    m_dimensions(dimensions), m_color1(color1), m_color2(color2)
{}

TextureData CheckerboardTexture2DGenerator::GenerateTextureData() const
{
    TextureData result;

    size_t size = m_dimensions.width * m_dimensions.height;
    Shared<FixedArray<Color8>> textureData = MakeShared<FixedArray<Color8>>(size);

    Color8 c1 = (Color8)m_color1;
    Color8 c2 = (Color8)m_color2;

    for (int i = 0; i < m_dimensions.width; i++)
    {
        for (int j = 0; j < m_dimensions.height; j++)
        {
            int index = (j * m_dimensions.width) + i;

            (*textureData)[index] = ((i + j) % 2 != 0) ? c1 : c2;
        }
    }

    result.SetData(textureData, m_dimensions);
    return result;
}
