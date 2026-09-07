#pragma once
#include "fixed-array.h"
#include <cstdint>
#include <types/dimensions.h>
#include <math/vector2i.h>

class ByteMap final
{
public:
	ByteMap(uint32_t width, uint32_t height);
	ByteMap(const FixedArray<uint8_t>& bytes, Dimensions dimensions);
	ByteMap(FixedArray<uint8_t>&& bytes, Dimensions dimensions);
	uint8_t& Byte(Vector2i at);
	const uint8_t& Byte(Vector2i at) const;
	FixedArray<uint8_t>& GetBytes();
	const FixedArray<uint8_t>& GetBytes() const;
	const Dimensions& GetDimensions() const;
	void SetBytes(const FixedArray<uint8_t>& bytes, Dimensions dimensions);
	void SetBytes(FixedArray<uint8_t>&& bytes, Dimensions dimensions);
private:
	FixedArray<uint8_t> m_bytes;
	Dimensions m_dimensions;
};
