#include <containers/byte-map.h>
#include <logging/log-macros.h>

ByteMap::ByteMap(uint32_t width, uint32_t height) :
    m_bytes(width * height),
    m_dimensions(width, height)
{}

ByteMap::ByteMap(const FixedArray<uint8_t>& bytes, Dimensions dimensions) :
    m_bytes(bytes),
    m_dimensions(dimensions)
{
    if (dimensions.width * dimensions.height != m_bytes.GetElementCount())
    {
        LOG_ERROR("Byte array is inconsistent with dimensions.");
    }
}

ByteMap::ByteMap(FixedArray<uint8_t>&& bytes, Dimensions dimensions) :
    m_bytes(std::move(bytes)),
    m_dimensions(dimensions)
{
    if (dimensions.width * dimensions.height != m_bytes.GetElementCount())
    {
        LOG_ERROR("Byte array is inconsistent with dimensions.");
    }
}

uint8_t& ByteMap::Byte(Vector2i at)
{
    return m_bytes[at.y * m_dimensions.width + at.x];
}

const uint8_t& ByteMap::Byte(Vector2i at) const
{
    return m_bytes[at.y * m_dimensions.width + at.x];
}

FixedArray<uint8_t>& ByteMap::GetBytes()
{
    return m_bytes;
}

const FixedArray<uint8_t>& ByteMap::GetBytes() const
{
    return m_bytes;
}

const Dimensions& ByteMap::GetDimensions() const
{
    return m_dimensions;
}

void ByteMap::SetBytes(const FixedArray<uint8_t>& bytes, Dimensions dimensions)
{
    if (dimensions.width * dimensions.height != bytes.GetElementCount())
    {
        LOG_ERROR("Byte array is inconsistent with dimensions.");
    }

    m_bytes = bytes;
    m_dimensions = dimensions;
}

void ByteMap::SetBytes(FixedArray<uint8_t>&& bytes, Dimensions dimensions)
{
    if (dimensions.width * dimensions.height != bytes.GetElementCount())
    {
        LOG_ERROR("Byte array is inconsistent with dimensions.");
    }

    m_bytes = std::move(bytes);
    m_dimensions = dimensions;
}
