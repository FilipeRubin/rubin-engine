#include <containers/mesh-data-3d.h>
#include <cstring>

MeshData3D::MeshData3D() :
	m_vertices(nullptr),
	m_indices(nullptr)
{
}

MeshData3D::MeshData3D(MeshData3D&& other) noexcept :
	m_vertices(std::move(other.m_vertices)),
	m_indices(std::move(other.m_indices))
{
}

MeshData3D& MeshData3D::operator=(MeshData3D&& other) noexcept
{
	if (&other != this)
	{
		m_vertices = std::move(other.m_vertices);
		m_indices = std::move(other.m_indices);
	}

	return *this;
}

void MeshData3D::SetVertices(Shared<FixedArray<Vertex3D>> vertices)
{
	m_vertices = vertices;
}

void MeshData3D::SetIndices(Shared<FixedArray<unsigned int>> indices)
{
	m_indices = indices;
}

Shared<FixedArray<Vertex3D>> MeshData3D::GetVertices() const
{
	return m_vertices;
}

Shared<FixedArray<unsigned int>> MeshData3D::GetIndices() const
{
	return m_indices;
}
