#pragma once
#include "i-mesh-2d-generator.h"

class QuadMesh2DGenerator : public IMesh2DGenerator
{
public:
	QuadMesh2DGenerator(Vector2 size);
	MeshData2D GenerateMeshData() const override;
private:
	Vector2 m_size;
};
