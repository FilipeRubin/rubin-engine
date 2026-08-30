#pragma once
#include "fixed-array.h"
#include <types/vertex-2d.h>
#include <utils/shared.h>

class MeshData2D final
{
public:
	MeshData2D();
	MeshData2D(const MeshData2D& other) = delete;
	MeshData2D(MeshData2D&& other) noexcept;
	MeshData2D& operator=(const MeshData2D& other) = delete;
	MeshData2D& operator=(MeshData2D&& other) noexcept;
	void SetVertices(Shared<FixedArray<Vertex2D>> vertices);
	void SetIndices(Shared<FixedArray<unsigned int>> indices);
	Shared<FixedArray<Vertex2D>> GetVertices() const;
	Shared<FixedArray<unsigned int>> GetIndices() const;
private:
	Shared<FixedArray<Vertex2D>> m_vertices;
	Shared<FixedArray<unsigned int>> m_indices;
};
