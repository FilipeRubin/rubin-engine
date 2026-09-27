#include <containers/texture-data.h>
#include <cstring>

TextureData::TextureData() :
	m_data(nullptr),
	m_dimensions(Dimensions(0, 0))
{
}

TextureData::TextureData(TextureData&& other) noexcept :
	m_data(std::move(other.m_data)),
	m_dimensions(other.m_dimensions)
{
	other.m_dimensions = Dimensions(0, 0);
}

TextureData& TextureData::operator=(TextureData&& other) noexcept
{
	if (this != &other)
	{
		m_data.Reset();

		m_data = std::move(other.m_data);
		m_dimensions = other.m_dimensions;

		other.m_dimensions = Dimensions(0, 0);
	}
	return *this;
}

Shared<FixedArray<Color8>> TextureData::GetData() const
{
	return m_data;
}

Dimensions TextureData::GetDimensions() const
{
	return m_dimensions;
}

void TextureData::SetData(Shared<FixedArray<Color8>> data, Dimensions dimensions)
{
	m_data = data;
	m_dimensions = dimensions;
}

Color8& TextureData::Pixel(Dimensions index)
{
	return m_data->GetData()[index.height * m_dimensions.width + index.width];
}
