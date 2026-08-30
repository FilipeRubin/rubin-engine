#pragma once
#include "fixed-array.h"
#include <types/vertex-3d.h>
#include <utils/shared.h>

class MeshData3D final
{
public:
	MeshData3D();
	MeshData3D(const MeshData3D& other) = delete;
	MeshData3D(MeshData3D&& other) noexcept;
	MeshData3D& operator=(const MeshData3D& other) = delete;
	MeshData3D& operator=(MeshData3D&& other) noexcept;
	void SetVertices(Shared<FixedArray<Vertex3D>> vertices);
	void SetIndices(Shared<FixedArray<unsigned int>> indices);
	Shared<FixedArray<Vertex3D>> GetVertices() const;
	Shared<FixedArray<unsigned int>> GetIndices() const;
private:
	Shared<FixedArray<Vertex3D>> m_vertices;
	Shared<FixedArray<unsigned int>> m_indices;
};
