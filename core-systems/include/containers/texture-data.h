#pragma once
#include "fixed-array.h"
#include <types/color8.h>
#include <types/dimensions.h>
#include <utils/shared.h>

class TextureData
{
public:
	TextureData();
	TextureData(const TextureData& other) = delete;
	TextureData(TextureData&& other) noexcept;
	TextureData& operator=(const TextureData& other) = delete;
	TextureData& operator=(TextureData&& other) noexcept;

	Shared<FixedArray<Color8>> GetData() const;
	Dimensions GetDimensions() const;
	void SetData(Shared<FixedArray<Color8>> data, Dimensions dimensions);
	Color8& Pixel(Dimensions index);
private:
	Shared<FixedArray<Color8>> m_data;
	Dimensions m_dimensions;
};
