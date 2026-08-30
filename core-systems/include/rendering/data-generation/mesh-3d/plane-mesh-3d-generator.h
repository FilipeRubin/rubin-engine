#pragma once
#include "i-mesh-3d-generator.h"

class PlaneMesh3DGenerator : public IMesh3DGenerator
{
public:
	PlaneMesh3DGenerator(Vector2 dimensions);
	MeshData3D GenerateMeshData() const override;
private:
	Vector2 m_dimensions;
};
