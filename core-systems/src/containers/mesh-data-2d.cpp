#include <containers/mesh-data-2d.h>
#include <cstring>

MeshData2D::MeshData2D() :
    m_vertices(nullptr),
    m_indices(nullptr)
{
}

MeshData2D::MeshData2D(MeshData2D&& other) noexcept :
    m_vertices(std::move(other.m_vertices)),
    m_indices(std::move(other.m_indices))
{
}

MeshData2D& MeshData2D::operator=(MeshData2D&& other) noexcept
{
    if (&other != this)
    {
        m_vertices = std::move(other.m_vertices);
        m_indices = std::move(other.m_indices);
    }

    return *this;
}

void MeshData2D::SetVertices(Shared<FixedArray<Vertex2D>> vertices)
{
    m_vertices = vertices;
}

void MeshData2D::SetIndices(Shared<FixedArray<unsigned int>> indices)
{
    m_indices = indices;
}

Shared<FixedArray<Vertex2D>> MeshData2D::GetVertices() const
{
    return m_vertices;
}

Shared<FixedArray<unsigned int>> MeshData2D::GetIndices() const
{
    return m_indices;
}
